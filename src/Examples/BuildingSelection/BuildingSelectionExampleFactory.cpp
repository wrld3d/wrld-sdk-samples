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
    BuildingSelectionExampleFactory::BuildingSelectionExampleFactory(Eegeo::EegeoWorld& world,
                                    DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                    Eegeo::Modules::CollisionVisualizationModule& collisionVisualizationModule,
                                    Eegeo::Modules::BuildingFootprintsModule& buildingFootprintsModule)
    : m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    , m_collisionVisualizationModule(collisionVisualizationModule)
    , m_buildingFootprintsModule(buildingFootprintsModule)
    {}
    
    std::string BuildingSelectionExampleFactory::ExampleName() const
    {
        return Examples::BuildingSelectionExample::GetName();
    }
    
    
    IExample* BuildingSelectionExampleFactory::CreateExample() const
    {
        Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
        
        Eegeo::Collision::EnvironmentRayCaster* pRayCaster = new Eegeo::Collision::EnvironmentRayCaster
        (
            mapModule.GetAggregateCollisionBvhProvider(),
            mapModule.GetEnvironmentFlatteningService()
        );
        
        return new BuildingSelectionExample(m_defaultCameraControllerFactory.Create(),
                                            m_globeCameraTouchController,
                                            m_collisionVisualizationModule,
                                            m_buildingFootprintsModule,
                                            pRayCaster);
    }

}