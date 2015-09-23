// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RemoveMapLayerExampleFactory.h"
#include "RemoveMapLayerExample.h"
#include "DefaultCameraControllerFactory.h"
#include "RenderingModule.h"
#include "BuildingPresentationModule.h"
#include "TransportPresentationModule.h"
#include "TerrainPresentationModule.h"
#include "ShadowPresentationModule.h"

namespace Examples
{
    RemoveMapLayerExampleFactory::RemoveMapLayerExampleFactory(Eegeo::EegeoWorld& world,
                                                               DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                               Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
    : m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    {

    }

    IExample* RemoveMapLayerExampleFactory::CreateExample() const
    {
        Eegeo::Modules::Map::Layers::BuildingPresentationModule& buildingPresentationModule = m_world.GetBuildingPresentationModule();
        Eegeo::Modules::Map::Layers::ShadowPresentationModule& shadowPresentationModule = m_world.GetShadowPresentationModule();
        Eegeo::Modules::Map::Layers::TerrainPresentationModule& terrainPresentationModule = m_world.GetTerrainPresentationModule();
        Eegeo::Modules::Map::Layers::TransportPresentationModule& transportPresentationModule = m_world.GetTransportPresentationModule();
        
        Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
        
        return new Examples::RemoveMapLayerExample(buildingPresentationModule.GetBuildingRenderableFilter(),
                                                   shadowPresentationModule.GetShadowRenderableFilter(),
                                                   terrainPresentationModule.GetLcmTerrainRenderableFilter(),
                                                   transportPresentationModule.GetRoadsRenderableFilter(),
                                                   renderingModule.GetRenderableFilters(),
                                                   m_defaultCameraControllerFactory.Create(),
                                                   m_globeCameraTouchController);
    }

    std::string RemoveMapLayerExampleFactory::ExampleName() const
    {
        return Examples::RemoveMapLayerExample::GetName();
    }
}

