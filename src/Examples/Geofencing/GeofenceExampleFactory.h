// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IExampleFactory.h"
#include "IExample.h"
#include "DefaultCameraControllerFactory.h"
#include "EegeoWorld.h"

namespace Examples
{
    class GeofenceExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;
        
    public:
        GeofenceExampleFactory(Eegeo::EegeoWorld& world,
                               DefaultCameraControllerFactory& defaultCameraControllerFactory,
                               Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController);
        
        std::string ExampleName() const;
        
        IExample* CreateExample() const;
    };
}