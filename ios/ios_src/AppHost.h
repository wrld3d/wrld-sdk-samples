// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef APPHOST_H_
#define APPHOST_H_

#include "Types.h"
#include "Graphics.h"
#include "IJpegLoader.h"
#include "GlobeCameraInterestPointProvider.h"
#include "iOSInputBoxFactory.h"
#include "iOSKeyboardInputFactory.h"
#include "iOSAlertBoxFactory.h"
#include "NativeUIFactories.h"
#include "Blitter.h"
#include "AppInputDelegate.h"
#include "AppLocationDelegate.h"
#include "Modules.h"
#include <vector>

//example app includes
#include "ExampleApp.h"
#include "ExampleController.h"
#include "iOSExampleControllerView.h"
#include "iOSRouteMatchingExampleViewFactory.h"
#include "iOSRouteSimulationExampleViewFactory.h"

@class ViewController;
class AppInputDelegate;
class AppLocationDelegate;

class AppHost : protected Eegeo::NonCopyable
{
public:
	AppHost(
	    const std::string& apiKey,
        ViewController& viewController,
        const Eegeo::Rendering::ScreenProperties& screenProperties
	);
	~AppHost();

	void Update(float dt);
	void Draw(float dt);

	void OnPause();
	void OnResume();
    
	void SetViewportOffset(float x, float y);
    
    void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);

private:
    ViewController& m_viewController;
    Eegeo::Helpers::Jpeg::IJpegLoader* m_pJpegLoader;
	Eegeo::iOS::iOSLocationService* m_piOSLocationService;
	Eegeo::EegeoWorld* m_pWorld;
    Eegeo::Modules::CollisionVisualizationModule* m_pCollisionVisualizationModule;
    Eegeo::Modules::BuildingFootprintsModule* m_pBuildingFootprintsModule;
	AppInputDelegate* m_pAppInputDelegate;
    AppLocationDelegate* m_pAppLocationDelegate;

	Eegeo::UI::NativeInput::iOS::iOSInputBoxFactory m_iOSInputBoxFactory;
	Eegeo::UI::NativeInput::iOS::iOSKeyboardInputFactory m_iOSKeyboardInputFactory;
	Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory m_iOSAlertBoxFactory;
	Eegeo::UI::NativeUIFactories m_iOSNativeUIFactories;
    Eegeo::iOS::iOSPlatformAbstractionModule* m_piOSPlatformAbstractionModule;

	ExampleApp* m_pApp;
	Examples::iOSExampleControllerView* m_piOSExampleControllerView;
	Examples::iOSRouteMatchingExampleViewFactory* m_piOSRouteMatchingExampleViewFactory;
	Examples::iOSRouteSimulationExampleViewFactory* m_piOSRouteSimulationExampleViewFactory;
    
    void ConfigureExamples(const Eegeo::Rendering::ScreenProperties& screenProperties);
	void DestroyExamples();
	void RegisteriOSSpecificExamples();
};

#endif
