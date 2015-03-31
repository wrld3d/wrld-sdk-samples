// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PinsExampleFactory.h"
#include "PinsExample.h"
#include "DefaultCameraControllerFactory.h"
#include "IPlatformAbstractionModule.h"
#include "RenderingModule.h"
#include "TerrainModelModule.h"
#include "MapModule.h"

namespace Examples
{

    PinsExampleFactory::PinsExampleFactory(Eegeo::EegeoWorld& world,
                                           DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                           const IScreenPropertiesProvider& screenPropertiesProvider)
	: m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
	, m_screenPropertiesProvider(screenPropertiesProvider)
{

}

IExample* PinsExampleFactory::CreateExample() const
{
    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractioModule = m_world.GetPlatformAbstractionModule();
    Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
    Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_world.GetTerrainModelModule();
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    
    const Eegeo::Rendering::ScreenProperties& initialScreenProperties = m_screenPropertiesProvider.GetScreenProperties();
    
	return new Examples::PinsExample(platformAbstractioModule.GetTextureFileLoader(),
	                                 renderingModule.GetGlBufferPool(),
	                                 renderingModule.GetShaderIdGenerator(),
	                                 renderingModule.GetMaterialIdGenerator(),
	                                 renderingModule.GetVertexBindingPool(),
	                                 renderingModule.GetVertexLayoutPool(),
	                                 renderingModule.GetRenderableFilters(),
	                                 terrainModelModule.GetTerrainHeightProvider(),
	                                 mapModule.GetEnvironmentFlatteningService(),
	                                 m_defaultCameraControllerFactory.Create(),
                                     m_globeCameraTouchController,
                                     initialScreenProperties
                                     );
}

std::string PinsExampleFactory::ExampleName() const
{
	return Examples::PinsExample::GetName();
}

}

