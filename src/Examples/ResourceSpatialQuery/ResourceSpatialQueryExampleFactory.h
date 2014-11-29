// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ResourceSpatialQueryExampleFactory__
#define __ExampleApp__ResourceSpatialQueryExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
class ResourceSpatialQueryExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	DefaultCameraControllerFactory& m_defaultCameraControllerFactory;

public:
	ResourceSpatialQueryExampleFactory(Eegeo::EegeoWorld& world,
	                                   DefaultCameraControllerFactory& defaultCameraControllerFactory);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__ResourceSpatialQueryExampleFactory__) */
