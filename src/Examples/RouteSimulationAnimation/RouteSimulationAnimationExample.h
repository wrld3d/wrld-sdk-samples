// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RouteSimulationAnimationExample__
#define __ExampleApp__RouteSimulationAnimationExample__

#include <vector>
#include "IExample.h"
#include "RouteService.h"
#include "RouteBuilder.h"
#include "Route.h"
#include "RouteStyle.h"
#include "RouteSimulationService.h"
#include "RouteSimulationSession.h"
#include "RouteSimulationViewService.h"
#include "RouteSimulationModelBinding.h"
#include "RouteSimulationGlobeCameraController.h"
#include "RouteSimulationGlobeCameraControllerFactory.h"
#include "GLState.h"
#include "IFileIO.h"
#include "ITextureFileLoader.h"
#include "GlobeCameraController.h"
#include "EegeoWorld.h"
#include "IdentityRouteThicknessPolicy.h"
#include "GlobeCameraController.h"
#include "ScreenPropertiesProvider.h"
#include "Rendering.h"

namespace Examples
{
class RouteSimulationAnimationExample : public IExample, Eegeo::NonCopyable
{
private:
	Eegeo::Routes::RouteService& m_routeService;
	Eegeo::Routes::Simulation::RouteSimulationService& m_routeSimulationService;
	Eegeo::Routes::Simulation::View::RouteSimulationViewService& m_routeSimulationViewService;
    
	Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory& m_routeSimulationGlobeCameraControllerFactory;
	Eegeo::EegeoWorld& m_world;
	bool m_initialised;
    Eegeo::Rendering::SceneModels::SceneModel* m_pModel;
    Eegeo::Rendering::SceneModels::SceneModelLoader& m_sceneModelLoader;
    Eegeo::Rendering::SceneModels::SceneModelAnimator* m_pSceneModelAnimator;
	Eegeo::Routes::Route* m_pRoute;
	Eegeo::Routes::Style::Thickness::IdentityRouteThicknessPolicy m_routeThicknessPolicy;
	Eegeo::Routes::Simulation::RouteSimulationSession* m_pRouteSimulationSession;
    Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pViewBindingForCameraSession;
    Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraController* m_pRouteSessionFollowCameraController;

	void CalculateTransform(Eegeo::m44& transform);

public:
	RouteSimulationAnimationExample(Eegeo::Routes::RouteService& routeService,
	                                Eegeo::Routes::Simulation::RouteSimulationService& routeSimulationService,
	                                Eegeo::Routes::Simulation::View::RouteSimulationViewService& routeSimulationViewService,
                                    Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
	                                Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory& routeSimulationGlobeCameraControllerFactory,
                                    const IScreenPropertiesProvider& screenPropertiesProvider,
	                                Eegeo::EegeoWorld& eegeoWorld);
    virtual ~RouteSimulationAnimationExample();

	static std::string GetName()
	{
		return "RouteSimulationAnimationExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void EarlyUpdate(float dt);
	void Update(float dt);
    void PreWorldDraw() {}
	void Draw() {}
	void Suspend();
    
    Eegeo::Camera::CameraState GetCurrentCameraState() const;
    
    virtual void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);

    void NotifyViewNeedsLayout() {}
    
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

private:

	void Initialise();

	Eegeo::Routes::Route* BuildRoute();

	 Eegeo::Rendering::SceneModels::SceneModel* LoadCharacterModel() const;
};
}


#endif /* defined(__ExampleApp__RouteSimulationAnimationExample__) */
