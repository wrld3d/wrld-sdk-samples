// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__CameraTransitionExampleFactory__
#define __ExampleApp__CameraTransitionExampleFactory__

#include "IExampleFactory.h"
#include "GlobeCameraExampleBase.h"
#include "EegeoWorld.h"

namespace Examples
{
class CameraTransitionExampleFactory : public IExampleFactory
{
    DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;

public:
	CameraTransitionExampleFactory(Eegeo::EegeoWorld& world,
	                               DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                   Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__CameraTransitionExampleFactory__) */
