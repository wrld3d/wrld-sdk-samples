// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ToggleTrafficExampleFactory.h"
#include "ToggleTrafficExample.h"
#include "DefaultCameraControllerFactory.h"
#include "TrafficModule.h"

namespace Examples
{

ToggleTrafficExampleFactory::ToggleTrafficExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* ToggleTrafficExampleFactory::CreateExample() const
{
    Eegeo::Modules::TrafficModule& trafficModule = m_world.GetTrafficModule();
    
	return new Examples::ToggleTrafficExample(trafficModule.GetTrafficSimulationController(),
                                              m_defaultCameraControllerFactory.Create(),
                                              m_globeCameraTouchController);
}

std::string ToggleTrafficExampleFactory::ExampleName() const
{
	return Examples::ToggleTrafficExample::GetName();
}
}
