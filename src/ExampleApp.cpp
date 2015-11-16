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
#include "BuildingHighlightExampleFactory.h"
#include "CameraTransitionExampleFactory.h"
#include "ControlCityThemeExampleFactory.h"
#include "DebugPrimitiveRenderingExampleFactory.h"
#include "DynamicText3DExampleFactory.h"
#include "EnvironmentRayCasterExampleFactory.h"
#include "EnvironmentFlatteningExampleFactory.h"
#include "EnvironmentNotifierExampleFactory.h"
#include "FileIOExampleFactory.h"
#include "HeatmapExampleFactory.h"
#include "LoadModelExampleFactory.h"
#include "ModifiedRenderingExampleFactory.h"
#include "NavigationGraphExampleFactory.h"
#include "Pick3DObjectExampleFactory.h"
#include "PinOverModelExampleFactory.h"
#include "PinsExampleFactory.h"
#include "PODAnimationExampleFactory.h"
#include "PolyChartExampleFactory.h"
#include "RenderToTextureExampleFactory.h"
#include "ResourceSpatialQueryExampleFactory.h"
#include "RouteDrawingExampleFactory.h"
#include "RouteSimulationAnimationExampleFactory.h"
#include "RouteThicknessPolicyExampleFactory.h"
#include "ScreenPickExampleFactory.h"
#include "ScreenUnprojectExampleFactory.h"
#include "SingleCityExampleFactory.h"
#include "StencilAreaExampleFactory.h"
#include "ToggleTrafficExampleFactory.h"
#include "TrafficCongestionExampleFactory.h"
#include "WebRequestExampleFactory.h"
#include "CameraSplineExampleFactory.h"
#include "ReadHeadingExampleFactory.h"
#include "FireworksExampleFactory.h"
#include "MeshExampleFactory.h"
#include "GeofenceExampleFactory.h"
#include "BuildingSelectionExampleFactory.h"
#include "RemoveMapLayerExampleFactory.h"

namespace
{
    Eegeo::Rendering::LoadingScreen* CreateLoadingScreen(const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                         const Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                         const Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule)
    {
        Eegeo::Rendering::LoadingScreenConfig loadingScreenConfig;
        loadingScreenConfig.loadingBarBackgroundColor = Eegeo::v4(0.45f, 0.7f, 1.0f, 1.0f);
        loadingScreenConfig.fadeOutDurationSeconds = 1.5f;
        loadingScreenConfig.screenWidth = screenProperties.GetScreenWidth();
        loadingScreenConfig.screenHeight = screenProperties.GetScreenHeight();
        loadingScreenConfig.backgroundColor = Eegeo::v4(132.f/255.f, 203.f/255.f, 235.f/255.f, 1.f);
        loadingScreenConfig.loadingBarOffset = Eegeo::v2(0.5f, 0.1f);
        loadingScreenConfig.layout = Eegeo::Rendering::LoadingScreenLayout::Centred;
       
        
        Eegeo::Rendering::LoadingScreen* loadingScreen = Eegeo::Rendering::LoadingScreen::Create(
            "SplashScreen-1024x768.png",
            loadingScreenConfig,
            renderingModule.GetShaderIdGenerator(),
            renderingModule.GetMaterialIdGenerator(),
            renderingModule.GetGlBufferPool(),
            renderingModule.GetVertexLayoutPool(),
            renderingModule.GetVertexBindingPool(),
            platformAbstractionModule.GetTextureFileLoader());
            
        return loadingScreen;
    }
}




