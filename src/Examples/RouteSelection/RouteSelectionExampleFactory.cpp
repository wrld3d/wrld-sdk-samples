// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "RouteSelectionExampleFactory.h"
#include "RouteSelectionExample.h"
#include "DefaultCameraControllerFactory.h"
#include "RoutesModule.h"
#include "CollisionMeshResourceRepository.h"
#include "TerrainModelModule.h"

namespace Examples
{

RouteSelectionExampleFactory::RouteSelectionExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* RouteSelectionExampleFactory::CreateExample() const
{
    Eegeo::Modules::RoutesModule& routesModule = m_world.GetRoutesModule();
    Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_world.GetTerrainModelModule();
	return new Examples::RouteSelectionExample(routesModule.GetRouteService(),
                                               routesModule.GetRouteRepository(),
                                               m_world,
                                               terrainModelModule.GetTerrainHeightProvider(),
                                               terrainModelModule.GetTerrainCollisionMeshResourceRepository(),
                                               m_defaultCameraControllerFactory.Create(),
                                               m_globeCameraTouchController);
}

std::string RouteSelectionExampleFactory::ExampleName() const
{
	return Examples::RouteSelectionExample::GetName();
}

}

