// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WebRequestExample.h"
#include <map>
#include <string>

using namespace Eegeo::Web;

namespace
{
class ExternalPostHandlerType_NotPartOfPublicAPI : public IWebLoadRequestCompletionCallback
{
	void operator()(IWebResponse& webResponse)
	{
		int* userData = (int*)webResponse.GetUserData();
		const std::string& url = webResponse.GetUrl();
		size_t responseBodySize = webResponse.GetBodyData().size();

		Eegeo_TTY("\nFinished Https POST of %s in a non member function of calling type, with user data %d - resource size of %ld\n",
		          url.c_str(), *userData, responseBodySize);

		delete userData;

		Eegeo_TTY("\nIs our fake token a valid key? Response was: %s\n", &webResponse.GetBodyData()[0]);
	}
};

ExternalPostHandlerType_NotPartOfPublicAPI externalPostHandler;

class ExternalGetHandlerType_NotPartOfPublicAPI
{
	TWebLoadRequestCompletionCallback<ExternalGetHandlerType_NotPartOfPublicAPI> m_handler;

	void HandleRequest(IWebResponse& webResponse)
	{
		int* userData = (int*)webResponse.GetUserData();
		const std::string& url = webResponse.GetUrl();
		size_t responseBodySize = webResponse.GetBodyData().size();
		int result = webResponse.GetHttpStatusCode();

		Eegeo_TTY("\nFinished Http GET of %s, result was %d, with user data %d - resource size of %ld\n",
		          url.c_str(), result, *userData, responseBodySize);

		delete userData;
	}
public:

	ExternalGetHandlerType_NotPartOfPublicAPI()
		:m_handler(this, &ExternalGetHandlerType_NotPartOfPublicAPI::HandleRequest)
	{

	}

	IWebLoadRequestCompletionCallback& GetRequestHandler()
	{
		return m_handler;
	}
};

ExternalGetHandlerType_NotPartOfPublicAPI externalGetHandler;
}

namespace Examples
{
WebRequestExample::WebRequestExample(IWebLoadRequestFactory& webRequestFactory,
                                     Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_webRequestFactory(webRequestFactory)
{
}

void WebRequestExample::Start()
{
	Eegeo_TTY("Making 4 Http GETs, with integer labels as user data, using a member as the handler...\n");
    m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, "http://apikey.eegeo.com", externalGetHandler.GetRequestHandler())
        .SetUserData(new int(1))
        .Build()->Load();
    
    m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, "http://non-existent-example-host-1234.com", externalGetHandler.GetRequestHandler())
        .SetUserData(new int(2))
        .Build()->Load();
    
    m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, "http://wikipedia.org", externalGetHandler.GetRequestHandler())
        .SetUserData(new int(3))
        .Build()->Load();
    
    m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, "http://d2xvsc8j92rfya.cloudfront.net/non_existent_resource.hcff", externalGetHandler.GetRequestHandler())
        .SetUserData(new int(4))
        .Build()->Load();

	Eegeo_TTY("Making Https POST to Eegeo apikey service with invalid key (123456789), with integer labels as user data using a non-member as the handler...\n");
    m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::POST, "https://apikey.eegeo.com/validate", externalPostHandler)
        .AddFormData("token", "123456789")
        .SetUserData(new int(5678))
        .Build()->Load();
    
    m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, "http://wikipedia.org", externalGetHandler.GetRequestHandler())
        .AddHeader("X-MyCustom-Header", "Hello World")
        .SetUserData(new int(4))
        .Build()->Load();
}

}
