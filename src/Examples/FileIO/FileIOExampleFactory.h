// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__FileIOExampleFactory__
#define __ExampleApp__FileIOExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
class FileIOExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	DefaultCameraControllerFactory& m_defaultCameraControllerFactory;

public:
	FileIOExampleFactory(Eegeo::EegeoWorld& world,
	                     DefaultCameraControllerFactory& defaultCameraControllerFactory);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__FileIOExampleFactory__) */
