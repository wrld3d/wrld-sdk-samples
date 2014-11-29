// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__DynamicText3DExampleFactory__
#define __ExampleApp__DynamicText3DExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
class DynamicText3DExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	DefaultCameraControllerFactory& m_defaultCameraControllerFactory;

public:
	DynamicText3DExampleFactory(Eegeo::EegeoWorld& world,
	                            DefaultCameraControllerFactory& defaultCameraControllerFactory);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* defined(__ExampleApp__DynamicText3DExampleFactory__) */
