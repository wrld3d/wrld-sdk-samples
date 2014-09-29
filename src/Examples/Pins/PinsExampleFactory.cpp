// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PinsExampleFactory.h"
#include "PinsExample.h"

#include "IPlatformAbstractionModule.h"
#include "RenderingModule.h"
#include "TerrainModelModule.h"
#include "MapModule.h"

using namespace Examples;

PinsExampleFactory::PinsExampleFactory(Eegeo::EegeoWorld& world,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* PinsExampleFactory::CreateExample() const
{
    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractioModule = m_world.GetPlatformAbstractionModule();
    Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
    Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_world.GetTerrainModelModule();
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    
	return new Examples::PinsExample(platformAbstractioModule.GetTextureFileLoader(),
	                                 renderingModule.GetGlBufferPool(),
	                                 renderingModule.GetShaderIdGenerator(),
	                                 renderingModule.GetMaterialIdGenerator(),
	                                 renderingModule.GetVertexBindingPool(),
	                                 renderingModule.GetVertexLayoutPool(),
	                                 renderingModule.GetRenderableFilters(),
	                                 terrainModelModule.GetTerrainHeightProvider(),
	                                 mapModule.GetEnvironmentFlatteningService(),
	                                 m_globeCameraController);
}

std::string PinsExampleFactory::ExampleName() const
{
	return Examples::PinsExample::GetName();
}

