// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteSimulationExample.h"
#include "RouteBuilder.h"
#include "VectorMath.h"
#include "RouteStyle.h"
#include "VectorMath.h"
#include "GlobeCameraTouchControllerConfiguration.h"
#include "Logger.h"
#include "CameraHelpers.h"
#include "RenderCamera.h"
#include "ScreenProperties.h"
#include "GlobeCameraTouchController.h"
#include "GlobeCameraController.h"
#include "SceneModel.h"
#include "SceneModelLoader.h"
#include "SceneModelRenderableFilter.h"
#include "Random.h"

using namespace Eegeo;
using namespace Eegeo::Routes;
using namespace Eegeo::Routes::Simulation;
using namespace Eegeo::Routes::Simulation::View;
using namespace Eegeo::Routes::Simulation::Camera;

namespace Examples
{

void RouteSimulationExampleObserver::OnLinkReached(const Eegeo::Routes::Simulation::RouteSimulationSession& session) const
{
	// At each new link, we change the model being drawn
    int vehicleIndex = rand() % (int)(m_vehicleModels.size());
    Eegeo::Rendering::SceneModels::SceneModel* vehicleModel = m_vehicleModels.at(vehicleIndex);
	m_pModelBinding->SetModel(vehicleModel);

	const dv3& ecef = session.GetCurrentPositionEcef();

	Eegeo::Space::LatLongAltitude latLongAltitude = Eegeo::Space::LatLongAltitude::FromECEF(ecef);
	Eegeo_TTY("New link reached at %f, %f\n", latLongAltitude.GetLatitudeInDegrees(), latLongAltitude.GetLongitudeInDegrees());

}

RouteSimulationExample::RouteSimulationExample(RouteService& routeService,
        RouteSimulationService& routeSimulationService,
        RouteSimulationViewService& routeSimulationViewService,
        Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
        Eegeo::Camera::GlobeCamera::GlobeCameraController* pDefaultCameraController,
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& defaultCameraTouchController,
        RouteSimulationGlobeCameraControllerFactory& routeSimulationGlobeCameraControllerFactory,
        const IRouteSimulationExampleViewFactory& routeSimulationExampleViewFactory,
        EegeoWorld& world,
        const Eegeo::Rendering::ScreenProperties& screenProperties)
	: GlobeCameraExampleBase(pDefaultCameraController, defaultCameraTouchController)
    , m_routeService(routeService)
	,m_routeSimulationService(routeSimulationService)
	,m_routeSimulationViewService(routeSimulationViewService)
	,m_routeSimulationGlobeCameraControllerFactory(routeSimulationGlobeCameraControllerFactory)
	,m_world(world)
    ,m_sceneModelLoader(sceneModelLoader)
	,m_initialised(false)
	,m_pRoute(NULL)
	,m_usingFollowCamera(false)
	,m_routeSimulationExampleViewFactory(routeSimulationExampleViewFactory)
    , m_pSessionCycle(NULL)
    , m_pSessionAlternatingSpeedChanger(NULL)
    , m_pSessionCamera(NULL)
    , m_pViewBindingForCycleSession(NULL)
    , m_pViewBindingForOscillatingSession(NULL)
    , m_pViewBindingForCameraSession(NULL)
	, m_linkSpeedMultiplier(1.f)
    ,m_pRouteSessionFollowCameraController(NULL)
    , m_pRouteSimulationView(NULL)
    ,m_pVehicleModel1(NULL)
    ,m_pVehicleModel2(NULL)
	,m_decreaseSpeedToggleHandler(this, &RouteSimulationExample::DecreaseSpeedFollowed)
	,m_increaseSpeedToggleHandler(this, &RouteSimulationExample::IncreaseSpeedFollowed)
	,m_followCameraToggleHandler(this, &RouteSimulationExample::ToggleFollowCamera)
	,m_rotateToFollowToggledHandler(this, &RouteSimulationExample::ToggleRotateToFollow)
	,m_directionChangedHandler(this, &RouteSimulationExample::ChangeFollowDirection)
	,m_roadSideChangedHandler(this, &RouteSimulationExample::ToggleSideOfRoadToDriveOn)
{
	Eegeo::Space::EcefTangentBasis cameraInterestBasis;

	Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
	    Eegeo::Space::LatLong::FromDegrees(37.793348, -122.399035).ToECEF(),
	    354.824249f,
	    cameraInterestBasis);

