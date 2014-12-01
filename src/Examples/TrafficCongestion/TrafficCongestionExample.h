// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "GlobeCameraExampleBase.h"
#include "TrafficCongestion.h"
#include "ITrafficCongestionService.h"

namespace Examples
{
class TrafficCongestionExample : public GlobeCameraExampleBase
{
private:
	Eegeo::TrafficCongestion::ITrafficCongestionService& m_trafficCongestionService;
	float m_timeAccumulator;
	Eegeo::Streaming::MortonKey m_key;
	int m_congestionValue;
    

public:
	TrafficCongestionExample(
	    Eegeo::TrafficCongestion::ITrafficCongestionService& trafficCongestionService,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	static std::string GetName()
	{
		return "TrafficCongestionExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void Update(float dt);
	void Draw() {}
	void Suspend();
    
    
};
}
