// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteSimulationExampleFactory.h"
#include "RouteSimulationExample.h"
#include "RenderContext.h"
#include "LocalAsyncTextureLoader.h"
#include "CollisionMeshResourceRepository.h"
#include "DefaultCameraControllerFactory.h"
#include "TerrainModelModule.h"
#include "MapModule.h"
#include "RoutesModule.h"
#include "IPlatformAbstractionModule.h"
#include "AsyncLoadersModule.h"

namespace Examples
{

RouteSimulationExampleFactory::RouteSimulationExampleFactory(Eegeo::EegeoWorld& world,
                                                             DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                                             const IScreenPropertiesProvider& screenPropertiesProvider,
                                                             const IRouteSimulationExampleViewFactory& routeSimulationViewFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    , m_screenPropertiesProvider(screenPropertiesProvider)
	, m_routeSimulationViewFactory(routeSimulationViewFactory)
{
    Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_world.GetTerrainModelModule();
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    
	m_pRouteSimulationGlobeCameraControllerFactory = new Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory
	(
	    terrainModelModule.GetTerrainHeightProvider(),
	    mapModule.GetEnvironmentFlatteningService(),
	    mapModule.GetResourceCeilingProvider(),
	    terrainModelModule.GetCollisionMeshResourceRepository()
	);
}

RouteSimulationExampleFactory::~RouteSimulationExampleFactory()
{
	delete m_pRouteSimulationGlobeCameraControllerFactory;
}

IExample* RouteSimulationExampleFactory::CreateExample() const
{
    Eegeo::Modules::RoutesModule& routesModule = m_world.GetRoutesModule();
    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = m_world.GetPlatformAbstractionModule();
    Eegeo::Modules::Core::AsyncLoadersModule& asyncLoadersModule = m_world.GetAsyncLoadersModule();
    
	return new Examples::RouteSimulationExample(routesModule.GetRouteService(),
	        routesModule.GetRouteSimulationService(),
	        routesModule.GetRouteSimulationViewService(),
	        platformAbstractionModule.GetFileIO(),
	        asyncLoadersModule.GetLocalAsyncTextureLoader(),
	        m_defaultCameraControllerFactory.Create(),
            m_globeCameraTouchController,
	        *m_pRouteSimulationGlobeCameraControllerFactory,
            m_screenPropertiesProvider,
	        m_routeSimulationViewFactory,
	        m_world);
}

std::string RouteSimulationExampleFactory::ExampleName() const
{
	return Examples::RouteSimulationExample::GetName();
}

}
