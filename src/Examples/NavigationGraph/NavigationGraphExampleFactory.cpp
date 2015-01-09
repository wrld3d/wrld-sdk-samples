// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "NavigationGraphExampleFactory.h"
#include "NavigationGraphExample.h"
#include "DefaultCameraControllerFactory.h"
#include "TransportModelModule.h"

namespace Examples
{

NavigationGraphExampleFactory::NavigationGraphExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* NavigationGraphExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::Layers::TransportModelModule& transportModelModule = m_world.GetTransportModelModule();
    
	return new Examples::NavigationGraphExample(transportModelModule.GetRoadNavigationGraphRepository(),
                                                m_defaultCameraControllerFactory.Create(),
                                                m_globeCameraTouchController);
}

std::string NavigationGraphExampleFactory::ExampleName() const
{
	return Examples::NavigationGraphExample::GetName();
}

}