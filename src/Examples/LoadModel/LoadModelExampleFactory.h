// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__LoadModelExampleFactory__
#define __ExampleApp__LoadModelExampleFactory__

#include "IExampleFactory.h"
#include "GlobeCameraExampleBase.h"
#include "EegeoWorld.h"

namespace Examples
{
class LoadModelExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
    DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;

public:
	LoadModelExampleFactory(Eegeo::EegeoWorld& world,
	                        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                            Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* defined(__ExampleApp__LoadModelExampleFactory__) */
