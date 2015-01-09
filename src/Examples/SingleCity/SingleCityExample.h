// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__SingleCityExample__
#define __ExampleApp__SingleCityExample__

#include "GlobeCameraExampleBase.h"
#include "EegeoWorld.h"
#include "PrecacheService.h"
#include "GlobeCameraController.h"
#include "StreamingVolumeController.h"

namespace Examples
{
class SingleCityExample : public GlobeCameraExampleBase
{
private:
	
	Eegeo::Web::PrecacheService& m_precacheService;
	Eegeo::Streaming::StreamingVolumeController& m_streamingVolumeController;
	Eegeo::EegeoWorld& m_world;

	bool m_startedPrecaching;
	bool m_precacheComplete;

	void ConstrainCamera();

public:
	SingleCityExample(
	                  Eegeo::Web::PrecacheService& precacheService,
	                  Eegeo::Streaming::StreamingVolumeController& streamingVolumeController,
	                  Eegeo::EegeoWorld& world,
	                  Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	static std::string GetName()
	{
		return "SingleCityExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
    void EarlyUpdate(float dt);
	void Update(float dt);
	void Draw() {}
	void Suspend();
    
    
};
}


#endif /* defined(__ExampleApp__SingleCityExample__) */