	pDefaultCameraController->SetView(cameraInterestBasis, 1374.298706f);
    
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchConfiguration = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
    
    RouteSimulationGlobeCameraControllerConfig routeSimCameraConfig = RouteSimulationGlobeCameraControllerConfig::CreateDefault();
    
    m_pRouteSessionFollowCameraController = m_routeSimulationGlobeCameraControllerFactory.Create(false, touchConfiguration, routeSimCameraConfig, screenProperties);
}

void RouteSimulationExample::Initialise()
{
	//Load a model containing the nodes which will be bound to our route simulation sessions. For
	//a detailed explation see http://www.eegeo.com/developers/documentation/loading_rendering_models
	//or see LoadModelExample.cpp.
    LoadModelVehicleNodes(m_pVehicleModel1, m_pVehicleModel2, m_switchableVehicleModels);

	//Build the route - see RouteDrawingExample.cpp for a detailed explanation of building routes, or
	//check out http://www.eegeo.com/developers/documentation/routes
	m_pRoute = BuildRoute();

	//Create three simulation sessions for the same route. This first illustrates a session which
	//we will control such that it just loops around in a cycle forever, to illustrate route 'playback'.
	//The first session will just obey the link speed for the route links.
	m_pSessionCycle = m_routeSimulationService.BeginRouteSimulationSession(*m_pRoute);

	//The second session we will control such that it oscillates back and forward to illustrate
	//'rewinding' a route. We will vary the speed dynamically to illustrate 'fast-forward' playback.
	m_pSessionAlternatingSpeedChanger = m_routeSimulationService.BeginRouteSimulationSession(*m_pRoute);

	//The final session will be used to illustrate mapping a point on to the route. A useful application
	//of this might be to map a GPS location on to the route, but for illustrative purposes we map the
	//camera focus point on to the route, so that the effect is clear without relying on sampling the
	//GPS (we should not require you to catch a bus to test this example!).
	m_pSessionCamera = m_routeSimulationService.BeginRouteSimulationSession(*m_pRoute);

	//Start playback on the first two routes from the beginning - we will not start playback on the
	//m_pSessionCamera session as we want to control this session manually by setting the position
	//ourselves (and having the session select the closest route point to this position).
	m_pSessionCycle->StartPlaybackFromBeginning();
	m_pSessionAlternatingSpeedChanger->StartPlaybackFromBeginning();

	//Dynamically double the playback speed for the second route to illustrate fast-forward.

	m_linkSpeedMultiplier = 2.f;
	m_pSessionAlternatingSpeedChanger->UseLinkSpeedValueWithMultiplier(m_linkSpeedMultiplier);

	//Create a local transform for the views which will be bound to the route simulation
	//session. The source vehicle models are small so must be scaled up - a scale factor
	//of 15 works well for this case. In the mode we are using, the vehicles are also
	//facing backward, so we can rotate them in local space by 180 degrees so they face
	//forwards.
	Eegeo::m44 scale, rotation, transform;
	scale.Scale(15.f);
	rotation.RotateY(Eegeo::Math::kPI);
	m44::Mul(transform, scale, rotation);

	//Bind a view to each of the three sessions using a different vehicle node from the model.
	//A pointer is stored to the view bindings, such that we can access them to change the local
	//model transform as the vehicle changes direction (when the route alternates between rewind
	//and regular playback), or to disable and enable the rendering of the views.
	m_pViewBindingForCycleSession = m_routeSimulationViewService.CreateBinding(*m_pSessionCycle, m_switchableVehicleModels.at(0), transform);
	m_pViewBindingForOscillatingSession = m_routeSimulationViewService.CreateBinding(*m_pSessionAlternatingSpeedChanger, m_pVehicleModel1, transform);
	m_pViewBindingForCameraSession = m_routeSimulationViewService.CreateBinding(*m_pSessionCamera, m_pVehicleModel2, transform);


    m_pRouteSessionFollowCameraController->SetTiltEnabled(true);
    m_pRouteSessionFollowCameraController->SetView(37.7858, -122.401, 0, 1781.0f);
	m_pRouteSessionFollowCameraController->StartFollowingSession(m_pSessionAlternatingSpeedChanger);


	// Observe the progress along the route
	m_pExampleObserver = Eegeo_NEW(RouteSimulationExampleObserver)(m_pViewBindingForCycleSession, m_switchableVehicleModels);
	m_pSessionCycle->AddSessionObserver(*m_pExampleObserver);

	//Create some UI buttons for controlling the simulation...
	CreateAndBindUI();
}

