// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ExampleApp_ControlCityThemeExample_h
#define ExampleApp_ControlCityThemeExample_h

#include "GlobeCameraExampleBase.h"
#include "CityThemes.h"
#include "CityThemeData.h"
#include "ICityThemeChangedObserver.h"

namespace Examples
{
    
class ControlCityThemeExample : public GlobeCameraExampleBase, public Eegeo::Resources::CityThemes::ICityThemeChangedObserver
{
private:
	Eegeo::Resources::CityThemes::ICityThemesService& m_themeService;
	Eegeo::Resources::CityThemes::ICityThemeRepository& m_themeRepository;
	Eegeo::Resources::CityThemes::ICityThemesUpdater& m_themeUpdater;
	Eegeo::EegeoWorld& m_eegeoWorld;
	bool m_themeChanged;
    bool m_hasStreamedTheme;
    
	Eegeo::Resources::CityThemes::CityThemeData m_initialCityTheme;

	void ChangeTheme();
	void FindThemeByPointInPolygon();
public:
	ControlCityThemeExample(Eegeo::Resources::CityThemes::ICityThemesService& themeService,
	                        Eegeo::Resources::CityThemes::ICityThemeRepository& themeRepository,
	                        Eegeo::Resources::CityThemes::ICityThemesUpdater& themeUpdater,
	                        Eegeo::EegeoWorld& eegeoWorld,
	                        Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

    
    ~ControlCityThemeExample();
    
	static std::string GetName()
	{
		return "ControlCityThemeExample";
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


#endif
