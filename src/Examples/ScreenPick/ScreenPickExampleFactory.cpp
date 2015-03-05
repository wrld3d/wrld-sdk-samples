// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ScreenPickExampleFactory.h"
#include "ScreenPickExample.h"
#include "DefaultCameraControllerFactory.h"
#include "CollisionMeshResourceRepository.h"

#include "TerrainModelModule.h"
#include "DebugRenderingModule.h"

namespace Examples
{

ScreenPickExampleFactory::ScreenPickExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* ScreenPickExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_world.GetTerrainModelModule();
    Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule = m_world.GetDebugRenderingModule();
    
	return new Examples::ScreenPickExample(terrainModelModule.GetTerrainHeightProvider(),
	                                       terrainModelModule.GetTerrainCollisionMeshResourceRepository(),
                                           debugRenderingModule.GetDebugRenderer(),
	                                       m_defaultCameraControllerFactory.Create(),
                                           m_globeCameraTouchController);
}

std::string ScreenPickExampleFactory::ExampleName() const
{
	return Examples::ScreenPickExample::GetName();
}

}
