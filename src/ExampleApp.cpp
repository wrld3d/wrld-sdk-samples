// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ExampleApp.h"
#include "GlobeCameraTouchController.h"
#include "RenderCamera.h"
#include "GlobeCameraController.h"
#include "GlobeCameraInterestPointProvider.h"
#include "GlobeCameraController.h"
#include "CameraHelpers.h"
#include "LatLongAltitude.h"
#include "ScreenProperties.h"

// Modules
#include "MapModule.h"
#include "TerrainModelModule.h"

//example factories
#include "CameraTransitionExampleFactory.h"
#include "ControlCityThemeExampleFactory.h"
#include "DebugPrimitiveRenderingExampleFactory.h"
#include "DynamicText3DExampleFactory.h"
#include "EnvironmentFlatteningExampleFactory.h"
#include "EnvironmentNotifierExampleFactory.h"
#include "FileIOExampleFactory.h"
#include "LoadModelExampleFactory.h"
#include "ModifiedRenderingExampleFactory.h"
#include "NavigationGraphExampleFactory.h"
#include "Pick3DObjectExampleFactory.h"
#include "PinOverModelExampleFactory.h"
#include "PinsExampleFactory.h"
#include "PODAnimationExampleFactory.h"
#include "RenderToTextureExampleFactory.h"
#include "ResourceSpatialQueryExampleFactory.h"
#include "RouteDrawingExampleFactory.h"
#include "RouteSimulationAnimationExampleFactory.h"
#include "RouteThicknessPolicyExampleFactory.h"
#include "ScreenPickExampleFactory.h"
#include "ScreenUnprojectExampleFactory.h"
#include "SingleCityExampleFactory.h"
#include "ToggleTrafficExampleFactory.h"
#include "TrafficCongestionExampleFactory.h"
#include "WebRequestExampleFactory.h"
#include "CameraSplineExampleFactory.h"
#include "ReadHeadingExampleFactory.h"

ExampleApp::ExampleApp(Eegeo::EegeoWorld* pWorld,
                       Examples::ExampleController& exampleController)
	: m_pGlobeCameraController(NULL)
	, m_pCameraTouchController(NULL)
	, m_pWorld(pWorld)
	, m_exampleController(exampleController)
    , m_pActiveCamera(NULL)
{
	Eegeo::EegeoWorld& eegeoWorld = *pWorld;

	Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();

	m_pCameraTouchController = new Eegeo::Camera::GlobeCamera::GlobeCameraTouchController(touchControllerConfig);

	const bool useLowSpecSettings = false;
	Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration globeCameraControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration::CreateDefault(useLowSpecSettings);

    Eegeo::Modules::Map::MapModule& mapModule = eegeoWorld.GetMapModule();
    Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = eegeoWorld.GetTerrainModelModule();
    
	m_pGlobeCameraController = new Eegeo::Camera::GlobeCamera::GlobeCameraController(terrainModelModule.GetTerrainHeightProvider(),
	        mapModule.GetEnvironmentFlatteningService(),
	        mapModule.GetResourceCeilingProvider(),
	        *m_pCameraTouchController,
	        globeCameraControllerConfig);
    
    m_pActiveCamera = m_pGlobeCameraController->GetCamera();

    // override default configuration to enable two-finger pan gesture to control additional camera pitch
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchSettings touchSettings = m_pGlobeCameraController->GetTouchSettings();
    touchSettings.TiltEnabled = true;
    m_pGlobeCameraController->SetTouchSettings(touchSettings);

    const Eegeo::Rendering::ScreenProperties& screenProperties = eegeoWorld.GetScreenProperties();
	Eegeo::Camera::RenderCamera* renderCamera = m_pGlobeCameraController->GetCamera();
	renderCamera->SetViewport(0.f, 0.f, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());

	float interestPointLatitudeDegrees = 37.7858f;
	float interestPointLongitudeDegrees = -122.401f;
	float interestPointAltitudeMeters = 2.7;

	Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude::FromDegrees(interestPointLatitudeDegrees,
	        interestPointLongitudeDegrees,
	        interestPointAltitudeMeters);

	float cameraControllerOrientationDegrees = 0.0f;
	float cameraControllerDistanceFromInterestPointMeters = 1781.0f;

	Eegeo::Space::EcefTangentBasis cameraInterestBasis;
	Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(location.ToECEF(), cameraControllerOrientationDegrees, cameraInterestBasis);

	m_pGlobeCameraController->SetView(cameraInterestBasis, cameraControllerDistanceFromInterestPointMeters);

	//register all generic examples
    m_exampleController.RegisterCameraExample<Examples::CameraSplineExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::CameraTransitionExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ControlCityThemeExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::DebugPrimitiveRenderingExampleFactory>(*m_pGlobeCameraController);
    // TODO: Completely remove DebugSphere example as we should be using DebugRenderer now
	//m_exampleController.RegisterCameraExample<Examples::DebugSphereExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::DynamicText3DExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::EnvironmentFlatteningExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::EnvironmentNotifierExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::FileIOExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::LoadModelExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ModifiedRenderingExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::NavigationGraphExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::Pick3DObjectExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::PinsExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::PinOverModelExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::PODAnimationExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ReadHeadingExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::RenderToTextureExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ResourceSpatialQueryExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::RouteDrawingExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::RouteSimulationAnimationExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::RouteThicknessPolicyExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ScreenPickExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ScreenUnprojectExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::SingleCityExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::ToggleTrafficExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::TrafficCongestionExampleFactory>(*m_pGlobeCameraController);
	m_exampleController.RegisterCameraExample<Examples::WebRequestExampleFactory>(*m_pGlobeCameraController);
}

