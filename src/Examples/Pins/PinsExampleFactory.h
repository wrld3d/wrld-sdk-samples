// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__PinsExampleFactory__
#define __ExampleApp__PinsExampleFactory__

#include "IExampleFactory.h"
#include "GlobeCameraExampleBase.h"
#include "EegeoWorld.h"
#include "ScreenPropertiesProvider.h"

namespace Examples
{
class PinsExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
    DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;
    const IScreenPropertiesProvider& m_screenPropertiesProvider;

public:
	PinsExampleFactory(Eegeo::EegeoWorld& world,
                       DefaultCameraControllerFactory& defaultCameraControllerFactory,
                       Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                       const IScreenPropertiesProvider& screenPropertiesProvider);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* defined(__ExampleApp__PinsExampleFactory__) */
