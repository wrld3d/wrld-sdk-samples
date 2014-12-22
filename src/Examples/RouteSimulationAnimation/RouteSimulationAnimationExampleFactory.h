// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RouteSimulationAnimationExampleFactory__
#define __ExampleApp__RouteSimulationAnimationExampleFactory__

#include "IExampleFactory.h"
#include "GlobeCameraExampleBase.h"
#include "EegeoWorld.h"
#include "ScreenPropertiesProvider.h"

namespace Examples
{
class RouteSimulationAnimationExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
    DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;
    const IScreenPropertiesProvider& m_screenPropertiesProvider;
	Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory* m_pRouteSimulationGlobeCameraControllerFactory;

public:
	RouteSimulationAnimationExampleFactory(Eegeo::EegeoWorld& world,
	                                       DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                           const IScreenPropertiesProvider& screenPropertiesProvider);

	~RouteSimulationAnimationExampleFactory();

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__RouteSimulationAnimationExampleFactory__) */
