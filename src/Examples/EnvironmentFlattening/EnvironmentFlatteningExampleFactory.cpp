// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EnvironmentFlatteningExampleFactory.h"
#include "EnvironmentFlatteningExample.h"
#include "DefaultCameraControllerFactory.h"
#include "MapModule.h"

namespace Examples
{

EnvironmentFlatteningExampleFactory::EnvironmentFlatteningExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* EnvironmentFlatteningExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    
	return new Examples::EnvironmentFlatteningExample(mapModule.GetEnvironmentFlatteningService(),
	        m_defaultCameraControllerFactory.Create(),
            m_globeCameraTouchController);
}

std::string EnvironmentFlatteningExampleFactory::ExampleName() const
{
	return Examples::EnvironmentFlatteningExample::GetName();
}

}

