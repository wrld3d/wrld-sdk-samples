// Copyright eeGeo Ltd 2015, All Rights Reserved

#pragma once

#include "IExampleFactory.h"
#include "GlobeCameraExampleBase.h"
#include "EegeoWorld.h"

namespace Examples
{
    class StencilAreaExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;
        
    public:
        StencilAreaExampleFactory(Eegeo::EegeoWorld& world,
                                DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController);
        
        std::string ExampleName() const;
        
        IExample* CreateExample() const;
    };
}