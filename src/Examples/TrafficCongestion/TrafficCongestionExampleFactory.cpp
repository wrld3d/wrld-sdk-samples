// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "TrafficCongestionExampleFactory.h"
#include "TrafficCongestionExample.h"

#include "TrafficModule.h"

using namespace Examples;

TrafficCongestionExampleFactory::TrafficCongestionExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
{

}

IExample* TrafficCongestionExampleFactory::CreateExample() const
{
    Eegeo::Modules::TrafficModule& trafficModule = m_world.GetTrafficModule();
    
	return new Examples::TrafficCongestionExample(trafficModule.GetTrafficCongestionService(),
	        m_defaultCameraControllerFactory.Create());
}

std::string TrafficCongestionExampleFactory::ExampleName() const
{
	return Examples::TrafficCongestionExample::GetName();
}
