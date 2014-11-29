// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ScreenUnprojectExampleFactory.h"
#include "ScreenUnprojectExample.h"

#include "DebugRenderingModule.h"
#include "TerrainModelModule.h"

using namespace Examples;

ScreenUnprojectExampleFactory::ScreenUnprojectExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
{

}

IExample* ScreenUnprojectExampleFactory::CreateExample() const
{
    Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule = m_world.GetDebugRenderingModule();
    Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_world.GetTerrainModelModule();
    
	return new Examples::ScreenUnprojectExample(debugRenderingModule.GetDebugRenderer(),
                                                terrainModelModule.GetTerrainHeightProvider(),
                                                m_defaultCameraControllerFactory.Create());
}

std::string ScreenUnprojectExampleFactory::ExampleName() const
{
	return Examples::ScreenUnprojectExample::GetName();
}
