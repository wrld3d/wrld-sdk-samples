// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppHost.h"
#include "LatLongAltitude.h"
#include "EegeoWorld.h"
#include "AppInterface.h"
#include "JpegLoader.h"
#include "EffectHandler.h"
#include "SearchServiceCredentials.h"
#include "AndroidThreadHelper.h"
#include "GlobeCameraController.h"
#include "RenderCamera.h"
#include "CameraHelpers.h"
#include "PlatformConfig.h"
#include "AndroidPlatformConfigBuilder.h"
#include "AndroidLocationService.h"
#include "RouteMatchingExampleFactory.h"
#include "RouteSimulationExampleFactory.h"
#include "JavaHudCrossThreadCommunicationExampleFactory.h"
#include "PinsWithAttachedJavaUIExampleFactory.h"
#include "PositionJavaPinButtonExampleFactory.h"
#include "ExampleCameraJumpController.h"
#include "ShowJavaPlaceJumpUIExampleFactory.h"
#include "AndroidPlatformAbstractionModule.h"
#include "ScreenProperties.h"
#include "BuildingFootprintsModule.h"
#include "CollisionVisualizationModule.h"

namespace
{
    Eegeo::Modules::BuildingFootprintsModule* CreateBuildingFootprintsModule(Eegeo::EegeoWorld& world, const Eegeo::Modules::CollisionVisualizationModule& collisionVisualizationModule)
    {
        const Eegeo::BuildingFootprints::BuildingFootprintSelectionControllerConfig& buildingFootprintSelectionControllerConfig = Eegeo::Modules::BuildingFootprintsModule::MakeDefaultConfig();

        const Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = world.GetPlatformAbstractionModule();
        const Eegeo::Modules::Core::RenderingModule& renderingModule = world.GetRenderingModule();
        const Eegeo::Modules::Map::MapModule& mapModule = world.GetMapModule();
        const Eegeo::Modules::Map::Layers::BuildingStreamingModule& buildingStreamingModule = mapModule.GetBuildingStreamingModule();
        const Eegeo::Modules::Map::CoverageTreeModule& coverageTreeModule = mapModule.GetCoverageTreeModule();

        Eegeo::Modules::BuildingFootprintsModule* pBuildingFootprintsModule =
        Eegeo::Modules::BuildingFootprintsModule::Create(platformAbstractionModule,
                                                         renderingModule,
                                                         collisionVisualizationModule,
                                                         buildingStreamingModule,
                                                         coverageTreeModule,
                                                         buildingFootprintSelectionControllerConfig);
        return pBuildingFootprintsModule;
    }

    Eegeo::Modules::CollisionVisualizationModule* CreateCollisionVisualizationModule(Eegeo::EegeoWorld& world)
    {
        const Eegeo::CollisionVisualization::MaterialSelectionControllerConfig& materialSelectionControllerConfig = Eegeo::Modules::CollisionVisualizationModule::MakeDefaultConfig();


        const Eegeo::Modules::Core::RenderingModule& renderingModule = world.GetRenderingModule();
        const Eegeo::Modules::Map::MapModule& mapModule = world.GetMapModule();

        Eegeo::Modules::CollisionVisualizationModule* pCollisionVisualizationModule = Eegeo::Modules::CollisionVisualizationModule::Create(renderingModule, mapModule, materialSelectionControllerConfig);
        return pCollisionVisualizationModule;
    }
}

using namespace Eegeo::Android;
using namespace Eegeo::Android::Input;

