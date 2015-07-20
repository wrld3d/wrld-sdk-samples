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
#include "SceneModelsModule.h"
#include "DebugRenderingModule.h"

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
    Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule = m_world.GetDebugRenderingModule();
    Eegeo::Modules::Core::SceneModelsModule& sceneModelsModule = m_world.GetCoreModule().GetSceneModelsModule();
    
	return new Examples::LoadModelExample(
                                          sceneModelsModule.GetLocalModelLoader(),
                                          sceneModelsModule.GetMaterialResourceRepository(),
                                          sceneModelsModule.GetSceneModelRenderableFilter(),
                                          debugRenderingModule.GetDebugRenderer(),
	                                      m_defaultCameraControllerFactory.Create(),
                                          m_globeCameraTouchController);
}

std::string LoadModelExampleFactory::ExampleName() const
{
	return Examples::LoadModelExample::GetName();
}

}

