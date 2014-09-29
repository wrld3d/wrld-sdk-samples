// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef APPHOST_H_
#define APPHOST_H_

#include "Types.h"
#include "Graphics.h"
#include "AndroidFileIO.h"
#include "AndroidCacheFileIO.h"
#include "AndroidHttpCache.h"
#include "AndroidTextureFileLoader.h"
#include "AndroidWebRequestService.hpp"
#include "AndroidWebLoadRequestFactory.h"
#include "AndroidInputProcessor.h"
#include "AndroidLocationService.h"
#include "IJpegLoader.h"
#include "AndroidUrlEncoder.h"
#include "TerrainHeightProvider.h"
#include "AndroidInputHandler.h"
#include "AndroidInputBoxFactory.h"
#include "AndroidKeyboardInputFactory.h"
#include "AndroidAlertBoxFactory.h"
#include "NativeUIFactories.h"
#include "TerrainHeightRepository.h"
#include "GlobalShadowing.h"
#include "TouchEventWrapper.h"
#include "Blitter.h"
#include "AndroidNativeState.h"
#include "AppInputDelegate.h"
#include "Modules.h"
#include <vector>

//example app includes
#include "ExampleApp.h"
#include "ExampleController.h"
#include "AndroidExampleControllerView.h"
#include "AndroidExampleControllerProxy.h"
#include "AndroidSharedGlContext.h"
#include "AndroidRouteMatchingExampleViewFactory.h"
#include "AndroidRouteSimulationExampleViewFactory.h"
#include "ExampleCameraJumpController.h"

class AppHost : protected Eegeo::NonCopyable
{
public:
	AppHost(
	    const std::string& apiKey,
	    AndroidNativeState& nativeState,
	    float displayWidth,
	    float displayHeight,
	    EGLDisplay display,
	    EGLSurface shareSurface,
	    EGLContext resourceBuildShareContext
	);
	~AppHost();

	void Update(float dt);
	void Draw(float dt);

	void OnPause();
	void OnResume();

	void HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event);

	void SetEnvironmentFlatten(bool flattenState);
	void SetCameraLocation(const Eegeo::Space::LatLongAltitude& interestPoint, double distanceToInterestPoint, double orientationInDegrees);
	void SendCameraLocationToGUI();

	void SetSharedSurface(EGLSurface sharedSurface);
	void SetViewportOffset(float x, float y);

private:
	Eegeo::Blitter* m_pBlitter;
    Eegeo::Helpers::Jpeg::IJpegLoader* m_pJpegLoader;
	Eegeo::Android::AndroidLocationService* m_pAndroidLocationService;
	Eegeo::Rendering::ScreenProperties* m_pScreenProperties;
	Eegeo::EegeoWorld* m_pWorld;
	AndroidNativeState& m_nativeState;
	AppInputDelegate* m_pAppInputDelegate;

	Eegeo::Android::Input::AndroidInputHandler m_inputHandler;
	Eegeo::UI::NativeInput::Android::AndroidInputBoxFactory m_androidInputBoxFactory;
	Eegeo::UI::NativeInput::Android::AndroidKeyboardInputFactory m_androidKeyboardInputFactory;
	Eegeo::UI::NativeAlerts::Android::AndroidAlertBoxFactory m_androidAlertBoxFactory;
	Eegeo::UI::NativeUIFactories m_androidNativeUIFactories;

	ExampleApp* m_pApp;
	Examples::ExampleController* m_pExampleController;
	Examples::AndroidExampleControllerView* m_pAndroidExampleControllerView;
	Examples::AndroidRouteMatchingExampleViewFactory* m_pAndroidRouteMatchingExampleViewFactory;
	Examples::AndroidRouteSimulationExampleViewFactory* m_pAndroidRouteSimulationExampleViewFactory;
	ExampleCameraJumpController* m_pExampleCameraJumpController;

	Eegeo::Android::Input::AndroidInputProcessor* m_pInputProcessor;

	Eegeo::Android::AndroidPlatformAbstractionModule* m_pAndroidPlatformAbstractionModule;

	void ConfigureExamples();
	void DestroyExamples();
	void RegisterAndroidSpecificExamples();
};

#endif
