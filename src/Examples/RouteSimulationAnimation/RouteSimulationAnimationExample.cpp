// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteSimulationAnimationExample.h"
#include "VectorMath.h"
#include "GlobeCameraTouchControllerConfiguration.h"
#include "GlobeCameraTouchController.h"
#include "TransformHelpers.h"
#include "RenderCamera.h"
#include "ScreenProperties.h"
#include "SceneModelLoader.h"
#include "SceneModel.h"
#include "SceneModelAnimator.h"

using namespace Eegeo;
using namespace Eegeo::Routes;
using namespace Eegeo::Routes::Simulation;
using namespace Eegeo::Routes::Simulation::View;
using namespace Eegeo::Routes::Simulation::Camera;

namespace Examples
{
    RouteSimulationAnimationExample::RouteSimulationAnimationExample(RouteService& routeService,
                                                                     RouteSimulationService& routeSimulationService,
                                                                     RouteSimulationViewService& routeSimulationViewService,
                                                                     Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                                                     RouteSimulationGlobeCameraControllerFactory& routeSimulationGlobeCameraControllerFactory,
                                                                     const IScreenPropertiesProvider& screenPropertiesProvider,
                                                                     EegeoWorld& world)
    :m_routeService(routeService)
    ,m_routeSimulationService(routeSimulationService)
	,m_routeSimulationViewService(routeSimulationViewService)
    ,m_sceneModelLoader(sceneModelLoader)
	,m_routeSimulationGlobeCameraControllerFactory(routeSimulationGlobeCameraControllerFactory)
	,m_world(world)
	,m_initialised(false)
	,m_pRoute(NULL)
	,m_pModel(NULL)
    ,m_pSceneModelAnimator(NULL)
	,m_pRouteSimulationSession(NULL)
	,m_pViewBindingForCameraSession(NULL)
	,m_pRouteSessionFollowCameraController(NULL)
{
    RouteSimulationGlobeCameraControllerConfig routeSimCameraConfig = RouteSimulationGlobeCameraControllerConfig::CreateDefault();
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchConfiguration = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
    const Eegeo::Rendering::ScreenProperties& screenProperties = screenPropertiesProvider.GetScreenProperties();
    m_pRouteSessionFollowCameraController = m_routeSimulationGlobeCameraControllerFactory.Create(false, touchConfiguration, routeSimCameraConfig, screenProperties);
}

RouteSimulationAnimationExample::~RouteSimulationAnimationExample()
{
}

void RouteSimulationAnimationExample::Initialise()
{
	//Load a model containing the node that will be bound to our route simulation session. For
	//a detailed explation see http://www.eegeo.com/developers/documentation/loading_rendering_models
	//or see LoadModelExample.cpp.
	m_pModel = LoadCharacterModel();
    
    // Initialise animation.
    const int framesPerSecond = 30;
    m_pSceneModelAnimator = new Eegeo::Rendering::SceneModels::SceneModelAnimator(*m_pModel, framesPerSecond);
    m_pSceneModelAnimator->Play();

	//Build the route - see RouteDrawingExample.cpp for a detailed explanation of building routes, or
	//check out http://www.eegeo.com/developers/documentation/routes
	m_pRoute = BuildRoute();

	m_pRouteSimulationSession = m_routeSimulationService.BeginRouteSimulationSession(*m_pRoute);
    
    const float fovDegrees = 45.f;
    const float nearClipDistance = 10.f;
    const float farClipDistance = 10000.f;
    m_pRouteSessionFollowCameraController->SetProjection(Eegeo::Math::Deg2Rad(fovDegrees), nearClipDistance, farClipDistance);

	Eegeo::m44 transform;
	CalculateTransform(transform);

	m_pViewBindingForCameraSession = m_routeSimulationViewService.CreateBinding(*m_pRouteSimulationSession, m_pModel, transform);

	m_pRouteSimulationSession->StartPlaybackFromBeginning();

    m_pRouteSessionFollowCameraController->SetTiltEnabled(true);
    m_pRouteSessionFollowCameraController->SetView(37.7858, -122.401, 0, 781.0f);
	m_pRouteSessionFollowCameraController->StartFollowingSession(m_pRouteSimulationSession);

}

void RouteSimulationAnimationExample::EarlyUpdate(float dt)
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

	m_pRouteSessionFollowCameraController->Update(dt);
    m_pViewBindingForCameraSession->Update();
}

