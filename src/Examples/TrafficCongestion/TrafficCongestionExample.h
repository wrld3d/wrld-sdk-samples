// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "GlobeCameraExampleBase.h"
#include "TrafficCongestion.h"
#include "ITrafficCongestionService.h"
#include "ICityThemeChangedObserver.h"

namespace Examples
{
class TrafficCongestionExample : public GlobeCameraExampleBase, public Eegeo::Resources::CityThemes::ICityThemeChangedObserver
{
private:
	Eegeo::TrafficCongestion::ITrafficCongestionService& m_trafficCongestionService;
    Eegeo::Resources::CityThemes::ICityThemesService& m_cityThemesService;
    
	float m_timeAccumulator;
	Eegeo::Streaming::MortonKey m_key;
	int m_congestionValue;
    bool m_hasStreamedTheme;
    
    void CycleCongestionType();

public:
	TrafficCongestionExample(Eegeo::TrafficCongestion::ITrafficCongestionService& trafficCongestionService,
                             Eegeo::Resources::CityThemes::ICityThemesService& cityThemesService,
                             Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);
    
    ~TrafficCongestionExample();

	static std::string GetName()
	{
		return "TrafficCongestionExample";
	}
	std::string Name() const
	{
		return GetName();
	}

    void Start();
	void Update(float dt);
	void Draw() {}
	void Suspend();
    
    void OnThemeRequested(const Eegeo::Resources::CityThemes::CityThemeData& newTheme){};
    void OnThemeChanged(const Eegeo::Resources::CityThemes::CityThemeData& newTheme);
    
};
}
