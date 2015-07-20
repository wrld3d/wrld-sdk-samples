// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PODAnimationExampleFactory.h"
#include "PODAnimationExample.h"
#include "DefaultCameraControllerFactory.h"
#include "LocalAsyncTextureLoader.h"

#include "IPlatformAbstractionModule.h"
#include "RenderingModule.h"
#include "AsyncLoadersModule.h"
#include "LightingModule.h"
#include "SceneModelsModule.h"

namespace Examples
{

PODAnimationExampleFactory::PODAnimationExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* PODAnimationExampleFactory::CreateExample() const
{
    Eegeo::Modules::Core::SceneModelsModule& sceneModulesModule = m_world.GetCoreModule().GetSceneModelsModule();
    
	return new Examples::PODAnimationExample(sceneModulesModule.GetLocalModelLoader(),
                                             sceneModulesModule.GetSceneModelRenderableFilter(),
                                             m_defaultCameraControllerFactory.Create(),
                                             m_globeCameraTouchController);
    
}

std::string PODAnimationExampleFactory::ExampleName() const
{
	return Examples::PODAnimationExample::GetName();
}

}