void RouteSimulationExample::EarlyUpdate(float dt)
{
	//Defer initialisation until the loading state is over.
	if(m_world.Initialising())
	{
		return;
	}

	//Just create the routes once.
	if(!m_initialised)
	{
		//Load the model, build the route, create and configure the simulation settings.
		Initialise();

		//We have initialised so don't need to do so again.
		m_initialised = true;
	}
    
	//If we are using a follow camera bound to a route simulation session, we should update this camera.
	//Otherwise, the default camera should be used.
	if(m_usingFollowCamera)
	{
		m_pRouteSessionFollowCameraController->Update(dt);
	}
    else
    {
        GlobeCameraExampleBase::EarlyUpdate(dt);
    }
}

void RouteSimulationExample::Update(float dt)
{
	//Defer initialisation until the loading state is over.
	if(!m_initialised)
	{
		return;
	}
    
    Eegeo::Camera::RenderCamera renderCamera(m_usingFollowCamera
                                             ? m_pRouteSessionFollowCameraController->GetRenderCamera()
                                             : GetGlobeCameraController().GetRenderCamera());
    
    m_pViewBindingForCycleSession->Update();
    m_pViewBindingForOscillatingSession->Update();
    m_pViewBindingForCameraSession->Update();
    
	//The route session for which we want to project a position to (in this case, the ecef interest
	//point) should be updated giving it the latest position.
    Eegeo::Camera::CameraState cameraState(GetCurrentCameraState());
    const Eegeo::dv3& ecefPositionToProjectToRoute = cameraState.InterestPointEcef();
	m_pSessionCamera->SetCurrentPositionSnappedToRoute(ecefPositionToProjectToRoute);

	//For the session which should just cycle the route forever, when it has completed simply end
	//the session and restart playback from the beginning.
	if(m_pSessionCycle->IsRouteCompleted())
	{
		m_pSessionCycle->EndPlayback();
		m_pSessionCycle->StartPlaybackFromBeginning();
	}

	//For the session which should oscillate, when the route is finished we change the playback direction
	//and unpause the session (such that it restarts from where it left off), and also demonstrate that
	//we can change playback speed by selecting a random speed multiplier. This multiplier applies to the
	//link speed (such that it is like a 'fast-forward' function). If we wanted to, we could also override
	//the playback speed such that the link speed is ignored by calling the UseCustomSpeedValue method.
	if(m_pSessionAlternatingSpeedChanger->IsRouteCompleted())
	{
		m_pSessionAlternatingSpeedChanger->TogglePlaybackDirection();
		m_pSessionAlternatingSpeedChanger->Unpause();

		m_linkSpeedMultiplier = 0.5f + ((rand() % 200)/100.f);
		m_pSessionAlternatingSpeedChanger->UseLinkSpeedValueWithMultiplier(m_linkSpeedMultiplier);
	}

	EXAMPLE_LOG("%f metres from start of route. %f percent.\n", m_pSessionAlternatingSpeedChanger->GetDistanceFromStartInMetres(),(m_pSessionAlternatingSpeedChanger->GetDistanceFromStartInMetres() / m_pRoute->GetLength())*100.0f) ;
}