ExampleApp::~ExampleApp()
{
	delete m_pGlobeCameraController;
	delete m_pCameraTouchController;
}

void ExampleApp::OnPause()
{
	Eegeo::EegeoWorld& eegeoWorld = World();
	eegeoWorld.OnPause();
}

void ExampleApp::OnResume()
{
	Eegeo::EegeoWorld& eegeoWorld = World();
	eegeoWorld.OnResume();
}

void ExampleApp::Update (float dt)
{
	Eegeo::EegeoWorld& eegeoWorld = World();
    
    // Get active camera for current example
    // Draw and update with this camera.
    m_pActiveCamera = &m_exampleController.GetCurrentActiveCamera();

	eegeoWorld.EarlyUpdate(dt);
	m_exampleController.EarlyUpdate(dt, *m_pGlobeCameraController, *m_pCameraTouchController);

	eegeoWorld.Update(dt, *m_pActiveCamera, m_pGlobeCameraController->GetEcefInterestPoint());
    m_exampleController.Update(dt);
}

void ExampleApp::Draw (float dt)
{
	m_exampleController.PreWorldDraw();
	World().Draw(*m_pActiveCamera);
    m_exampleController.Draw();
}

void ExampleApp::Event_TouchRotate(const AppInterface::RotateData& data)
{
	if(World().Initialising())
	{
		return;
	}

	if(!m_exampleController.Event_TouchRotate(data))
	{
		m_pCameraTouchController->Event_TouchRotate(data);
	}
}

void ExampleApp::Event_TouchRotate_Start(const AppInterface::RotateData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchRotate_Start(data))
	{
		m_pCameraTouchController->Event_TouchRotate_Start(data);
	}
}

void ExampleApp::Event_TouchRotate_End(const AppInterface::RotateData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchRotate_End(data))
	{
		m_pCameraTouchController->Event_TouchRotate_End(data);
	}
}

void ExampleApp::Event_TouchPinch(const AppInterface::PinchData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchPinch(data))
	{
		m_pCameraTouchController->Event_TouchPinch(data);
	}
}

void ExampleApp::Event_TouchPinch_Start(const AppInterface::PinchData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchPinch_Start(data))
	{
		m_pCameraTouchController->Event_TouchPinch_Start(data);
	}
}

void ExampleApp::Event_TouchPinch_End(const AppInterface::PinchData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchPinch_End(data))
	{
		m_pCameraTouchController->Event_TouchPinch_End(data);
	}
}

void ExampleApp::Event_TouchPan(const AppInterface::PanData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchPan(data))
	{
		m_pCameraTouchController->Event_TouchPan(data);
	}
}

void ExampleApp::Event_TouchPan_Start(const AppInterface::PanData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchPan_Start(data))
	{
		m_pCameraTouchController->Event_TouchPan_Start(data);
	}
}

void ExampleApp::Event_TouchPan_End(const AppInterface::PanData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchPan_End(data))
	{
		m_pCameraTouchController->Event_TouchPan_End(data);
	}
}

void ExampleApp::Event_TouchTap(const AppInterface::TapData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchTap(data))
	{
		m_pCameraTouchController->Event_TouchTap(data);
	}
}

void ExampleApp::Event_TouchDoubleTap(const AppInterface::TapData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchDoubleTap(data))
	{
		m_pCameraTouchController->Event_TouchDoubleTap(data);
	}
}

void ExampleApp::Event_TouchDown(const AppInterface::TouchData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchDown(data))
	{
		m_pCameraTouchController->Event_TouchDown(data);
	}
}

void ExampleApp::Event_TouchMove(const AppInterface::TouchData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchMove(data))
	{
		m_pCameraTouchController->Event_TouchMove(data);
	}
}

void ExampleApp::Event_TouchUp(const AppInterface::TouchData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	if(!m_exampleController.Event_TouchUp(data))
	{
		m_pCameraTouchController->Event_TouchUp(data);
	}
}

