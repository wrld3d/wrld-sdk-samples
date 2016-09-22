// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RoutingServiceExampleFactory.h"
#include "RoutingServiceExample.h"
#include "DefaultCameraControllerFactory.h"
#include "RoutesModule.h"
#include "IPlatformAbstractionModule.h"
#include "MapModule.h"
#include "InteriorsPresentationModule.h"
#include "IRoutingServiceExampleViewFactory.h"

namespace Examples
{

RoutingServiceExampleFactory::RoutingServiceExampleFactory(Eegeo::EegeoWorld& world,
                                                           DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                                           IRoutingServiceExampleViewFactory& routingServiceViewFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    , m_routingServiceViewFactory(routingServiceViewFactory)
{

}

IExample* RoutingServiceExampleFactory::CreateExample() const
{
    Eegeo::Modules::RoutesModule& routesModule = m_world.GetRoutesModule();
    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = m_world.GetPlatformAbstractionModule();

	return new Examples::RoutingServiceExample(routesModule.GetRouteService(),
                                               routesModule.GetRoutingRequestBuilder(),
                                               platformAbstractionModule.GetWebLoadRequestFactory(),
                                               m_world,
                                               m_defaultCameraControllerFactory.Create(),
                                               m_globeCameraTouchController,
                                               m_routingServiceViewFactory);
}

std::string RoutingServiceExampleFactory::ExampleName() const
{
	return Examples::RoutingServiceExample::GetName();
}

}

