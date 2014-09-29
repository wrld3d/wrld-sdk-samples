// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FileIOExampleFactory.h"
#include "FileIOExample.h"

#include "IPlatformAbstractionModule.h"

using namespace Examples;

FileIOExampleFactory::FileIOExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* FileIOExampleFactory::CreateExample() const
{
    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = m_world.GetPlatformAbstractionModule();
    
	return new Examples::FileIOExample(platformAbstractionModule.GetFileIO(),
	                                   m_globeCameraController);
}

std::string FileIOExampleFactory::ExampleName() const
{
	return Examples::FileIOExample::GetName();
}


