// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ScreenPickExampleFactory.h"
#include "ScreenPickExample.h"

#include "CollisionMeshResourceRepository.h"

#include "TerrainModelModule.h"
#include "DebugRenderingModule.h"

using namespace Examples;

ScreenPickExampleFactory::ScreenPickExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* ScreenPickExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_world.GetTerrainModelModule();
    Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule = m_world.GetDebugRenderingModule();
    
	return new Examples::ScreenPickExample(terrainModelModule.GetTerrainHeightProvider(),
	                                       terrainModelModule.GetCollisionMeshResourceRepository(),
                                           debugRenderingModule.GetDebugRenderer(),
	                                       m_globeCameraController);
}

std::string ScreenPickExampleFactory::ExampleName() const
{
	return Examples::ScreenPickExample::GetName();
}

