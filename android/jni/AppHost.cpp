// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppHost.h"
#include "AndroidWebRequestService.hpp"
#include "LatLongAltitude.h"
#include "EegeoWorld.h"
#include "AppInterface.h"
#include "JpegLoader.h"
#include "Blitter.h"
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
	:m_pBlitter(NULL)
    ,m_pJpegLoader(NULL)
	,m_pScreenProperties(NULL)
	,m_pAndroidLocationService(NULL)
	,m_pWorld(NULL)
	,m_androidInputBoxFactory(&nativeState)
	,m_androidKeyboardInputFactory(&nativeState, m_inputHandler)
	,m_androidAlertBoxFactory(&nativeState)
	,m_androidNativeUIFactories(m_androidAlertBoxFactory, m_androidInputBoxFactory, m_androidKeyboardInputFactory)
	,m_pApp(NULL)
	,m_pExampleController(NULL)
	,m_pInputProcessor(NULL)
	,m_nativeState(nativeState)
	,m_pAndroidPlatformAbstractionModule(NULL)
{
	Eegeo::TtyHandler::TtyEnabled = false;
	Eegeo::AssertHandler::BreakOnAssert = true;

	Eegeo_ASSERT(resourceBuildShareContext != EGL_NO_CONTEXT);

	m_pAndroidLocationService = new AndroidLocationService(&nativeState);

	m_pScreenProperties = new Eegeo::Rendering::ScreenProperties(displayWidth, displayHeight, 1.f, nativeState.deviceDpi);

	std::set<std::string> customApplicationAssetDirectories;
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
	m_pBlitter = new Eegeo::Blitter(1024 * 128, 1024 * 64, 1024 * 32, m_pScreenProperties->GetScreenWidth(), m_pScreenProperties->GetScreenHeight());
	m_pBlitter->Initialise();;

	const Eegeo::EnvironmentCharacterSet::Type environmentCharacterSet = Eegeo::EnvironmentCharacterSet::Latin;
	std::string deviceModel = std::string(nativeState.deviceModel, strlen(nativeState.deviceModel));
	Eegeo::Config::PlatformConfig config = Eegeo::Android::AndroidPlatformConfigBuilder(deviceModel).Build();

	m_pWorld = new Eegeo::EegeoWorld(
	    apiKey,
	    *m_pAndroidPlatformAbstractionModule,
	    *m_pJpegLoader,
	    *m_pScreenProperties,
	    *m_pAndroidLocationService,
	    *m_pBlitter,
	    m_androidNativeUIFactories,
	    environmentCharacterSet,
	    config,
	    NULL);

	m_pAndroidPlatformAbstractionModule->SetWebRequestServiceWorkPool(m_pWorld->GetWorkPool());
	m_pInputProcessor = new Eegeo::Android::Input::AndroidInputProcessor(&m_inputHandler, m_pScreenProperties->GetScreenWidth(), m_pScreenProperties->GetScreenHeight());

	ConfigureExamples();

	m_pAppInputDelegate = new AppInputDelegate(*m_pApp);
	m_inputHandler.AddDelegateInputHandler(m_pAppInputDelegate);
}

AppHost::~AppHost()
{
	m_inputHandler.RemoveDelegateInputHandler(m_pAppInputDelegate);

	delete m_pAppInputDelegate;
	m_pAppInputDelegate = NULL;

	DestroyExamples();

	delete m_pApp;
	m_pApp = NULL;

	delete m_pWorld;
	m_pWorld = NULL;

	Eegeo::EffectHandler::Reset();
	Eegeo::EffectHandler::Shutdown();
	m_pBlitter->Shutdown();
	delete m_pBlitter;
	m_pBlitter = NULL;

	delete m_pAndroidLocationService;
	m_pAndroidLocationService = NULL;

	delete m_pJpegLoader;
	m_pJpegLoader = NULL;

	delete m_pScreenProperties;
	m_pScreenProperties = NULL;

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

void AppHost::ConfigureExamples()
{
	m_pAndroidExampleControllerView = new Examples::AndroidExampleControllerView(m_nativeState);

	m_pExampleController = new Examples::ExampleController(*m_pWorld, *m_pAndroidExampleControllerView);
	m_pApp = new ExampleApp(m_pWorld, *m_pExampleController);

	RegisterAndroidSpecificExamples();

	m_pAndroidExampleControllerView->PopulateExampleList(m_pExampleController->GetExampleNames());

	m_pExampleController->ActivatePrevious();
}

void AppHost::RegisterAndroidSpecificExamples()
{
	m_pAndroidRouteMatchingExampleViewFactory = new Examples::AndroidRouteMatchingExampleViewFactory(
	    m_nativeState);

	m_pExampleController->RegisterExample(new Examples::RouteMatchingExampleFactory(
	        *m_pWorld,
	        *m_pAndroidRouteMatchingExampleViewFactory,
	        m_pApp->GetCameraController()));

	m_pAndroidRouteSimulationExampleViewFactory = new Examples::AndroidRouteSimulationExampleViewFactory(
	    m_nativeState);

	m_pExampleController->RegisterExample(new Examples::RouteSimulationExampleFactory(
	        *m_pWorld,
	        m_pApp->GetCameraController(),
	        *m_pAndroidRouteSimulationExampleViewFactory));

	m_pExampleController->RegisterExample(new Examples::JavaHudCrossThreadCommunicationExampleFactory(*m_pWorld, m_nativeState, m_pApp->GetCameraController()));
	m_pExampleController->RegisterExample(new Examples::PinsWithAttachedJavaUIExampleFactory(*m_pWorld, m_nativeState, m_pApp->GetCameraController()));
	m_pExampleController->RegisterExample(new Examples::PositionJavaPinButtonExampleFactory(*m_pWorld, m_nativeState, m_pApp->GetCameraController()));

	m_pExampleCameraJumpController = new ExampleCameraJumpController(m_pApp->GetCameraController(), m_pApp->GetTouchController());
	m_pExampleController->RegisterExample(new Examples::ShowJavaPlaceJumpUIExampleFactory(*m_pExampleCameraJumpController, m_pApp->GetCameraController(), m_nativeState));
}

void AppHost::DestroyExamples()
{
	delete m_pExampleCameraJumpController;
	delete m_pAndroidRouteMatchingExampleViewFactory;
	delete m_pAndroidRouteSimulationExampleViewFactory;

	delete m_pExampleController;
	delete m_pAndroidExampleControllerView;
}




