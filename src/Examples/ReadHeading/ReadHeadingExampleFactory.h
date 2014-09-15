// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ReadHeadingExampleFactory__
#define __ExampleApp__ReadHeadingExampleFactory__

#include "IExampleFactory.h"
#include "Camera.h"

namespace Examples
{
    class ReadHeadingExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;

    public:
        ReadHeadingExampleFactory(
        	Eegeo::EegeoWorld& world,
            Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController
        );

        std::string ExampleName() const;

        IExample* CreateExample() const;
    };
}


#endif /* defined(__ExampleApp__ReadHeadingExampleFactory__) */
