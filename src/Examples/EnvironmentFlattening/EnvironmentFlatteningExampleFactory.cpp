// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EnvironmentFlatteningExampleFactory.h"
#include "EnvironmentFlatteningExample.h"

#include "MapModule.h"

using namespace Examples;

EnvironmentFlatteningExampleFactory::EnvironmentFlatteningExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* EnvironmentFlatteningExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    
	return new Examples::EnvironmentFlatteningExample(mapModule.GetEnvironmentFlatteningService(),
	        m_globeCameraController);
}

std::string EnvironmentFlatteningExampleFactory::ExampleName() const
{
	return Examples::EnvironmentFlatteningExample::GetName();
}
