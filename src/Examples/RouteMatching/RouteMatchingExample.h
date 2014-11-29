// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RouteMatchingExample__
#define __ExampleApp__RouteMatchingExample__

#include <vector>
#include "IExample.h"
#include "RouteService.h"
#include "Route.h"
#include "EegeoWorld.h"
#include "IdentityRouteThicknessPolicy.h"
#include "IRouteMatchingExampleViewFactory.h"
#include "IRouteMatchingExampleView.h"
#include "UIActionHandler.h"

namespace Examples
{
class RouteMatchingExample : public IExample
{
private:
	Eegeo::Routes::RouteService& m_routeService;
	Eegeo::EegeoWorld& m_world;

	const IRouteMatchingExampleViewFactory& m_routeMatchingViewFactory;
	UIActionHandler<RouteMatchingExample> m_toggleRouteMatchingHandler;
	IRouteMatchingExampleView* m_pRouteMatchingView;
    
    Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pCameraController;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

	bool m_createdRoutes;
	bool m_routesMatchedToNavigationGraph;
	std::vector<Eegeo::Routes::Route*> m_routes;
	Eegeo::Routes::Style::Thickness::IdentityRouteThicknessPolicy m_routeThicknessPolicy;

	void CreateRoutes(bool shouldMatchToNavigationGraph);
	void DestroyRoutes();
	void CreateAndBindUI();

public:
	RouteMatchingExample(Eegeo::Routes::RouteService& routeService,
	                     Eegeo::EegeoWorld& eegeoWorld,
	                     const IRouteMatchingExampleViewFactory& routeMatchingViewFactory,
	                     Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController);

	static std::string GetName()
	{
		return "RouteMatchingExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void Update(float dt);
	void Draw() {}
	void Suspend();
    const Eegeo::Camera::RenderCamera& GetRenderCamera() const;
    Eegeo::dv3 GetInterestPoint() const;

	void ToggleMatching();
};
}

#endif /* defined(__ExampleApp__RouteMatchingExample__) */