void RouteSimulationExample::Suspend()
{
	m_pSessionCycle->RemoveSessionObserver(*m_pExampleObserver);
	delete m_pExampleObserver;
	m_pExampleObserver = NULL;

	m_routeSimulationViewService.DestroyBinding(m_pViewBindingForCycleSession);
	m_routeSimulationViewService.DestroyBinding(m_pViewBindingForOscillatingSession);
	m_routeSimulationViewService.DestroyBinding(m_pViewBindingForCameraSession);
    
	m_routeSimulationService.EndRouteSimulationSession(m_pSessionCycle);
	m_routeSimulationService.EndRouteSimulationSession(m_pSessionAlternatingSpeedChanger);
	m_routeSimulationService.EndRouteSimulationSession(m_pSessionCamera);

	m_pSessionCycle = NULL;
	m_pSessionAlternatingSpeedChanger = NULL;
	m_pSessionCamera = NULL;

	m_routeService.DestroyRoute(m_pRoute);
	m_pRoute = NULL;
    
    delete m_pVehicleModel1;
    m_pVehicleModel1 = NULL;
    delete m_pVehicleModel2;
    m_pVehicleModel2 = NULL;
    
    for(int i = 0; i < 3; i++)
    {
        delete m_switchableVehicleModels.at(i);
    }
    m_switchableVehicleModels.clear();

	delete m_pRouteSessionFollowCameraController;
	m_pRouteSessionFollowCameraController = NULL;

	m_pRouteSimulationView->RemoveIncreaseSpeedHandler(m_increaseSpeedToggleHandler);
	m_pRouteSimulationView->RemoveDecreaseSpeedHandler(m_decreaseSpeedToggleHandler);
	m_pRouteSimulationView->RemoveFollowCameraDirectionChangedHandler(m_directionChangedHandler);
	m_pRouteSimulationView->RemoveFollowCameraToggledHandler(m_followCameraToggleHandler);
	m_pRouteSimulationView->RemoveRotateToFollowToggledHandler(m_rotateToFollowToggledHandler);
	m_pRouteSimulationView->RemoveSideOfRoadToDriveOnToggledHandler(m_roadSideChangedHandler);

	Eegeo_DELETE m_pRouteSimulationView;

	m_pRouteSimulationView = NULL;

	m_initialised = false;
}

void RouteSimulationExample::ToggleFollowCamera()
{
	m_usingFollowCamera = !m_usingFollowCamera;

	//Disable the rendering of the non-followed session view bindings if we are following,
	//otherwise enable them.
	m_pViewBindingForCycleSession->SetEnabled(!m_usingFollowCamera);
	m_pViewBindingForCameraSession->SetEnabled(!m_usingFollowCamera);
}

void RouteSimulationExample::ChangeFollowDirection()
{
	Eegeo_ASSERT(m_usingFollowCamera);

	m_pSessionAlternatingSpeedChanger->TogglePlaybackDirection();
}
    
Eegeo::Camera::CameraState RouteSimulationExample::GetCurrentCameraState() const
{
    if(m_usingFollowCamera)
    {
        return m_pRouteSessionFollowCameraController->GetCameraState();
    }
    else
    {
        return GetGlobeCameraController().GetCameraState();
    }
}
    
void RouteSimulationExample::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
{
    m_pRouteSessionFollowCameraController->UpdateScreenProperties(screenProperties);
    GetGlobeCameraController().UpdateScreenProperties(screenProperties);
}
    
float ClampedLinkSpeed(float linkSpeed)
{
	return Math::Clamp(linkSpeed, 0.5f, 32.f);
}

void RouteSimulationExample::IncreaseSpeedFollowed()
{
	Eegeo_ASSERT(m_usingFollowCamera);

	m_linkSpeedMultiplier += 0.5f;
	m_linkSpeedMultiplier = ClampedLinkSpeed(m_linkSpeedMultiplier);
	m_pSessionAlternatingSpeedChanger->UseLinkSpeedValueWithMultiplier(m_linkSpeedMultiplier);
}

