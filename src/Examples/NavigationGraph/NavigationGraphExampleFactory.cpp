// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "NavigationGraphExampleFactory.h"
#include "NavigationGraphExample.h"

#include "TransportModelModule.h"

using namespace Examples;

NavigationGraphExampleFactory::NavigationGraphExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
{

}

IExample* NavigationGraphExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::Layers::TransportModelModule& transportModelModule = m_world.GetTransportModelModule();
    
	return new Examples::NavigationGraphExample(transportModelModule.GetRoadNavigationGraphRepository(),
                                                m_defaultCameraControllerFactory.Create());
}

std::string NavigationGraphExampleFactory::ExampleName() const
{
	return Examples::NavigationGraphExample::GetName();
}
