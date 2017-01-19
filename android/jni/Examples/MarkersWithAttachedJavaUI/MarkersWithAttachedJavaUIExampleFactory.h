// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"
#include "AndroidNativeState.h"
#include "ScreenPropertiesProvider.h"
#include <string>

namespace Examples
{
class MarkersWithAttachedJavaUIExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	AndroidNativeState& m_nativeState;
	DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;
    const IScreenPropertiesProvider& m_screenPropertiesProvider;

public:
    MarkersWithAttachedJavaUIExampleFactory(
	    Eegeo::EegeoWorld& world,
	    AndroidNativeState& nativeState,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
        const IScreenPropertiesProvider& screenPropertiesProvider);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}
