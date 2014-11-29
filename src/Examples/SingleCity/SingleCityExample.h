// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__SingleCityExample__
#define __ExampleApp__SingleCityExample__

#include "IExample.h"
#include "EegeoWorld.h"
#include "PrecacheService.h"
#include "GlobeCameraController.h"
#include "StreamingVolumeController.h"

namespace Examples
{
class SingleCityExample : public IExample
{
private:
	Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pCameraController;
	Eegeo::Web::PrecacheService& m_precacheService;
	Eegeo::Streaming::StreamingVolumeController& m_streamingVolumeController;
	Eegeo::EegeoWorld& m_world;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

	bool m_startedPrecaching;
	bool m_precacheComplete;

	void ConstrainCamera();
    
    Eegeo::Camera::GlobeCamera::GlobeCameraController& GlobeCamera() { return *m_pCameraController; }

public:
	SingleCityExample(
	                  Eegeo::Web::PrecacheService& precacheService,
	                  Eegeo::Streaming::StreamingVolumeController& streamingVolumeController,
	                  Eegeo::EegeoWorld& world,
	                  Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController);

	static std::string GetName()
	{
		return "SingleCityExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void Update(float dt);
	void AfterCameraUpdate();
	void Draw() {}
	void Suspend();
    const Eegeo::Camera::RenderCamera& GetRenderCamera() const;
    Eegeo::dv3 GetInterestPoint() const;
};
}


#endif /* defined(__ExampleApp__SingleCityExample__) */
