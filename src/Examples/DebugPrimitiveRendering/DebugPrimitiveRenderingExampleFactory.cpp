// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DebugPrimitiveRenderingExampleFactory.h"
#include "DebugPrimitiveRenderingExample.h"
#include "DefaultCameraControllerFactory.h"
#include "DebugRenderingModule.h"

namespace Examples
{

DebugPrimitiveRenderingExampleFactory::DebugPrimitiveRenderingExampleFactory(Eegeo::EegeoWorld& world,
                                                                             DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* DebugPrimitiveRenderingExampleFactory::CreateExample() const
{
    Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule = m_world.GetDebugRenderingModule();
    
	return new Examples::DebugPrimitiveRenderingExample(debugRenderingModule.GetDebugRenderer(),
                                                        m_defaultCameraControllerFactory.Create(),
                                                        m_globeCameraTouchController);
}

std::string DebugPrimitiveRenderingExampleFactory::ExampleName() const
{
	return Examples::DebugPrimitiveRenderingExample::GetName();
}

}
