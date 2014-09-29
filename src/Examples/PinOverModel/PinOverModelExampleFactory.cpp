// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PinOverModelExampleFactory.h"
#include "PinOverModelExample.h"
#include "LocalAsyncTextureLoader.h"

#include "IPlatformAbstractionModule.h"
#include "RenderingModule.h"
#include "TerrainModelModule.h"
#include "MapModule.h"
#include "AsyncLoadersModule.h"
#include "LightingModule.h"

using namespace Examples;

PinOverModelExampleFactory::PinOverModelExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* PinOverModelExampleFactory::CreateExample() const
{
    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractioModule = m_world.GetPlatformAbstractionModule();
    Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
    Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_world.GetTerrainModelModule();
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    Eegeo::Modules::Core::AsyncLoadersModule& asyncLoadersModule = m_world.GetAsyncLoadersModule();
    Eegeo::Modules::Core::LightingModule& lightingModule = m_world.GetLightingModule();
    
	return new Examples::PinOverModelExample(platformAbstractioModule.GetTextureFileLoader(),
	        renderingModule.GetGlBufferPool(),
	        renderingModule.GetShaderIdGenerator(),
	        renderingModule.GetMaterialIdGenerator(),
	        renderingModule.GetVertexBindingPool(),
	        renderingModule.GetVertexLayoutPool(),
	        renderingModule.GetRenderableFilters(),
	        terrainModelModule.GetTerrainHeightProvider(),
	        mapModule.GetEnvironmentFlatteningService(),
	        platformAbstractioModule.GetFileIO(),
	        asyncLoadersModule.GetLocalAsyncTextureLoader(),
	        lightingModule.GetGlobalFogging(),
	        renderingModule.GetNullMaterial(),
	        m_globeCameraController);
}

std::string PinOverModelExampleFactory::ExampleName() const
{
	return Examples::PinOverModelExample::GetName();
}


