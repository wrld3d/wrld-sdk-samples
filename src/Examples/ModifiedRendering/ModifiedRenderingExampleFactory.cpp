// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModifiedRenderingExampleFactory.h"
#include "ModifiedRenderingExample.h"
#include "DefaultCameraControllerFactory.h"
#include "MapModule.h"
#include "LightingModule.h"
#include "BuildingModelModule.h"
#include "BuildingPresentationModule.h"
#include "RenderingModule.h"
#include "CameraFrustumStreamingVolume.h"

namespace Examples
{

ModifiedRenderingExampleFactory::ModifiedRenderingExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* ModifiedRenderingExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::Layers::BuildingModelModule& buildingModelModule = m_world.GetBuildingModelModule();
    Eegeo::Modules::Map::Layers::BuildingPresentationModule& buildingPresentationModule = m_world.GetBuildingPresentationModule();
    Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
    Eegeo::Rendering::AsyncTexturing::IAsyncTexture& placeHolderTexture = m_world.GetAsyncLoadersModule().GetPlaceholderTexture();
    
	return new Examples::ModifiedRenderingExample(
	        buildingModelModule.GetBuildingSceneElementRepository(),
	        buildingPresentationModule.GetBuildingRenderableFilter(),
	        renderingModule.GetRenderableFilters(),
	        renderingModule.GetShaderIdGenerator(),
	        renderingModule.GetMaterialIdGenerator(),
            renderingModule.GetVertexBindingPool(),
	        placeHolderTexture,
	        m_defaultCameraControllerFactory.Create(),
            m_globeCameraTouchController);
}

std::string ModifiedRenderingExampleFactory::ExampleName() const
{
	return Examples::ModifiedRenderingExample::GetName();
}
}

