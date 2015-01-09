// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "TrafficCongestionExampleFactory.h"
#include "TrafficCongestionExample.h"
#include "DefaultCameraControllerFactory.h"
#include "TrafficModule.h"

namespace Examples
{

TrafficCongestionExampleFactory::TrafficCongestionExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* TrafficCongestionExampleFactory::CreateExample() const
{
    Eegeo::Modules::TrafficModule& trafficModule = m_world.GetTrafficModule();
    
	return new Examples::TrafficCongestionExample(trafficModule.GetTrafficCongestionService(),
                                                  m_defaultCameraControllerFactory.Create(),
                                                  m_globeCameraTouchController);
}

std::string TrafficCongestionExampleFactory::ExampleName() const
{
	return Examples::TrafficCongestionExample::GetName();
}

}
