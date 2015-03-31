// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PinOverModelExampleFactory.h"
#include "PinOverModelExample.h"
#include "LocalAsyncTextureLoader.h"
#include "DefaultCameraControllerFactory.h"
#include "IPlatformAbstractionModule.h"
#include "RenderingModule.h"
#include "TerrainModelModule.h"
#include "MapModule.h"
#include "AsyncLoadersModule.h"
#include "LightingModule.h"

namespace Examples
{

PinOverModelExampleFactory::PinOverModelExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                          const IScreenPropertiesProvider& screenPropertiesProvider)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    , m_screenPropertiesProvider(screenPropertiesProvider)
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
    
    const Eegeo::Rendering::ScreenProperties& initialScreenProperties = m_screenPropertiesProvider.GetScreenProperties();
    
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
	        renderingModule.GetNullMaterialFactory(),
	        m_defaultCameraControllerFactory.Create(),
            m_globeCameraTouchController,
            initialScreenProperties);
}

std::string PinOverModelExampleFactory::ExampleName() const
{
	return Examples::PinOverModelExample::GetName();
}

}

