// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "LoadModelExampleFactory.h"
#include "LoadModelExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"
#include "LocalAsyncTextureLoader.h"

#include "IPlatformAbstractionModule.h"
#include "AsyncLoadersModule.h"
#include "LightingModule.h"

using namespace Examples;

LoadModelExampleFactory::LoadModelExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* LoadModelExampleFactory::CreateExample() const
{
    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = m_world.GetPlatformAbstractionModule();
    Eegeo::Modules::Core::AsyncLoadersModule& asyncLoadersModule = m_world.GetAsyncLoadersModule();
    Eegeo::Modules::Core::LightingModule& lightingModule = m_world.GetLightingModule();
    
	return new Examples::LoadModelExample(Eegeo::Space::LatLongAltitude::FromECEF(m_globeCameraController.GetEcefInterestPoint()),
	                                      platformAbstractionModule.GetFileIO(),
	                                      asyncLoadersModule.GetLocalAsyncTextureLoader(),
	                                      lightingModule.GetGlobalFogging(),
	                                      m_globeCameraController);
}

std::string LoadModelExampleFactory::ExampleName() const
{
	return Examples::LoadModelExample::GetName();
}

