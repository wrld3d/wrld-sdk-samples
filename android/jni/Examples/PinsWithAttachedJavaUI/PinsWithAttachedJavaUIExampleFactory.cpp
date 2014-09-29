// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PinsWithAttachedJavaUIExampleFactory.h"
#include "PinsWithAttachedJavaUIExample.h"

#include "IPlatformAbstractionModule.h"
#include "RenderingModule.h"
#include "TerrainModelModule.h"
#include "MapModule.h"

using namespace Examples;

PinsWithAttachedJavaUIExampleFactory::PinsWithAttachedJavaUIExampleFactory(
    Eegeo::EegeoWorld& world,
    AndroidNativeState& nativeState,
    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_nativeState(nativeState)
	, m_globeCameraController(globeCameraController)
{

}

IExample* PinsWithAttachedJavaUIExampleFactory::CreateExample() const
{
	Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = m_world.GetPlatformAbstractionModule();
	Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
	Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = m_world.GetTerrainModelModule();
	Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();

	return new Examples::PinsWithAttachedJavaUIExample(
	           m_world,
	           m_nativeState,
	           platformAbstractionModule.GetTextureFileLoader(),
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

std::string PinsWithAttachedJavaUIExampleFactory::ExampleName() const
{
	return Examples::PinsWithAttachedJavaUIExample::GetName();
}
