// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ControlCityThemeExampleFactory.h"
#include "ControlCityThemeExample.h"
#include "DefaultCameraControllerFactory.h"
#include "CityThemesModule.h"

namespace Examples
{

ControlCityThemeExampleFactory::ControlCityThemeExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* ControlCityThemeExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::CityThemesModule& cityThemesModule = m_world.GetCityThemesModule();
    
	return new Examples::ControlCityThemeExample(cityThemesModule.GetCityThemesService(),
	        cityThemesModule.GetCityThemesRepository(),
	        cityThemesModule.GetCityThemesUpdater(),
	        m_world,
	        m_defaultCameraControllerFactory.Create(),
            m_globeCameraTouchController);
}

std::string ControlCityThemeExampleFactory::ExampleName() const
{
	return Examples::ControlCityThemeExample::GetName();
}
}

