// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <iostream>
#include "GlobeCameraExampleBase.h"
#include "Fireworks.h"
#include "Modules.h"
#include "CityThemes.h"

namespace Examples
{
/*!
 *  FireworksExample demonstrates how to add fireworks displays to the world, configured to appear at certain times of day.
 */
class FireworksExample : public GlobeCameraExampleBase
{
private:
    Eegeo::Modules::FireworksModule* m_pFireworksModule;
    
    Eegeo::Resources::CityThemes::ICityThemesService& m_cityThemesService;

public:
    FireworksExample(Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                     Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                     Eegeo::Modules::Core::RenderingModule& renderingModule,
                     Eegeo::Modules::IPlatformAbstractionModule& platformModule,
                     Eegeo::Modules::Map::StreamingModule& streamingModule,
                     Eegeo::Modules::Map::MapModule& mapModule,
                     Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule,
                     Eegeo::Resources::CityThemes::ICityThemesService& cityThemesService);
    ~FireworksExample();

	static std::string GetName()
	{
		return "FireworksExample";
	}
    
	std::string Name() const
	{
		return GetName();
	}

    void Start();
    void Update(float dt);
	void Draw() {}
    void Suspend();

    
    
};
}