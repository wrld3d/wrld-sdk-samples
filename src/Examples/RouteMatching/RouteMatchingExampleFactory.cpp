// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteMatchingExampleFactory.h"
#include "RouteMatchingExample.h"

using namespace Examples;

#include "RoutesModule.h"

RouteMatchingExampleFactory::RouteMatchingExampleFactory(Eegeo::EegeoWorld& world,
        const IRouteMatchingExampleViewFactory& routeMatchingViewFactory,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
	, m_routeMatchingViewFactory(routeMatchingViewFactory)
{

}

IExample* RouteMatchingExampleFactory::CreateExample() const
{
    Eegeo::Modules::RoutesModule& routesModule = m_world.GetRoutesModule();
    
	return new Examples::RouteMatchingExample(routesModule.GetRouteService(),
	        m_world,
	        m_routeMatchingViewFactory,
	        m_globeCameraController);
}

std::string RouteMatchingExampleFactory::ExampleName() const
{
	return Examples::RouteMatchingExample::GetName();
}
