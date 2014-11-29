// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ResourceSpatialQueryExampleFactory.h"
#include "ResourceSpatialQueryExample.h"

using namespace Examples;

ResourceSpatialQueryExampleFactory::ResourceSpatialQueryExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
{

}

IExample* ResourceSpatialQueryExampleFactory::CreateExample() const
{
	return new Examples::ResourceSpatialQueryExample(m_world.GetResourceSpatialQueryService(),
	        m_defaultCameraControllerFactory.Create());
}

std::string ResourceSpatialQueryExampleFactory::ExampleName() const
{
	return Examples::ResourceSpatialQueryExample::GetName();
}


