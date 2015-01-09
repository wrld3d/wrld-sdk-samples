// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WebRequestExampleFactory.h"
#include "WebRequestExample.h"
#include "DefaultCameraControllerFactory.h"
#include "IPlatformAbstractionModule.h"

namespace Examples
{

WebRequestExampleFactory::WebRequestExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* WebRequestExampleFactory::CreateExample() const
{
    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = m_world.GetPlatformAbstractionModule();
    
	return new Examples::WebRequestExample(platformAbstractionModule.GetWebLoadRequestFactory(),
	                                       m_defaultCameraControllerFactory.Create(),
                                           m_globeCameraTouchController);
}

std::string WebRequestExampleFactory::ExampleName() const
{
	return Examples::WebRequestExample::GetName();
}

}
