// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ExampleApp__
#define __ExampleApp__ExampleApp__

#include "GlobeCamera.h"
#include "EegeoWorld.h"
#include "ExampleController.h"
#include "ScreenProperties.h"
#include "DefaultCameraControllerFactory.h"
#include "Modules.h"


class ExampleApp : private Eegeo::NonCopyable
{
private:
    Examples::DefaultCameraControllerFactory* m_pCameraControllerFactory;
	Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* m_pCameraTouchController;
	Eegeo::EegeoWorld* m_pWorld;
    Eegeo::Rendering::LoadingScreen* m_pLoadingScreen;
	Examples::ExampleController* m_pExampleController;
    Examples::ScreenPropertiesProvider m_screenPropertiesProvider;
    

	Eegeo::EegeoWorld& World()
	{
		return * m_pWorld;
	}
    
    void UpdateLoadingScreen(float dt);

public:
	ExampleApp(Eegeo::EegeoWorld* pWorld,
	           Examples::IExampleControllerView& view,
               const Eegeo::Rendering::ScreenProperties& screenProperties,
               Eegeo::Modules::CollisionVisualizationModule& collisionVisualizationModule,
               Eegeo::Modules::BuildingFootprintsModule& buildingFootprintsModule);

	~ExampleApp();

	void OnPause();

	void OnResume();

	void Update (float dt);

	void Draw (float dt);
    
    void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
    
    Examples::ExampleController& GetExampleController() const { return *m_pExampleController; }
    
    Examples::DefaultCameraControllerFactory& GetDefaultCameraControllerFactory() const { return *m_pCameraControllerFactory; }

	Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& GetTouchController()
	{
		return *m_pCameraTouchController;
	}
    
    const Examples::IScreenPropertiesProvider& GetScreenPropertiesProvider() const { return m_screenPropertiesProvider; }

	void Event_TouchRotate 			(const AppInterface::RotateData& data);
	void Event_TouchRotate_Start	(const AppInterface::RotateData& data);
	void Event_TouchRotate_End 		(const AppInterface::RotateData& data);

	void Event_TouchPinch 			(const AppInterface::PinchData& data);
	void Event_TouchPinch_Start 	(const AppInterface::PinchData& data);
	void Event_TouchPinch_End 		(const AppInterface::PinchData& data);

	void Event_TouchPan				(const AppInterface::PanData& data);
	void Event_TouchPan_Start		(const AppInterface::PanData& data);
	void Event_TouchPan_End 		(const AppInterface::PanData& data);

	void Event_TouchTap 			(const AppInterface::TapData& data);
	void Event_TouchDoubleTap		(const AppInterface::TapData& data);

	void Event_TouchDown 			(const AppInterface::TouchData& data);
	void Event_TouchMove 			(const AppInterface::TouchData& data);
	void Event_TouchUp 				(const AppInterface::TouchData& data);
};

#endif /* defined(__ExampleApp__ExampleApp__) */
