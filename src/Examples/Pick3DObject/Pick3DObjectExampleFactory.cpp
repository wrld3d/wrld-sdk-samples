// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "Pick3DObjectExampleFactory.h"
#include "Pick3DObjectExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"

#include "DebugRenderingModule.h"

using namespace Examples;

Pick3DObjectExampleFactory::Pick3DObjectExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
{

}

IExample* Pick3DObjectExampleFactory::CreateExample() const
{
    Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule = m_world.GetDebugRenderingModule();
    
	return new Examples::Pick3DObjectExample(
                                             debugRenderingModule.GetDebugRenderer(),
                                             m_defaultCameraControllerFactory.Create());
}

std::string Pick3DObjectExampleFactory::ExampleName() const
{
	return Examples::Pick3DObjectExample::GetName();
}

