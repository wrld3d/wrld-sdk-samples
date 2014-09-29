// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteDrawingExampleFactory.h"
#include "RouteDrawingExample.h"

using namespace Examples;

#include "RoutesModule.h"

RouteDrawingExampleFactory::RouteDrawingExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* RouteDrawingExampleFactory::CreateExample() const
{
    Eegeo::Modules::RoutesModule& routesModule = m_world.GetRoutesModule();
    
	return new Examples::RouteDrawingExample(routesModule.GetRouteService(),
	        m_world,
	        m_globeCameraController);
}

std::string RouteDrawingExampleFactory::ExampleName() const
{
	return Examples::RouteDrawingExample::GetName();
}

