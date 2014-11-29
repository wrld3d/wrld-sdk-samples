// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PODAnimationExampleFactory.h"
#include "PODAnimationExample.h"

#include "LocalAsyncTextureLoader.h"

#include "IPlatformAbstractionModule.h"
#include "RenderingModule.h"
#include "AsyncLoadersModule.h"
#include "LightingModule.h"

using namespace Examples;

PODAnimationExampleFactory::PODAnimationExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
{

}

IExample* PODAnimationExampleFactory::CreateExample() const
{ 
    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractioModule = m_world.GetPlatformAbstractionModule();
    Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
    Eegeo::Modules::Core::AsyncLoadersModule& asyncLoadersModule = m_world.GetAsyncLoadersModule();
    Eegeo::Modules::Core::LightingModule& lightingModule = m_world.GetLightingModule();
    
	return new Examples::PODAnimationExample(platformAbstractioModule.GetFileIO(),
                                             asyncLoadersModule.GetLocalAsyncTextureLoader(),
                                             lightingModule.GetGlobalFogging(),
                                             renderingModule.GetRenderableFilters(),
                                             renderingModule.GetNullMaterialFactory(),
                                             m_defaultCameraControllerFactory.Create());
    
}

std::string PODAnimationExampleFactory::ExampleName() const
{
	return Examples::PODAnimationExample::GetName();
}

