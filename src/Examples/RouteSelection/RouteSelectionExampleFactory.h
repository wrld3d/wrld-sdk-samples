// Copyright eeGeo Ltd 2016, All Rights Reserved

#ifndef __ExampleApp__RouteSelectionExampleFactory__
#define __ExampleApp__RouteSelectionExampleFactory__

#include "IExampleFactory.h"
#include "GlobeCameraExampleBase.h"
#include "EegeoWorld.h"

namespace Examples
{
class RouteSelectionExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
    DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;

public:
	RouteSelectionExampleFactory(Eegeo::EegeoWorld& world,
	                           DefaultCameraControllerFactory& defaultCameraControllerFactory,
                               Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__RouteSelectionExampleFactory__) */
