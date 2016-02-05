// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RouteSimulationExample__
#define __ExampleApp__RouteSimulationExample__

#include <vector>
#include "GlobeCameraExampleBase.h"
#include "RouteService.h"
#include "RouteBuilder.h"
#include "Route.h"
#include "RouteStyle.h"
#include "RouteSimulationService.h"
#include "RouteSimulationSession.h"
#include "RouteSimulationViewService.h"
#include "SphereMesh.h"
#include "RouteSimulationModelBinding.h"
#include "RouteSimulationGlobeCameraController.h"
#include "RouteSimulationGlobeCameraControllerFactory.h"
#include "GLState.h"
#include "IFileIO.h"
#include "ITextureFileLoader.h"
#include "Model.h"
#include "Node.h"
#include "GlobeCameraController.h"
#include "EegeoWorld.h"
#include "IInterestPointProvider.h"
#include "IdentityRouteThicknessPolicy.h"
#include "IRouteSimulationSessionObserver.h"
#include "IRouteSimulationExampleViewFactory.h"
#include "IRouteSimulationExampleView.h"
#include "UIActionHandler.h"
#include "ScreenPropertiesProvider.h"
#include "Rendering.h"

namespace Examples
{
class RouteSimulationExampleObserver : public Eegeo::Routes::Simulation::IRouteSimulationSessionObserver
{
public:
	RouteSimulationExampleObserver(Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* pModelBinding,
                                   std::vector<Eegeo::Rendering::SceneModels::SceneModel*>& vehicleModels)
		: m_pModelBinding(pModelBinding)
        , m_vehicleModels(vehicleModels)
	{
	}

	void OnLinkReached(const Eegeo::Routes::Simulation::RouteSimulationSession& session) const;

private:
	Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pModelBinding;
    const std::vector<Eegeo::Rendering::SceneModels::SceneModel*>& m_vehicleModels;
};

class RouteSimulationExample : public GlobeCameraExampleBase
{
private:
	Eegeo::Routes::RouteService& m_routeService;
	Eegeo::Routes::Simulation::RouteSimulationService& m_routeSimulationService;
	Eegeo::Routes::Simulation::View::RouteSimulationViewService& m_routeSimulationViewService;
	Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory& m_routeSimulationGlobeCameraControllerFactory;
	Eegeo::EegeoWorld& m_world;
    Eegeo::Rendering::SceneModels::SceneModelLoader& m_sceneModelLoader;
    
	const IRouteSimulationExampleViewFactory& m_routeSimulationExampleViewFactory;
	IRouteSimulationExampleView* m_pRouteSimulationView;
	Examples::UIActionHandler<RouteSimulationExample> m_decreaseSpeedToggleHandler;
	Examples::UIActionHandler<RouteSimulationExample> m_increaseSpeedToggleHandler;
	Examples::UIActionHandler<RouteSimulationExample> m_followCameraToggleHandler;
	Examples::UIActionHandler<RouteSimulationExample> m_rotateToFollowToggledHandler;
	Examples::UIActionHandler<RouteSimulationExample> m_directionChangedHandler;
    Examples::UIActionHandler<RouteSimulationExample> m_roadSideChangedHandler;
    
	bool m_initialised;
	bool m_usingFollowCamera;
    Eegeo::Rendering::SceneModels::SceneModel* m_pVehicleModel1;
    Eegeo::Rendering::SceneModels::SceneModel* m_pVehicleModel2;
    std::vector<Eegeo::Rendering::SceneModels::SceneModel*> m_switchableVehicleModels;
	Eegeo::Routes::Route* m_pRoute;
	Eegeo::Routes::Style::Thickness::IdentityRouteThicknessPolicy m_routeThicknessPolicy;

	Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionCycle;
	Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionAlternatingSpeedChanger;
	Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionCamera;

	Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pViewBindingForCycleSession;
	Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pViewBindingForOscillatingSession;
	Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pViewBindingForCameraSession;

	float m_linkSpeedMultiplier;


	Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraController* m_pRouteSessionFollowCameraController;

	RouteSimulationExampleObserver* m_pExampleObserver;
public:
	RouteSimulationExample(Eegeo::Routes::RouteService& routeService,
	                       Eegeo::Routes::Simulation::RouteSimulationService& routeSimulationService,
	                       Eegeo::Routes::Simulation::View::RouteSimulationViewService& routeSimulationViewService,
	                       Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                           Eegeo::Camera::GlobeCamera::GlobeCameraController* pDefaultCameraController,
                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& defaultCameraTouchController,
	                       Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory& routeSimulationGlobeCameraControllerFactory,
	                       const IRouteSimulationExampleViewFactory& routeSimulationExampleViewFactory,
                           Eegeo::EegeoWorld& eegeoWorld,
                           const Eegeo::Rendering::ScreenProperties& screenProperties);

	static std::string GetName()
	{
		return "RouteSimulationExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void EarlyUpdate(float dt);
	void Update(float dt);
	void Draw() {}
	void Suspend();
    
    Eegeo::Camera::CameraState GetCurrentCameraState() const;
    
    virtual void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
    
    void NotifyViewNeedsLayout();
    
	void Event_TouchRotate 			(const AppInterface::RotateData& data);
	void Event_TouchRotate_Start	(const AppInterface::RotateData& data);
	void Event_TouchRotate_End 		(const AppInterface::RotateData& data);

	void Event_TouchPinch 			(const AppInterface::PinchData& data);
	void Event_TouchPinch_Start 	(const AppInterface::PinchData& data);
	void Event_TouchPinch_End 		(const AppInterface::PinchData& data);

	void Event_TouchPan				(const AppInterface::PanData& data);
	void Event_TouchPan_Start		(const AppInterface::PanData& data);
	void Event_TouchPan_End 		(const AppInterface::PanData& data);
    
    void Event_TouchTap 			(const AppInterface::TapData& data) {;}
    void Event_TouchDoubleTap		(const AppInterface::TapData& data) {;}
    void Event_TouchDown 			(const AppInterface::TouchData& data) {;}
    void Event_TouchMove 			(const AppInterface::TouchData& data) {;}
    void Event_TouchUp 				(const AppInterface::TouchData& data) {;}

	void ToggleFollowCamera();
	void ChangeFollowDirection();
	void IncreaseSpeedFollowed();
	void DecreaseSpeedFollowed();
	void ToggleRotateToFollow();
	void ToggleSideOfRoadToDriveOn();

private:

	void Initialise();

	void CreateAndBindUI();

	Eegeo::Routes::Route* BuildRoute() const;

    void LoadModelVehicleNodes(Eegeo::Rendering::SceneModels::SceneModel*& pVehicleModel1,
                               Eegeo::Rendering::SceneModels::SceneModel*& pVehicleModel2,
                               std::vector<Eegeo::Rendering::SceneModels::SceneModel*>& out_vehicleModels) const;
};
}

#endif /* defined(__ExampleApp__RouteSimulationExample__) */