AppHost::AppHost(
    const std::string& apiKey,
    AndroidNativeState& nativeState,
    float displayWidth,
    float displayHeight,
    EGLDisplay display,
    EGLSurface shareSurface,
    EGLContext resourceBuildShareContext
)
	: m_isPaused(false)
	,m_pJpegLoader(NULL)
	,m_pAndroidLocationService(NULL)
	,m_pWorld(NULL)
	,m_nativeState(nativeState)
	,m_androidInputBoxFactory(&nativeState)
	,m_androidKeyboardInputFactory(&nativeState, m_inputHandler)
	,m_androidAlertBoxFactory(&nativeState)
	,m_androidNativeUIFactories(m_androidAlertBoxFactory, m_androidInputBoxFactory, m_androidKeyboardInputFactory)
	,m_pApp(NULL)
	,m_pAndroidExampleControllerView(NULL)
	,m_pAndroidRouteMatchingExampleViewFactory(NULL)
	,m_pAndroidRouteSimulationExampleViewFactory(NULL)
	,m_pInputProcessor(NULL)
	,m_pAndroidPlatformAbstractionModule(NULL)
	,m_pCollisionVisualizationModule(NULL)
	,m_pBuildingFootprintsModule(NULL)
{
	Eegeo::TtyHandler::TtyEnabled = false;
	Eegeo::AssertHandler::BreakOnAssert = true;

	Eegeo_ASSERT(resourceBuildShareContext != EGL_NO_CONTEXT);

	m_pAndroidLocationService = new AndroidLocationService(&nativeState);

	Eegeo::Rendering::ScreenProperties screenProperties(Eegeo::Rendering::ScreenProperties::Make(displayWidth, displayHeight, 1.f, nativeState.deviceDpi));

	std::set<std::string> customApplicationAssetDirectories;
	customApplicationAssetDirectories.insert("heatmap_example");
	customApplicationAssetDirectories.insert("load_model_example");
	customApplicationAssetDirectories.insert("mesh_example");
	customApplicationAssetDirectories.insert("pin_over_model_example");
	customApplicationAssetDirectories.insert("pins_example");
	customApplicationAssetDirectories.insert("pins_with_attached_java_ui_example");
	customApplicationAssetDirectories.insert("pod_animation_example");
	customApplicationAssetDirectories.insert("route_simulation_example");
	customApplicationAssetDirectories.insert("route_simulation_animation_example");

	m_pJpegLoader = new Eegeo::Helpers::Jpeg::JpegLoader();

	m_pAndroidPlatformAbstractionModule = new Eegeo::Android::AndroidPlatformAbstractionModule(nativeState,
																							   *m_pJpegLoader,
																							   display,
																							   resourceBuildShareContext,
																							   shareSurface,
																							   apiKey,
																							   customApplicationAssetDirectories);

	Eegeo::EffectHandler::Initialise();

	const Eegeo::EnvironmentCharacterSet::Type environmentCharacterSet = Eegeo::EnvironmentCharacterSet::Latin;
	std::string deviceModel = std::string(nativeState.deviceModel, strlen(nativeState.deviceModel));
	Eegeo::Config::PlatformConfig config = Eegeo::Android::AndroidPlatformConfigBuilder(deviceModel).Build();

	config.OptionsConfig.GenerateCollisionForAllResources = true;
	config.CityThemesConfig.EmbeddedThemeManifestFile = "embedded_manifest.txt";
	config.CityThemesConfig.EmbeddedThemeTexturePath = "Textures";
	config.CityThemesConfig.EmbeddedThemeNameContains = "Summer";
	config.CityThemesConfig.EmbeddedThemeStateName = "DayDefault";

	m_pWorld = new Eegeo::EegeoWorld(
	    apiKey,
	    *m_pAndroidPlatformAbstractionModule,
	    *m_pJpegLoader,
	    screenProperties,
	    *m_pAndroidLocationService,
	    m_androidNativeUIFactories,
	    environmentCharacterSet,
	    config,
	    NULL);

    m_pCollisionVisualizationModule = CreateCollisionVisualizationModule(*m_pWorld);
    m_pBuildingFootprintsModule = CreateBuildingFootprintsModule(*m_pWorld, *m_pCollisionVisualizationModule);

	m_pInputProcessor = new Eegeo::Android::Input::AndroidInputProcessor(&m_inputHandler, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());

	ConfigureExamples(screenProperties);

	m_pAppInputDelegate = new AppInputDelegate(*m_pApp);
	m_inputHandler.AddDelegateInputHandler(m_pAppInputDelegate);
}

AppHost::~AppHost()
{
	m_inputHandler.RemoveDelegateInputHandler(m_pAppInputDelegate);

	delete m_pAppInputDelegate;
	m_pAppInputDelegate = NULL;

	delete m_pApp;
	m_pApp = NULL;

	DestroyExamples();

    delete m_pBuildingFootprintsModule;
    m_pBuildingFootprintsModule = NULL;

    delete m_pCollisionVisualizationModule;
    m_pCollisionVisualizationModule = NULL;

	delete m_pWorld;
	m_pWorld = NULL;

	Eegeo::EffectHandler::Reset();
	Eegeo::EffectHandler::Shutdown();

	delete m_pAndroidLocationService;
	m_pAndroidLocationService = NULL;

	delete m_pJpegLoader;
	m_pJpegLoader = NULL;

	delete m_pAndroidPlatformAbstractionModule;
	m_pAndroidPlatformAbstractionModule = NULL;
}

