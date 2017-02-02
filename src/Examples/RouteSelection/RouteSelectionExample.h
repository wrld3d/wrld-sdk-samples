// Copyright eeGeo Ltd 2016, All Rights Reserved

#ifndef __ExampleApp__RouteSelectionExample__
#define __ExampleApp__RouteSelectionExample__

#include <vector>
#include "GlobeCameraExampleBase.h"
#include "RouteService.h"
#include "RouteRepository.h"
#include "Route.h"
#include "EegeoWorld.h"
#include "ExampleRouteThicknessPolicy.h"

namespace Examples
{
class RouteSelectionExample : public GlobeCameraExampleBase
{
private:
	Eegeo::Routes::RouteService& m_routeService;
    Eegeo::Routes::RouteRepository& m_routeRepository;
	Eegeo::EegeoWorld& m_world;

	bool m_createdRoutes;
	std::vector<Eegeo::Routes::Route*> m_routes;
	ExampleRouteThicknessPolicy m_routeThicknessPolicy;
    Eegeo::Resources::Terrain::Collision::TerrainRayPicker* m_pRayPicker;

    std::vector<std::vector<Eegeo::Space::LatLongAltitude>> m_sourceRoutePts;
    std::vector<int> m_displayedRouteToSourceRouteMap;
    std::vector<Eegeo::v4> m_routeColors;
    int m_selectedRoute;
    int m_indexBeforeSelectedSegment;
    void CreateRoutes();
    void DestroyRoutes();

public:
	RouteSelectionExample(Eegeo::Routes::RouteService& routeService,
                          Eegeo::Routes::RouteRepository& routeRepository,
                          Eegeo::EegeoWorld& eegeoWorld,
                          Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                          const Eegeo::Collision::ICollisionBvhProvider& collisionMeshResourceProvider,
	                      Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	static std::string GetName()
	{
		return "RouteSelectionExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void Update(float dt);
	void Draw() {}
	void Suspend();
    
    void Event_TouchTap(const AppInterface::TapData& data);
    
};
}



#endif /* defined(__ExampleApp__RouteSelectionExample__) */
