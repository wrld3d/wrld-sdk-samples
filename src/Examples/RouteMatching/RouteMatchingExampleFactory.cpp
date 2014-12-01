// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteMatchingExampleFactory.h"
#include "RouteMatchingExample.h"
#include "DefaultCameraControllerFactory.h"
#include "RoutesModule.h"

namespace Examples
{



RouteMatchingExampleFactory::RouteMatchingExampleFactory(Eegeo::EegeoWorld& world,
                                                         const IRouteMatchingExampleViewFactory& routeMatchingViewFactory,
                                                         DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                         Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
	, m_routeMatchingViewFactory(routeMatchingViewFactory)
{

}

IExample* RouteMatchingExampleFactory::CreateExample() const
{
    Eegeo::Modules::RoutesModule& routesModule = m_world.GetRoutesModule();
    
	return new Examples::RouteMatchingExample(routesModule.GetRouteService(),
                                              m_world,
                                              m_routeMatchingViewFactory,
                                              m_defaultCameraControllerFactory.Create(),
                                              m_globeCameraTouchController);
}

std::string RouteMatchingExampleFactory::ExampleName() const
{
	return Examples::RouteMatchingExample::GetName();
}

}
