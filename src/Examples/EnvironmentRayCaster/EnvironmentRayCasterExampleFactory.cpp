// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EnvironmentRayCasterExampleFactory.h"
#include "EnvironmentRayCasterExample.h"
#include "DefaultCameraControllerFactory.h"
#include "CollisionMeshResourceRepository.h"
#include "AggregateCollisionBvhProvider.h"

#include "DebugRenderingModule.h"

namespace Examples
{
    
    EnvironmentRayCasterExampleFactory::EnvironmentRayCasterExampleFactory(Eegeo::EegeoWorld& world,
                                                       DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
    : m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    {
        
    }
    
    IExample* EnvironmentRayCasterExampleFactory::CreateExample() const
    {
        Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule = m_world.GetDebugRenderingModule();
        Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
        
        return new Examples::EnvironmentRayCasterExample(
                                               mapModule.GetAggregateCollisionBvhProvider(),
                                               mapModule.GetEnvironmentFlatteningService(),
                                               debugRenderingModule.GetDebugRenderer(),
                                               m_defaultCameraControllerFactory.Create(),
                                               m_globeCameraTouchController);
    }
    
    std::string EnvironmentRayCasterExampleFactory::ExampleName() const
    {
        return Examples::EnvironmentRayCasterExample::GetName();
    }
    
}