// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModifiedRenderingExampleFactory.h"
#include "ModifiedRenderingExample.h"

using namespace Examples;

#include "MapModule.h"
#include "LightingModule.h"
#include "BuildingModelModule.h"
#include "BuildingPresentationModule.h"
#include "RenderingModule.h"
#include "CameraFrustumStreamingVolume.h"

ModifiedRenderingExampleFactory::ModifiedRenderingExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* ModifiedRenderingExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    Eegeo::Modules::Core::LightingModule& lightingModule = m_world.GetLightingModule();
    Eegeo::Modules::Map::Layers::BuildingModelModule& buildingModelModule = m_world.GetBuildingModelModule();
    Eegeo::Modules::Map::Layers::BuildingPresentationModule& buildingPresentationModule = m_world.GetBuildingPresentationModule();
    Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
    
	return new Examples::ModifiedRenderingExample(
	        mapModule.GetStreamingVolume(),
	        lightingModule.GetGlobalLighting(),
	        buildingModelModule.GetBuildingSceneElementRepository(),
	        buildingPresentationModule.GetBuildingRenderableFilter(),
	        renderingModule.GetRenderableFilters(),
	        renderingModule.GetShaderIdGenerator(),
	        renderingModule.GetMaterialIdGenerator(),
	        m_world.GetEnvironmentPlaceholderTexture(),
	        m_globeCameraController);
}

std::string ModifiedRenderingExampleFactory::ExampleName() const
{
	return Examples::ModifiedRenderingExample::GetName();
}

