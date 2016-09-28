// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IExampleFactory.h"
#include "EegeoRootDeclarations.h"
#include "ScreenPropertiesProvider.h"
#include "ConfigSections.h"
#include "IVRModeTracker.h"

namespace Examples
{
    class VRCardboardExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        const Eegeo::Config::DeviceSpec& m_deviceSpecs;
        const IScreenPropertiesProvider& m_screenPropertiesProvider;
        DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
        Examples::IVRModeTracker& m_vrModeTracker;
        
    public:
        VRCardboardExampleFactory(Eegeo::EegeoWorld& world,
                                  const Eegeo::Config::DeviceSpec& deviceSpecs,
                                  DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                  const IScreenPropertiesProvider& screenPropertiesProvider,
								  Examples::IVRModeTracker& vrModeTracker);
        
        std::string ExampleName() const;
        
        IExample* CreateExample() const;
    };
}