void AppHost::OnResume()
{
	m_pApp->OnResume();
}

void AppHost::OnPause()
{
	m_pApp->OnPause();
	m_pAndroidLocationService->StopListening();
}

void AppHost::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
{
    m_pApp->NotifyScreenPropertiesChanged(screenProperties);
}

void AppHost::SetSharedSurface(EGLSurface sharedSurface)
{
	m_pAndroidPlatformAbstractionModule->UpdateSurface(sharedSurface);
}

void AppHost::SetViewportOffset(float x, float y)
{
	m_inputHandler.SetViewportOffset(x, y);
}

void AppHost::HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event)
{
	m_pInputProcessor->HandleInput(event);
}

void AppHost::Update(float dt)
{
	m_pInputProcessor->Update(dt);
	m_pApp->Update(dt);
}

void AppHost::Draw(float dt)
{
	m_pApp->Draw(dt);
}

void AppHost::ConfigureExamples(const Eegeo::Rendering::ScreenProperties& screenProperties)
{
	m_pAndroidExampleControllerView = new Examples::AndroidExampleControllerView(m_nativeState);

	m_pApp = new ExampleApp(m_pWorld, *m_pAndroidExampleControllerView, screenProperties, *m_pCollisionVisualizationModule, *m_pBuildingFootprintsModule);

	RegisterAndroidSpecificExamples();

	m_pAndroidExampleControllerView->PopulateExampleList(m_pApp->GetExampleController().GetExampleNames());

	m_pApp->GetExampleController().ActivatePrevious();
}

void AppHost::RegisterAndroidSpecificExamples()
{
	m_pAndroidRouteMatchingExampleViewFactory = new Examples::AndroidRouteMatchingExampleViewFactory(
	    m_nativeState);

	m_pApp->GetExampleController().RegisterExample(new Examples::RouteMatchingExampleFactory(
	        *m_pWorld,
	        *m_pAndroidRouteMatchingExampleViewFactory,
	        m_pApp->GetDefaultCameraControllerFactory(),
	        m_pApp->GetTouchController()));

	m_pAndroidRouteSimulationExampleViewFactory = new Examples::AndroidRouteSimulationExampleViewFactory(
	    m_nativeState);

	Examples::ExampleController& exampleController = m_pApp->GetExampleController();
	exampleController.RegisterExample(new Examples::RouteSimulationExampleFactory(
	        *m_pWorld,
	        m_pApp->GetDefaultCameraControllerFactory(),
	        m_pApp->GetTouchController(),
	        m_pApp->GetScreenPropertiesProvider(),
	        *m_pAndroidRouteSimulationExampleViewFactory));

	exampleController.RegisterExample(new Examples::JavaHudCrossThreadCommunicationExampleFactory(
			*m_pWorld,
			m_nativeState,
			m_pApp->GetDefaultCameraControllerFactory(),
			m_pApp->GetTouchController()));

	exampleController.RegisterExample(new Examples::PinsWithAttachedJavaUIExampleFactory(
			*m_pWorld,
			m_nativeState,
			m_pApp->GetDefaultCameraControllerFactory(),
			m_pApp->GetTouchController(),
			m_pApp->GetScreenPropertiesProvider()));

	exampleController.RegisterExample(new Examples::PositionJavaPinButtonExampleFactory(
			*m_pWorld,
			m_nativeState,
			m_pApp->GetDefaultCameraControllerFactory(),
			m_pApp->GetTouchController()));

	exampleController.RegisterExample(new Examples::ShowJavaPlaceJumpUIExampleFactory(
			m_nativeState,
			m_pApp->GetDefaultCameraControllerFactory(),
			m_pApp->GetTouchController()));
}

void AppHost::DestroyExamples()
{
	delete m_pAndroidRouteMatchingExampleViewFactory;
	delete m_pAndroidRouteSimulationExampleViewFactory;

	delete m_pAndroidExampleControllerView;
}




