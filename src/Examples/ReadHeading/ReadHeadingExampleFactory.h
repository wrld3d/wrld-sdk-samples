// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ReadHeadingExampleFactory__
#define __ExampleApp__ReadHeadingExampleFactory__

#include "IExampleFactory.h"
#include "GlobeCamera.h"
#include "EegeoRootDeclarations.h"

namespace Examples
{
    class ReadHeadingExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;

    public:
        ReadHeadingExampleFactory(
                                  Eegeo::EegeoWorld& world,
                                  DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                  Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController
        );

        std::string ExampleName() const;

        IExample* CreateExample() const;
    };
}


#endif /* defined(__ExampleApp__ReadHeadingExampleFactory__) */
