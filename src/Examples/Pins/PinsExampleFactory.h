// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__PinsExampleFactory__
#define __ExampleApp__PinsExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
class PinsExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	DefaultCameraControllerFactory& m_defaultCameraControllerFactory;

public:
	PinsExampleFactory(Eegeo::EegeoWorld& world,
	                   DefaultCameraControllerFactory& defaultCameraControllerFactory);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* defined(__ExampleApp__PinsExampleFactory__) */
