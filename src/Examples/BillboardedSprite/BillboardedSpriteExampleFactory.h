// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

// Change to include guards
#pragma once

#include "IExampleFactory.h"
#include "GlobeCameraExampleBase.h"
#include "EegeoWorld.h"

namespace Examples
{
    class BillboardedSpriteExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;

    public:
        BillboardedSpriteExampleFactory(Eegeo::EegeoWorld& world,
                                        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController);

        std::string ExampleName() const;

        IExample* CreateExample() const;
    };
}
