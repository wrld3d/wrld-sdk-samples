// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__CameraTransitionExampleFactory__
#define __ExampleApp__CameraTransitionExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
class CameraTransitionExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	DefaultCameraControllerFactory& m_defaultCameraControllerFactory;

public:
	CameraTransitionExampleFactory(Eegeo::EegeoWorld& world,
	                               DefaultCameraControllerFactory& defaultCameraControllerFactory);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__CameraTransitionExampleFactory__) */
