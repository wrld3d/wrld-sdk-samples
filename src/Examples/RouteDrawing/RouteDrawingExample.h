// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RouteDrawingExample__
#define __ExampleApp__RouteDrawingExample__

#include <vector>
#include "IExample.h"
#include "RouteService.h"
#include "Route.h"
#include "EegeoWorld.h"
#include "IdentityRouteThicknessPolicy.h"

namespace Examples
{
class RouteDrawingExample : public IExample
{
private:
	Eegeo::Routes::RouteService& m_routeService;
	Eegeo::EegeoWorld& m_world;

	bool m_createdRoutes;
	std::vector<Eegeo::Routes::Route*> m_routes;
	Eegeo::Routes::Style::Thickness::IdentityRouteThicknessPolicy m_routeThicknessPolicy;
    Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pCameraController;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

public:
	RouteDrawingExample(Eegeo::Routes::RouteService& routeService,
	                    Eegeo::EegeoWorld& eegeoWorld,
	                    Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController);

	static std::string GetName()
	{
		return "RouteDrawingExample";
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
};
}



#endif /* defined(__ExampleApp__RouteDrawingExample__) */
