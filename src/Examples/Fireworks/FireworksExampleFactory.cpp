// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FireworksExampleFactory.h"
#include "FireworksExample.h"
#include "DefaultCameraControllerFactory.h"
#include "CityThemesModule.h"

namespace Examples
{

FireworksExampleFactory::FireworksExampleFactory(Eegeo::EegeoWorld& world,
                                                 DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* FireworksExampleFactory::CreateExample() const
{
	return new Examples::FireworksExample(m_defaultCameraControllerFactory.Create(),
                                          m_globeCameraTouchController,
                                          m_world.GetRenderingModule(),
                                          m_world.GetPlatformAbstractionModule(),
                                          m_world.GetStreamingModule(),
                                          m_world.GetMapModule(),
                                          m_world.GetTerrainModelModule(),
                                          m_world.GetCityThemesModule().GetCityThemesService());
}

std::string FireworksExampleFactory::ExampleName() const
{
	return Examples::FireworksExample::GetName();
}
}

