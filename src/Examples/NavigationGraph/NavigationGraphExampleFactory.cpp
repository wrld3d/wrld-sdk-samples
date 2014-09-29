// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "NavigationGraphExampleFactory.h"
#include "NavigationGraphExample.h"

#include "TransportModelModule.h"

using namespace Examples;

NavigationGraphExampleFactory::NavigationGraphExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* NavigationGraphExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::Layers::TransportModelModule& transportModelModule = m_world.GetTransportModelModule();
    
	return new Examples::NavigationGraphExample(transportModelModule.GetRoadNavigationGraphRepository(),
                                                m_globeCameraController);
}

std::string NavigationGraphExampleFactory::ExampleName() const
{
	return Examples::NavigationGraphExample::GetName();
}
