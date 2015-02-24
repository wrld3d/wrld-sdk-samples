// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "GeofenceExampleFactory.h"
#include "GeofenceExample.h"
#include "DataModule.h"

namespace Examples
{
    GeofenceExampleFactory::GeofenceExampleFactory(Eegeo::EegeoWorld& world,
                                           DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
    : m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    {
        
    }
    
    IExample* GeofenceExampleFactory::CreateExample() const
    {
        return new Examples::GeofenceExample(m_defaultCameraControllerFactory.Create(),
                                             m_globeCameraTouchController,
                                             m_world.GetDataModule().GetGeofenceModule().GetController());

    }
    
    std::string GeofenceExampleFactory::ExampleName() const
    {
        return Examples::GeofenceExample::GetName();
    }
}
