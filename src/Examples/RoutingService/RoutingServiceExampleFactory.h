// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RoutingServiceExampleFactory__
#define __ExampleApp__RoutingServiceExampleFactory__

#include "IExampleFactory.h"
#include "GlobeCameraExampleBase.h"
#include "EegeoWorld.h"
#include "Interiors.h"

namespace Examples
{
class IRoutingServiceExampleViewFactory;

class RoutingServiceExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
    DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;
    IRoutingServiceExampleViewFactory& m_routingServiceViewFactory;
    
public:
	RoutingServiceExampleFactory(Eegeo::EegeoWorld& world,
	                           DefaultCameraControllerFactory& defaultCameraControllerFactory,
                               Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                               IRoutingServiceExampleViewFactory& routingServiceViewFactory);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__RoutingServiceExampleFactory__) */
