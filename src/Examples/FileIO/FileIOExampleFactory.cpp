// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FileIOExampleFactory.h"
#include "FileIOExample.h"
#include "DefaultCameraControllerFactory.h"
#include "IPlatformAbstractionModule.h"

namespace Examples
{

FileIOExampleFactory::FileIOExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{
}

IExample* FileIOExampleFactory::CreateExample() const
{
    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = m_world.GetPlatformAbstractionModule();
    
	return new Examples::FileIOExample(platformAbstractionModule.GetFileIO(),
	                                   m_defaultCameraControllerFactory.Create(),
                                       m_globeCameraTouchController);
}

std::string FileIOExampleFactory::ExampleName() const
{
	return Examples::FileIOExample::GetName();
}

}


