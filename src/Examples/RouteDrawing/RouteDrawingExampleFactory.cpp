// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteDrawingExampleFactory.h"
#include "RouteDrawingExample.h"
#include "DefaultCameraControllerFactory.h"
#include "RoutesModule.h"

namespace Examples
{



RouteDrawingExampleFactory::RouteDrawingExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* RouteDrawingExampleFactory::CreateExample() const
{
    Eegeo::Modules::RoutesModule& routesModule = m_world.GetRoutesModule();
    
	return new Examples::RouteDrawingExample(routesModule.GetRouteService(),
                                             m_world,
                                             m_defaultCameraControllerFactory.Create(),
                                             m_globeCameraTouchController);
}

std::string RouteDrawingExampleFactory::ExampleName() const
{
	return Examples::RouteDrawingExample::GetName();
}

}

