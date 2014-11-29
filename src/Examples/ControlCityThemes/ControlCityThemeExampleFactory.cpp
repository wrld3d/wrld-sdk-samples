// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ControlCityThemeExampleFactory.h"
#include "ControlCityThemeExample.h"

#include "CityThemesModule.h"

using namespace Examples;

ControlCityThemeExampleFactory::ControlCityThemeExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
{

}

IExample* ControlCityThemeExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::CityThemesModule& cityThemesModule = m_world.GetCityThemesModule();
    
	return new Examples::ControlCityThemeExample(cityThemesModule.GetCityThemesService(),
	        cityThemesModule.GetCityThemesRepository(),
	        cityThemesModule.GetCityThemesUpdater(),
	        m_world,
	        m_defaultCameraControllerFactory.Create());
}

std::string ControlCityThemeExampleFactory::ExampleName() const
{
	return Examples::ControlCityThemeExample::GetName();
}