void RouteSimulationExample::DecreaseSpeedFollowed()
{
	Eegeo_ASSERT(m_usingFollowCamera);

	m_linkSpeedMultiplier -= 0.5f;
	m_linkSpeedMultiplier = ClampedLinkSpeed(m_linkSpeedMultiplier);
	m_pSessionAlternatingSpeedChanger->UseLinkSpeedValueWithMultiplier(m_linkSpeedMultiplier);
}

void RouteSimulationExample::ToggleRotateToFollow()
{
	Eegeo_ASSERT(m_usingFollowCamera);

	if(m_pRouteSessionFollowCameraController->GetOrientationMode() == RouteSimulationGlobeCameraController::UnlockedOrientation)
	{
		m_pRouteSessionFollowCameraController->LockFollowHeadingToCurrentLinkDirection();
	}
	else
	{
		m_pRouteSessionFollowCameraController->UnlockFollowHeading();
	}
}

void RouteSimulationExample::ToggleSideOfRoadToDriveOn()
{
	m_pSessionAlternatingSpeedChanger->SetDrivesOnRight(!m_pSessionAlternatingSpeedChanger->GetDrivesOnRight());
	m_pSessionCamera->SetDrivesOnRight(!m_pSessionCamera->GetDrivesOnRight());
	m_pSessionCycle->SetDrivesOnRight(!m_pSessionCycle->GetDrivesOnRight());
}

Route* RouteSimulationExample::BuildRoute() const
{
	const float halfWidth = 5.f;
	const float routeSpeedMetersPerSecond = 20.f;
	const Eegeo::v4 routeColor(1, 0, 1, 0.6f);
	const float altitudeMeters = 3.f;

	RouteBuilder builder;

	std::vector<RouteVertex> points = builder.Start(routeColor, halfWidth, routeSpeedMetersPerSecond, Routes::Road)
	                                  .AddPoint(37.795729,-122.401698, altitudeMeters)
	                                  .AddPoint(37.794873,-122.401516, altitudeMeters)
	                                  .AddPoint(37.794728,-122.403179, altitudeMeters)
	                                  .AddPoint(37.794483,-122.404863, altitudeMeters)
	                                  .AddPoint(37.793618,-122.404670, altitudeMeters)
	                                  .AddPoint(37.793813,-122.403007, altitudeMeters)
	                                  .AddPoint(37.792940,-122.402825, altitudeMeters)
	                                  .AddPoint(37.793109,-122.401108, altitudeMeters)
	                                  .AddPoint(37.792143,-122.400990, altitudeMeters)
	                                  .AddPoint(37.790303,-122.400603, altitudeMeters)
	                                  .AddPoint(37.790324,-122.400126, altitudeMeters)
	                                  .AddPoint(37.794449,-122.394906, altitudeMeters)
	                                  .AddPoint(37.793253,-122.393238, altitudeMeters)
	                                  .AddPoint(37.793707,-122.392578, altitudeMeters)
	                                  .FinishRoute();

	const Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone);
	return m_routeService.CreateRoute(points, routeStyle, false);
}

    void RouteSimulationExample::LoadModelVehicleNodes(Eegeo::Rendering::SceneModels::SceneModel*& pVehicleModel1,
                                                       Eegeo::Rendering::SceneModels::SceneModel*& pVehicleModel2,
                                                       std::vector<Eegeo::Rendering::SceneModels::SceneModel*>& out_vehicleModels) const
{
    pVehicleModel1 = m_sceneModelLoader.LoadPOD("route_simulation_example/car1.pod");
    pVehicleModel2 = m_sceneModelLoader.LoadPOD("route_simulation_example/car2.pod");
    
    out_vehicleModels.push_back(pVehicleModel1->Clone());
    out_vehicleModels.push_back(pVehicleModel2->Clone());
    out_vehicleModels.push_back(m_sceneModelLoader.LoadPOD("route_simulation_example/car3.pod"));
}

