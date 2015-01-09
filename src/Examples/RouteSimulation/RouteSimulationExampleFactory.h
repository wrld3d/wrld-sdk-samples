// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RouteSimulationExampleFactory__
#define __ExampleApp__RouteSimulationExampleFactory__

#include "IExampleFactory.h"
#include "GlobeCameraExampleBase.h"
#include "EegeoWorld.h"
#include "IRouteSimulationExampleViewFactory.h"
#include "ScreenPropertiesProvider.h"

namespace Examples
{
class RouteSimulationExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	const IRouteSimulationExampleViewFactory& m_routeSimulationViewFactory;
    DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;
    const IScreenPropertiesProvider& m_screenPropertiesProvider;
	Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory* m_pRouteSimulationGlobeCameraControllerFactory;

public:
	RouteSimulationExampleFactory(Eegeo::EegeoWorld& world,
	                              DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                  Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                  const IScreenPropertiesProvider& screenPropertiesProvider,
	                              const IRouteSimulationExampleViewFactory& routeSimulationViewFactory);

	~RouteSimulationExampleFactory();

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* defined(__ExampleApp__RouteSimulationExampleFactory__) */
