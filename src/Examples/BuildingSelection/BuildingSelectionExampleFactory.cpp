// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "BuildingSelectionExampleFactory.h"
#include "BuildingSelectionExample.h"
#include "DefaultCameraControllerFactory.h"
#include "BuildingFootprintsModule.h"
#include "CollisionVisualizationModule.h"
#include "EnvironmentRayCaster.h"
#include "MapModule.h"
#include "AggregateCollisionBvhProvider.h"

namespace Examples
{

    namespace
    {
        Eegeo::Modules::CollisionVisualizationModule* CreateCollisionVisualizationModule(Eegeo::EegeoWorld& world)
        {
            const Eegeo::CollisionVisualization::MaterialSelectionControllerConfig& materialSelectionControllerConfig = Eegeo::Modules::CollisionVisualizationModule::MakeDefaultConfig();
            
            
            const Eegeo::Modules::Core::RenderingModule& renderingModule = world.GetRenderingModule();
            const Eegeo::Modules::Map::MapModule& mapModule = world.GetMapModule();
            
            Eegeo::Modules::CollisionVisualizationModule* pCollisionVisualizationModule = Eegeo::Modules::CollisionVisualizationModule::Create(renderingModule, mapModule, materialSelectionControllerConfig);
            return pCollisionVisualizationModule;
        }
        
        Eegeo::Modules::BuildingFootprintsModule* CreateBuildingFootprintsModule(Eegeo::EegeoWorld& world, const Eegeo::Modules::CollisionVisualizationModule& collisionVisualizationModule)
        {
            const Eegeo::BuildingFootprints::BuildingFootprintSelectionControllerConfig& buildingFootprintSelectionControllerConfig = Eegeo::Modules::BuildingFootprintsModule::MakeDefaultConfig();
            
            const Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = world.GetPlatformAbstractionModule();
            const Eegeo::Modules::Core::RenderingModule& renderingModule = world.GetRenderingModule();
            
            Eegeo::Modules::BuildingFootprintsModule* pBuildingFootprintsModule = Eegeo::Modules::BuildingFootprintsModule::Create(platformAbstractionModule, renderingModule, collisionVisualizationModule, buildingFootprintSelectionControllerConfig);
            return pBuildingFootprintsModule;
        }
    }
    
    BuildingSelectionExampleFactory::BuildingSelectionExampleFactory(Eegeo::EegeoWorld& world,
                                    DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
    : m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    {}
    
    std::string BuildingSelectionExampleFactory::ExampleName() const
    {
        return Examples::BuildingSelectionExample::GetName();
    }
    
    
    IExample* BuildingSelectionExampleFactory::CreateExample() const
    {
        Eegeo::Modules::CollisionVisualizationModule* pCollisionVisualizationModule = CreateCollisionVisualizationModule(m_world);
        Eegeo::Modules::BuildingFootprintsModule* pBuildingFootprintsModule = CreateBuildingFootprintsModule(m_world, *pCollisionVisualizationModule);
        
        Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
        
        Eegeo::Collision::EnvironmentRayCaster* pRayCaster = new Eegeo::Collision::EnvironmentRayCaster
        (
            mapModule.GetAggregateCollisionBvhProvider(),
            mapModule.GetEnvironmentFlatteningService()
        );
        
        return new BuildingSelectionExample(m_defaultCameraControllerFactory.Create(),
                                            m_globeCameraTouchController,
                                            pCollisionVisualizationModule,
                                            pBuildingFootprintsModule,
                                            pRayCaster);
    }

}