void RouteSimulationExample::NotifyViewNeedsLayout()
{
    if (m_pRouteSimulationView != NULL)
    {
        m_pRouteSimulationView->NotifyNeedsLayout();
    }
}

//For each of the events our follow camera should intercept, we should handle this event
//and pass it to the follow camera if it is enabled. If the follow camera is enabled, we
//should block this event from being passed up to the default camera by declaring the
//event handled (by returning true from the even handler).
void RouteSimulationExample::Event_TouchRotate(const AppInterface::RotateData& data)
{
	if (m_usingFollowCamera)
	{
		m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchRotate(data);
	}
    else
    {
        GlobeCameraExampleBase::Event_TouchRotate(data);
    }
}

void RouteSimulationExample::Event_TouchRotate_Start(const AppInterface::RotateData& data)
{
	if (m_usingFollowCamera)
	{
		m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchRotate_Start(data);
	}
    else
    {
        GlobeCameraExampleBase::Event_TouchRotate_Start(data);
    }

}

void RouteSimulationExample::Event_TouchRotate_End(const AppInterface::RotateData& data)
{
	if(m_usingFollowCamera)
	{
		m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchRotate_End(data);
	}
    else
    {
        GlobeCameraExampleBase::Event_TouchRotate_End(data);
    }
}

void RouteSimulationExample::Event_TouchPinch(const AppInterface::PinchData& data)
{
	if(m_usingFollowCamera)
	{
		m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPinch(data);
	}
    else
    {
        GlobeCameraExampleBase::Event_TouchPinch(data);
    }
}

void RouteSimulationExample::Event_TouchPinch_Start(const AppInterface::PinchData& data)
{
	if(m_usingFollowCamera)
	{
		m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPinch_Start(data);
	}
    else
    {
        GlobeCameraExampleBase::Event_TouchPinch_Start(data);
    }
}

void RouteSimulationExample::Event_TouchPinch_End(const AppInterface::PinchData& data)
{
	if(m_usingFollowCamera)
	{
		m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPinch_End(data);
	}
    else
    {
        GlobeCameraExampleBase::Event_TouchPinch_End(data);
    }
}

void RouteSimulationExample::Event_TouchPan(const AppInterface::PanData& data)
{
	if(m_usingFollowCamera)
	{
		m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPan(data);
	}
    else
    {
        GlobeCameraExampleBase::Event_TouchPan(data);
    }
}

void RouteSimulationExample::Event_TouchPan_Start(const AppInterface::PanData& data)
{
	if(m_usingFollowCamera)
	{
		m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPan_Start(data);
	}
    else
    {
        GlobeCameraExampleBase::Event_TouchPan_Start(data);
    }
}

void RouteSimulationExample::Event_TouchPan_End(const AppInterface::PanData& data)
{
	if(m_usingFollowCamera)
	{
		m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPan_End(data);
	}
    else
    {
        GlobeCameraExampleBase::Event_TouchPan_End(data);
    }
}

void RouteSimulationExample::CreateAndBindUI()
{
	m_pRouteSimulationView = m_routeSimulationExampleViewFactory.CreateRouteSimulationExampleView();

	m_pRouteSimulationView->AddIncreaseSpeedHandler(m_increaseSpeedToggleHandler);
	m_pRouteSimulationView->AddDecreaseSpeedHandler(m_decreaseSpeedToggleHandler);
	m_pRouteSimulationView->AddFollowCameraDirectionChangedHandler(m_directionChangedHandler);
	m_pRouteSimulationView->AddFollowCameraToggledHandler(m_followCameraToggleHandler);
	m_pRouteSimulationView->AddRotateToFollowToggledHandler(m_rotateToFollowToggledHandler);
	m_pRouteSimulationView->AddSideOfRoadToDriveOnToggledHandler(m_roadSideChangedHandler);
}

}