ExampleApp::ExampleApp(Eegeo::EegeoWorld* pWorld,
                       Examples::IExampleControllerView& view,
                       const Eegeo::Rendering::ScreenProperties& screenProperties,
                       Eegeo::Modules::CollisionVisualizationModule& collisionVisualizationModule,
                       Eegeo::Modules::BuildingFootprintsModule& buildingFootprintsModule)
	: m_pCameraControllerFactory(NULL)
	, m_pCameraTouchController(NULL)
	, m_pWorld(pWorld)
    , m_pLoadingScreen(NULL)
	, m_pExampleController(NULL)
    , m_screenPropertiesProvider(screenProperties)
{
	Eegeo::EegeoWorld& eegeoWorld = *pWorld;

	Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();

	m_pCameraTouchController = new Eegeo::Camera::GlobeCamera::GlobeCameraTouchController(touchControllerConfig, m_screenPropertiesProvider.GetScreenProperties());

	const bool useLowSpecSettings = false;
	Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration globeCameraControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration::CreateDefault(useLowSpecSettings);

    Eegeo::Modules::Map::MapModule& mapModule = eegeoWorld.GetMapModule();
    Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = eegeoWorld.GetTerrainModelModule();
    
    const bool twoFingerPanTiltEnabled = true;
    const float interestPointLatitudeDegrees = 37.7858f;
    const float interestPointLongitudeDegrees = -122.401f;
    const float interestPointAltitudeMeters = 2.7f;
    const float cameraControllerOrientationDegrees = 0.0f;
    const float cameraControllerDistanceFromInterestPointMeters = 1781.0f;
    
    m_pCameraControllerFactory = new Examples::DefaultCameraControllerFactory(
                                                                    terrainModelModule,
                                                                    mapModule,
                                                                    *m_pCameraTouchController,
                                                                    m_screenPropertiesProvider,
                                                                    globeCameraControllerConfig,
                                                                    twoFingerPanTiltEnabled,
                                                                    interestPointLatitudeDegrees,
                                                                    interestPointLongitudeDegrees,
                                                                    interestPointAltitudeMeters,
                                                                    cameraControllerOrientationDegrees,
                                                                    cameraControllerDistanceFromInterestPointMeters);
    
    m_pLoadingScreen = CreateLoadingScreen(screenProperties, eegeoWorld.GetRenderingModule(), eegeoWorld.GetPlatformAbstractionModule());
    
    m_pExampleController = new Examples::ExampleController(*m_pWorld,
                                                           view,
                                                           *m_pCameraControllerFactory,
                                                           *m_pCameraTouchController,
                                                           m_screenPropertiesProvider);

	//register all generic examples

    m_pExampleController->RegisterCameraExample<Examples::BuildingHighlightExampleFactory>();
    m_pExampleController->RegisterExample(Eegeo_NEW(Examples::BuildingSelectionExampleFactory)(World(),
                                                                                               *m_pCameraControllerFactory,
                                                                                               *m_pCameraTouchController,
                                                                                               collisionVisualizationModule,
                                                                                               buildingFootprintsModule));
    m_pExampleController->RegisterScreenPropertiesProviderExample<Examples::CameraSplineExampleFactory>(m_screenPropertiesProvider);
    m_pExampleController->RegisterCameraExample<Examples::CameraTransitionExampleFactory>();
    m_pExampleController->RegisterCameraExample<Examples::ControlCityThemeExampleFactory>();
    m_pExampleController->RegisterCameraExample<Examples::DebugPrimitiveRenderingExampleFactory>();
    // TODO: Completely remove DebugSphere example as we should be using DebugRenderer now
	//m_pExampleController->RegisterCameraExample<Examples::DebugSphereExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::DynamicText3DExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::EnvironmentFlatteningExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::EnvironmentNotifierExampleFactory>();
    m_pExampleController->RegisterCameraExample<Examples::EnvironmentRayCasterExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::FileIOExampleFactory>();
    m_pExampleController->RegisterCameraExample<Examples::FireworksExampleFactory>();
    m_pExampleController->RegisterCameraExample<Examples::GeofenceExampleFactory>();
    m_pExampleController->RegisterCameraExample<Examples::HeatmapExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::LoadModelExampleFactory>();
    m_pExampleController->RegisterCameraExample<Examples::MeshExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::ModifiedRenderingExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::NavigationGraphExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::Pick3DObjectExampleFactory>();
	m_pExampleController->RegisterCameraControllerScreenPropertiesProviderExample<Examples::PinsExampleFactory>(m_screenPropertiesProvider);
	m_pExampleController->RegisterCameraControllerScreenPropertiesProviderExample<Examples::PinOverModelExampleFactory>(m_screenPropertiesProvider  );
	m_pExampleController->RegisterCameraExample<Examples::PODAnimationExampleFactory>();
    m_pExampleController->RegisterCameraExample<Examples::PolyChartExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::ReadHeadingExampleFactory>();
    m_pExampleController->RegisterCameraExample<Examples::RemoveMapLayerExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::ResourceSpatialQueryExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::RouteDrawingExampleFactory>();
	m_pExampleController->RegisterCameraControllerScreenPropertiesProviderExample<Examples::RouteSimulationAnimationExampleFactory>(m_screenPropertiesProvider);
	m_pExampleController->RegisterCameraExample<Examples::RouteThicknessPolicyExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::ScreenPickExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::ScreenUnprojectExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::SingleCityExampleFactory>();
    m_pExampleController->RegisterCameraExample<Examples::StencilAreaExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::ToggleTrafficExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::TrafficCongestionExampleFactory>();
	m_pExampleController->RegisterCameraExample<Examples::WebRequestExampleFactory>();
    m_pExampleController->RegisterCameraControllerScreenPropertiesProviderExample<Examples::RenderToTextureExampleFactory>(m_screenPropertiesProvider);
}

