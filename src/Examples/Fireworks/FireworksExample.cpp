// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FireworksExample.h"
#include "FireworksLocationConfiguration.h"
#include "GlobeCameraController.h"
#include "LatLongAltitude.h"
#include "FireworksModule.h"
#include "ICityThemesService.h"

namespace Examples
{

FireworksExample::FireworksExample(Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                   Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                                   Eegeo::Modules::Core::RenderingModule& renderingModule,
                                   Eegeo::Modules::IPlatformAbstractionModule& platformModule,
                                   Eegeo::Modules::Map::StreamingModule& streamingModule,
                                   Eegeo::Modules::Map::MapModule& mapModule,
                                   Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule,
                                   Eegeo::Resources::CityThemes::ICityThemesService& cityThemesService)
: GlobeCameraExampleBase(pCameraController, cameraTouchController)
, m_cityThemesService(cityThemesService)
{
    m_pFireworksModule = Eegeo::Modules::FireworksModule::Create("firework_01.png",
                                                                 renderingModule,
                                                                 platformModule,
                                                                 streamingModule,
                                                                 mapModule,
                                                                 terrainModelModule);
}
    
FireworksExample::~FireworksExample()
{
    Eegeo_DELETE m_pFireworksModule;
}
    
void FireworksExample::Start()
{
    // In this example, three fireworks displays are added to the world.
    
    // The first is at the San Francisco bay area, and will always be displayed
    Eegeo::Fireworks::FireworksLocationConfiguration location0 =
        Eegeo::Fireworks::FireworksLocationConfiguration(Eegeo::Space::LatLong::FromDegrees(37.796341f, -122.392842f),
                                                         1.0f,
                                                         0,
                                                         0);
    
    m_pFireworksModule->AddFireworksLocation(0, location0);
    
    // The second is in front of Buckingham Palace in London, and only be enabled bewteen the hours of 8pm and 9pm.
    // (You may need to change the device time to see this one)
    Eegeo::Fireworks::FireworksLocationConfiguration location1 =
        Eegeo::Fireworks::FireworksLocationConfiguration(Eegeo::Space::LatLong::FromDegrees(51.501793f, -0.140605f),
                                                         1.0f,
                                                         20,
                                                         21);
    
    m_pFireworksModule->AddFireworksLocation(1, location1);
    
    // The third one is at the Statue of Liberty in New York.  It'll be a 24 hour display but only have a 50% chance of playing when you visit.
    Eegeo::Fireworks::FireworksLocationConfiguration location2 =
        Eegeo::Fireworks::FireworksLocationConfiguration(Eegeo::Space::LatLong::FromDegrees(40.689904f, -74.043019f),
                                                         0.5f,
                                                         0,
                                                         0);
    
    m_pFireworksModule->AddFireworksLocation(2, location2);
    
    // Set to night time theme for best results.
    m_cityThemesService.RequestTransitionToState("NightDefault", 1.0f);
    
}
    
void FireworksExample::Suspend()
{
    m_cityThemesService.RequestTransitionToState("DayDefault", 1.0f);
    
    m_pFireworksModule->Clear();
    
    
}

void FireworksExample::Update(float dt)
{
    Eegeo::Camera::RenderCamera renderCamera(GetGlobeCameraController().GetRenderCamera());
    m_pFireworksModule->Update(dt, renderCamera);
}

}
