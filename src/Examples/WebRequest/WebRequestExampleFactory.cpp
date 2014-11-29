// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WebRequestExampleFactory.h"
#include "WebRequestExample.h"

#include "IPlatformAbstractionModule.h"

using namespace Examples;

WebRequestExampleFactory::WebRequestExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
{

}

IExample* WebRequestExampleFactory::CreateExample() const
{
    Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = m_world.GetPlatformAbstractionModule();
    
	return new Examples::WebRequestExample(platformAbstractionModule.GetWebLoadRequestFactory(),
	                                       m_defaultCameraControllerFactory.Create());
}

std::string WebRequestExampleFactory::ExampleName() const
{
	return Examples::WebRequestExample::GetName();
}
