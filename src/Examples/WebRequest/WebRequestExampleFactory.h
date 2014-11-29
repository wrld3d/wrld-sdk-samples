// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__WebRequestExampleFactory__
#define __ExampleApp__WebRequestExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
class WebRequestExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	DefaultCameraControllerFactory& m_defaultCameraControllerFactory;

public:
	WebRequestExampleFactory(Eegeo::EegeoWorld& world,
	                         DefaultCameraControllerFactory& defaultCameraControllerFactory);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__WebRequestExampleFactory__) */
