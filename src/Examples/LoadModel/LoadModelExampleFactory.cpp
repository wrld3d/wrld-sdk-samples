// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "LoadModelExampleFactory.h"
#include "LoadModelExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"
#include "LocalAsyncTextureLoader.h"
#include "DefaultCameraControllerFactory.h"
#include "IPlatformAbstractionModule.h"
#include "AsyncLoadersModule.h"
#include "LightingModule.h"

namespace Examples
{

LoadModelExampleFactory::LoadModelExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* LoadModelExampleFactory::CreateExample() const
{
    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = m_world.GetPlatformAbstractionModule();
    Eegeo::Modules::Core::AsyncLoadersModule& asyncLoadersModule = m_world.GetAsyncLoadersModule();
    Eegeo::Modules::Core::LightingModule& lightingModule = m_world.GetLightingModule();
    
	return new Examples::LoadModelExample(
	                                      platformAbstractionModule.GetFileIO(),
	                                      asyncLoadersModule.GetLocalAsyncTextureLoader(),
	                                      lightingModule.GetGlobalFogging(),
	                                      m_defaultCameraControllerFactory.Create(),
                                          m_globeCameraTouchController);
}

std::string LoadModelExampleFactory::ExampleName() const
{
	return Examples::LoadModelExample::GetName();
}

}

