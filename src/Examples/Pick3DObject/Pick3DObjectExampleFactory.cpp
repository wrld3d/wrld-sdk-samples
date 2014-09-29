// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "Pick3DObjectExampleFactory.h"
#include "Pick3DObjectExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"

#include "DebugRenderingModule.h"

using namespace Examples;

Pick3DObjectExampleFactory::Pick3DObjectExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* Pick3DObjectExampleFactory::CreateExample() const
{
    Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule = m_world.GetDebugRenderingModule();
    
	return new Examples::Pick3DObjectExample(Eegeo::Space::LatLongAltitude::FromECEF(m_globeCameraController.GetEcefInterestPoint()),
                                             m_world.GetScreenProperties(),
                                             debugRenderingModule.GetDebugRenderer(),
                                             m_globeCameraController);
}

std::string Pick3DObjectExampleFactory::ExampleName() const
{
	return Examples::Pick3DObjectExample::GetName();
}

