// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FireworksExampleFactory.h"
#include "FireworksExample.h"

using namespace Examples;

FireworksExampleFactory::FireworksExampleFactory(Eegeo::EegeoWorld& world,
                                                 Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* FireworksExampleFactory::CreateExample() const
{
	return new Examples::FireworksExample(m_globeCameraController,
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

