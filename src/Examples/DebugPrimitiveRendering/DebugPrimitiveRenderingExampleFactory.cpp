// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DebugPrimitiveRenderingExampleFactory.h"
#include "DebugPrimitiveRenderingExample.h"

#include "DebugRenderingModule.h"

using namespace Examples;

DebugPrimitiveRenderingExampleFactory::DebugPrimitiveRenderingExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
{

}

IExample* DebugPrimitiveRenderingExampleFactory::CreateExample() const
{
    Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule = m_world.GetDebugRenderingModule();
    
	return new Examples::DebugPrimitiveRenderingExample(debugRenderingModule.GetDebugRenderer(),
	        m_defaultCameraControllerFactory.Create());
}

std::string DebugPrimitiveRenderingExampleFactory::ExampleName() const
{
	return Examples::DebugPrimitiveRenderingExample::GetName();
}

