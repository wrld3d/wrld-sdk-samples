// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RoutingServiceExample__
#define __ExampleApp__RoutingServiceExample__

#include <vector>
#include "GlobeCameraExampleBase.h"
#include "RouteService.h"
#include "Route.h"
#include "EegeoWorld.h"
#include "LinearAltitudeBasedRouteThicknessPolicy.h"
#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"
#include "Interiors.h"
#include "UIActionHandler.h"

namespace Examples
{
    
class IRoutingServiceExampleView;
class IRoutingServiceExampleViewFactory;
    
class RoutingServiceExample : public GlobeCameraExampleBase
{
private:
    
	Eegeo::Routes::RouteService& m_routeService;
    const Eegeo::Routes::Webservice::RoutingRequestBuilder& m_requestBuilder;
    Eegeo::EegeoWorld& m_world;
    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
    Eegeo::Web::TWebLoadRequestCompletionCallback<RoutingServiceExample> m_routeReceivedCallback;
    Eegeo::Resources::Interiors::InteriorInteractionModel* m_pInteriorInteractionModel;
    Eegeo::Resources::Interiors::InteriorSelectionModel* m_pInteriorSelectionModel;
    IRoutingServiceExampleView* m_pRoutingServiceView;
    IRoutingServiceExampleViewFactory& m_routingServiceViewFactory;
    
    UIActionHandler<RoutingServiceExample> m_moveUpHandler;
    UIActionHandler<RoutingServiceExample> m_moveDownHandler;
    UIActionHandler<RoutingServiceExample> m_getRouteHandler;

    bool m_enteredInterior;
	std::vector<Eegeo::Routes::Route*> m_routes;
	Eegeo::Routes::Style::Thickness::LinearAltitudeBasedRouteThicknessPolicy m_routeThicknessPolicy;

    void RouteReceivedCallback(Eegeo::Web::IWebResponse& webResponse);
    void EnterInterior(const Eegeo::Resources::Interiors::InteriorId& interiorId);
    void ExitInterior();
    void CreateAndBindUI();
    
    void MoveUp();
    void MoveDown();
    void GetRoute();

public:
	RoutingServiceExample(Eegeo::Routes::RouteService& routeService,
                          const Eegeo::Routes::Webservice::RoutingRequestBuilder& requestBuilder,
                          Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
	                      Eegeo::EegeoWorld& eegeoWorld,
	                      Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                          IRoutingServiceExampleViewFactory& routingServiceViewFactory);

	static std::string GetName()
	{
		return "RoutingServiceExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void Update(float dt);
	void Draw() {}
	void Suspend();
    
    
};
}



#endif /* defined(__ExampleApp__RoutingServiceExample__) */
