// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "Pick3DObjectExampleFactory.h"
#include "Pick3DObjectExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"
#include "DefaultCameraControllerFactory.h"
#include "DebugRenderingModule.h"

namespace Examples
{

Pick3DObjectExampleFactory::Pick3DObjectExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* Pick3DObjectExampleFactory::CreateExample() const
{
    Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule = m_world.GetDebugRenderingModule();
    
	return new Examples::Pick3DObjectExample(
                                             debugRenderingModule.GetDebugRenderer(),
                                             m_defaultCameraControllerFactory.Create(),
                                             m_globeCameraTouchController);
}

std::string Pick3DObjectExampleFactory::ExampleName() const
{
	return Examples::Pick3DObjectExample::GetName();
}
}

