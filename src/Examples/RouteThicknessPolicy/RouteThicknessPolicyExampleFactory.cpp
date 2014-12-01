// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteThicknessPolicyExampleFactory.h"
#include "RouteThicknessPolicyExample.h"
#include "DefaultCameraControllerFactory.h"
#include "RoutesModule.h"

namespace Examples
{

RouteThicknessPolicyExampleFactory::RouteThicknessPolicyExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* RouteThicknessPolicyExampleFactory::CreateExample() const
{
    Eegeo::Modules::RoutesModule& routesModule = m_world.GetRoutesModule();
    
	return new Examples::RouteThicknessPolicyExample(routesModule.GetRouteService(),
                                                     m_world,
                                                     m_defaultCameraControllerFactory.Create(),
                                                     m_globeCameraTouchController);
}

std::string RouteThicknessPolicyExampleFactory::ExampleName() const
{
	return Examples::RouteThicknessPolicyExample::GetName();
}
}
