// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ResourceSpatialQueryExampleFactory.h"
#include "ResourceSpatialQueryExample.h"
#include "DefaultCameraControllerFactory.h"

namespace Examples
{

ResourceSpatialQueryExampleFactory::ResourceSpatialQueryExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* ResourceSpatialQueryExampleFactory::CreateExample() const
{
	return new Examples::ResourceSpatialQueryExample(m_world.GetResourceSpatialQueryService(),
                                                     m_defaultCameraControllerFactory.Create(),
                                                     m_globeCameraTouchController);
}

std::string ResourceSpatialQueryExampleFactory::ExampleName() const
{
	return Examples::ResourceSpatialQueryExample::GetName();
}

}