void RouteSimulationAnimationExample::Update(float dt)
{
	//Defer initialisation until the loading state is over.
	if(!m_initialised)
	{
		return;
	}

	if(m_pRouteSimulationSession->IsRouteCompleted())
	{
		m_pRouteSimulationSession->TogglePlaybackDirection();
		m_pRouteSimulationSession->Unpause();
	}

	Eegeo_TTY("%f metres from start of route. %f percent.\n", m_pRouteSimulationSession->GetDistanceFromStartInMetres(),(m_pRouteSimulationSession->GetDistanceFromStartInMetres() / m_pRoute->GetLength())*100.0f);

	Eegeo::m44 transform;
	CalculateTransform(transform);
	m_pViewBindingForCameraSession->SetModelTransform(transform);

	//Update animation
    m_pSceneModelAnimator->Update(dt);
}

void RouteSimulationAnimationExample::Suspend()
{
	if (m_pRouteSessionFollowCameraController)
	{
		m_pRouteSessionFollowCameraController->StopFollowingSession();
	}

	m_routeSimulationViewService.DestroyBinding(m_pViewBindingForCameraSession);

	m_routeSimulationService.EndRouteSimulationSession(m_pRouteSimulationSession);

	m_pRouteSimulationSession = NULL;

	m_routeService.DestroyRoute(m_pRoute);
	m_pRoute = NULL;

    delete m_pSceneModelAnimator;
    m_pSceneModelAnimator = NULL;
    
	delete m_pModel;
	m_pModel = NULL;

	delete m_pRouteSessionFollowCameraController;
	m_pRouteSessionFollowCameraController = NULL;
    
	m_initialised = false;
}
    
void RouteSimulationAnimationExample::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
{
    m_pRouteSessionFollowCameraController->UpdateScreenProperties(screenProperties);
}

Route* RouteSimulationAnimationExample::BuildRoute()
{
	const float halfWidth = 5.f;

	// 0.00185 is a factor that works well for the animation
	// speed of this model
	const float routeSpeedMetersPerSecond = 30.f;

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

Eegeo::Rendering::SceneModels::SceneModel* RouteSimulationAnimationExample::LoadCharacterModel() const
{
    Eegeo::Rendering::SceneModels::SceneModel* pModel = m_sceneModelLoader.LoadPOD("route_simulation_animation_example/BoxCharacter.pod");

	return pModel;
}

void RouteSimulationAnimationExample::CalculateTransform(Eegeo::m44& transform)
{
	const float scaleModifier = 100.f;
	const float minimumScale = 3.f;
    
    const Eegeo::dv3& position = m_pRouteSimulationSession->GetCurrentPositionEcef();
    float scaleAsFunctionOfAltitude =
    Eegeo::Helpers::TransformHelpers::ComputeModelScaleForConstantScreenSize(m_pRouteSessionFollowCameraController->GetRenderCamera(),
                                                                             position) / scaleModifier;
    
    
	Eegeo::m44 scale, rotation;
	scale.Scale(Eegeo::Max(scaleAsFunctionOfAltitude, minimumScale));
	rotation.RotateY(static_cast<float>(M_PI));
	m44::Mul(transform, scale, rotation);

}
    
Eegeo::Camera::CameraState RouteSimulationAnimationExample::GetCurrentCameraState() const
{
    return m_pRouteSessionFollowCameraController->GetCameraState();
}

void RouteSimulationAnimationExample::Event_TouchRotate(const AppInterface::RotateData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchRotate(data);
}

void RouteSimulationAnimationExample::Event_TouchRotate_Start(const AppInterface::RotateData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchRotate_Start(data);
}

void RouteSimulationAnimationExample::Event_TouchRotate_End(const AppInterface::RotateData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchRotate_End(data);
}

void RouteSimulationAnimationExample::Event_TouchPinch(const AppInterface::PinchData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPinch(data);
}

void RouteSimulationAnimationExample::Event_TouchPinch_Start(const AppInterface::PinchData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPinch_Start(data);
}

void RouteSimulationAnimationExample::Event_TouchPinch_End(const AppInterface::PinchData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPinch_End(data);
}

void RouteSimulationAnimationExample::Event_TouchPan(const AppInterface::PanData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPan(data);
}

void RouteSimulationAnimationExample::Event_TouchPan_Start(const AppInterface::PanData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPan_Start(data);
}

void RouteSimulationAnimationExample::Event_TouchPan_End(const AppInterface::PanData& data)
{
	m_pRouteSessionFollowCameraController->GetTouchController().Event_TouchPan_End(data);
}

}
