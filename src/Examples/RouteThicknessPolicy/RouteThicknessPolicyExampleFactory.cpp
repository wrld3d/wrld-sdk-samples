// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteThicknessPolicyExampleFactory.h"
#include "RouteThicknessPolicyExample.h"

#include "RoutesModule.h"

using namespace Examples;

RouteThicknessPolicyExampleFactory::RouteThicknessPolicyExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* RouteThicknessPolicyExampleFactory::CreateExample() const
{
    Eegeo::Modules::RoutesModule& routesModule = m_world.GetRoutesModule();
    
	return new Examples::RouteThicknessPolicyExample(routesModule.GetRouteService(),
	        m_world,
	        m_globeCameraController);
}

std::string RouteThicknessPolicyExampleFactory::ExampleName() const
{
	return Examples::RouteThicknessPolicyExample::GetName();
}
