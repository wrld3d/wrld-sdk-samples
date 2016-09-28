// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "VRCardboardExampleFactory.h"
#include "VRCardboardExample.h"
#include "EegeoWorld.h"
#include "ResourceCeilingProvider.h"
#include "DefaultCameraControllerFactory.h"
#include "MapModule.h"

namespace Examples
{

	VRCardboardExampleFactory::VRCardboardExampleFactory(Eegeo::EegeoWorld& world,
                                                         const Eegeo::Config::DeviceSpec& deviceSpecs,
                                                         DefaultCameraControllerFactory&defaultCameraControllerFactory,
                                                         const IScreenPropertiesProvider& screenPropertiesProvider,
														 Examples::IVRModeTracker& vrModeTracker)
    : m_world(world)
    , m_deviceSpecs(deviceSpecs)
    , m_screenPropertiesProvider(screenPropertiesProvider)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
	, m_vrModeTracker(vrModeTracker)
	{
    
	}

	IExample* VRCardboardExampleFactory::CreateExample() const
	{
	    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();

	    return new Examples::VRCardboardExample(m_world,
	                                            m_deviceSpecs,
	                                            mapModule.GetResourceCeilingProvider(),
	                                            m_defaultCameraControllerFactory.Create(),
												m_screenPropertiesProvider,
												m_vrModeTracker);
	}

	std::string VRCardboardExampleFactory::ExampleName() const
	{
		return Examples::VRCardboardExample::GetName();
	}
}