ExampleApp::~ExampleApp()
{
	delete m_pCameraTouchController;
    delete m_pLoadingScreen;
    delete m_pExampleController;
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
    
    m_pCameraTouchController->Update(dt);

	eegeoWorld.EarlyUpdate(dt);
    
	m_pExampleController->EarlyUpdate(dt);
    
    Eegeo::Camera::CameraState cameraState(m_pExampleController->GetCurrentCameraState());
    Eegeo::Streaming::IStreamingVolume& streamingVolume(m_pExampleController->GetCurrentStreamingVolume());
    
    Eegeo::EegeoUpdateParameters updateParameters(dt,
                                                  cameraState.LocationEcef(),
                                                  cameraState.InterestPointEcef(),
                                                  cameraState.ViewMatrix(),
                                                  cameraState.ProjectionMatrix(),
                                                  streamingVolume,
                                                  m_screenPropertiesProvider.GetScreenProperties());
    
	eegeoWorld.Update(updateParameters);
    
    m_pExampleController->Update(dt);
    
    UpdateLoadingScreen(dt);
}

void ExampleApp::Draw (float dt)
{
    m_pExampleController->PreWorldDraw();
    
    Eegeo::EegeoWorld& eegeoWorld = World();
    
    Eegeo::Camera::CameraState cameraState(m_pExampleController->GetCurrentCameraState());
    
    Eegeo::EegeoDrawParameters drawParameters(cameraState.LocationEcef(),
                                              cameraState.InterestPointEcef(),
                                              cameraState.ViewMatrix(),
                                              cameraState.ProjectionMatrix(),
                                              m_screenPropertiesProvider.GetScreenProperties());
    
    eegeoWorld.Draw(drawParameters);
    
    m_pExampleController->Draw();
    
    if (m_pLoadingScreen != NULL)
    {
        m_pLoadingScreen->Draw();
    }
}

void ExampleApp::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
{
    m_screenPropertiesProvider.NotifyScreenPropertiesChanged(screenProperties);
    
    if (m_pLoadingScreen != NULL)
    {
        m_pLoadingScreen->NotifyScreenDimensionsChanged(screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());
    }
    
    m_pExampleController->NotifyScreenPropertiesChanged(screenProperties);
}

void ExampleApp::UpdateLoadingScreen(float dt)
{
    if (m_pLoadingScreen == NULL)
        return;
    
    Eegeo::EegeoWorld& eegeoWorld = World();
    
    if (!eegeoWorld.Initialising() && !m_pLoadingScreen->IsDismissed())
    {
        m_pLoadingScreen->Dismiss();
        Eegeo::TtyHandler::TtyEnabled = true;
    }
    
    m_pLoadingScreen->SetProgress(eegeoWorld.GetInitialisationProgress());
    m_pLoadingScreen->Update(dt);
    
    if (!m_pLoadingScreen->IsVisible())
    {
        Eegeo_DELETE m_pLoadingScreen;
        m_pLoadingScreen = NULL;
    }
}

void ExampleApp::Event_TouchRotate(const AppInterface::RotateData& data)
{
	if(World().Initialising())
	{
		return;
	}

	m_pExampleController->Event_TouchRotate(data);

}

void ExampleApp::Event_TouchRotate_Start(const AppInterface::RotateData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchRotate_Start(data);
}

void ExampleApp::Event_TouchRotate_End(const AppInterface::RotateData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchRotate_End(data);
}

void ExampleApp::Event_TouchPinch(const AppInterface::PinchData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchPinch(data);
}

void ExampleApp::Event_TouchPinch_Start(const AppInterface::PinchData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchPinch_Start(data);
}

void ExampleApp::Event_TouchPinch_End(const AppInterface::PinchData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchPinch_End(data);
}

void ExampleApp::Event_TouchPan(const AppInterface::PanData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchPan(data);
}

void ExampleApp::Event_TouchPan_Start(const AppInterface::PanData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchPan_Start(data);
}

void ExampleApp::Event_TouchPan_End(const AppInterface::PanData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchPan_End(data);
}

void ExampleApp::Event_TouchTap(const AppInterface::TapData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchTap(data);
}

void ExampleApp::Event_TouchDoubleTap(const AppInterface::TapData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchDoubleTap(data);
}

void ExampleApp::Event_TouchDown(const AppInterface::TouchData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchDown(data);
}

void ExampleApp::Event_TouchMove(const AppInterface::TouchData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchMove(data);
}

void ExampleApp::Event_TouchUp(const AppInterface::TouchData& data)
{
    if(World().Initialising())
	{
		return;
	}
    
	m_pExampleController->Event_TouchUp(data);
}

