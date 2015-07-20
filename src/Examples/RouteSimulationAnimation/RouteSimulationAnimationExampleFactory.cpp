// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteSimulationAnimationExampleFactory.h"
#include "RouteSimulationAnimationExample.h"
#include "LocalAsyncTextureLoader.h"
#include "RenderContext.h"

#include "CollisionMeshResourceRepository.h"

#include "MapModule.h"
#include "TerrainModelModule.h"
#include "RoutesModule.h"
#include "RenderingModule.h"
#include "IPlatformAbstractionModule.h"
#include "AsyncLoadersModule.h"
#include "SceneModelsModule.h"

namespace Examples
{

RouteSimulationAnimationExampleFactory::RouteSimulationAnimationExampleFactory(Eegeo::EegeoWorld& world,
                                                                               DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                                               Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                                                               const IScreenPropertiesProvider& screenPropertiesProvider)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    , m_screenPropertiesProvider(screenPropertiesProvider)
	, m_pRouteSimulationGlobeCameraControllerFactory(NULL)
{
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_world.GetTerrainModelModule();
    
	m_pRouteSimulationGlobeCameraControllerFactory = new Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory
	(
            terrainModelModule.GetTerrainHeightProvider(),
	        mapModule.GetEnvironmentFlatteningService(),
	        mapModule.GetResourceCeilingProvider(),
	        terrainModelModule.GetTerrainCollisionMeshResourceRepository()
	);
}


RouteSimulationAnimationExampleFactory::~RouteSimulationAnimationExampleFactory()
{
	delete m_pRouteSimulationGlobeCameraControllerFactory;
}

IExample* RouteSimulationAnimationExampleFactory::CreateExample() const
{
    Eegeo::Modules::RoutesModule& routesModule = m_world.GetRoutesModule();
    Eegeo::Modules::Core::SceneModelsModule& sceneModelsModule = m_world.GetCoreModule().GetSceneModelsModule();
    
	return new Examples::RouteSimulationAnimationExample(routesModule.GetRouteService(),
	        routesModule.GetRouteSimulationService(),
	        routesModule.GetRouteSimulationViewService(),
            sceneModelsModule.GetLocalModelLoader(),
	        *m_pRouteSimulationGlobeCameraControllerFactory,
            m_screenPropertiesProvider,
	        m_world);
}

std::string RouteSimulationAnimationExampleFactory::ExampleName() const
{
	return Examples::RouteSimulationAnimationExample::GetName();
}
}
