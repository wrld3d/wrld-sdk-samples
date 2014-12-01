// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__WebRequestExample__
#define __ExampleApp__WebRequestExample__

#include "GlobeCameraExampleBase.h"

#include "IWebLoadRequestFactory.h"
#include "WebLoadRequestCompletionCallback.h"
#include "IWebLoadRequest.h"

namespace Examples
{
class WebRequestExample : public GlobeCameraExampleBase
{
private:
	Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
    

public:
	WebRequestExample(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
	                  Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	static std::string GetName()
	{
		return "WebRequestExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt) {}
	void Draw() {}
	void Suspend() {}
    
    
};
}


#endif /* defined(__ExampleApp__WebRequestExample__) */
