// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ToggleTrafficExampleFactory.h"
#include "ToggleTrafficExample.h"

#include "TrafficModule.h"

using namespace Examples;

ToggleTrafficExampleFactory::ToggleTrafficExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* ToggleTrafficExampleFactory::CreateExample() const
{
    Eegeo::Modules::TrafficModule& trafficModule = m_world.GetTrafficModule();
    
	return new Examples::ToggleTrafficExample(trafficModule.GetTrafficSimulationController(),
	        m_globeCameraController);
}

std::string ToggleTrafficExampleFactory::ExampleName() const
{
	return Examples::ToggleTrafficExample::GetName();
}
