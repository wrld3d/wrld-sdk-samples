// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ReadHeadingExampleFactory.h"
#include "ReadHeadingExample.h"
#include "Location.h"
#include "EegeoWorld.h"
#include "DefaultCameraControllerFactory.h"
#include "DebugRenderingModule.h"

namespace Examples
{

ReadHeadingExampleFactory::ReadHeadingExampleFactory(
                                                     Eegeo::EegeoWorld& world,
                                                     DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
: m_world(world)
, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
, m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* ReadHeadingExampleFactory::CreateExample() const
{
    Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule = m_world.GetDebugRenderingModule();
	
    return new Examples::ReadHeadingExample(
		m_world,
		m_defaultCameraControllerFactory.Create(),
        m_globeCameraTouchController,
		debugRenderingModule.GetDebugRenderer(),
		m_world.GetLocationService()
	);
}

std::string ReadHeadingExampleFactory::ExampleName() const
{
	return Examples::ReadHeadingExample::GetName();
}

}