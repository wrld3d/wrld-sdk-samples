// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JavaHudCrossThreadCommunicationExampleFactory.h"
#include "JavaHudCrossThreadCommunicationExample.h"
#include "JavaHudCrossThreadCommunicationProxy.h"

#include "CityThemesModule.h"

using namespace Examples;

JavaHudCrossThreadCommunicationExampleFactory::JavaHudCrossThreadCommunicationExampleFactory(
    Eegeo::EegeoWorld& world,
    AndroidNativeState& nativeState,
    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_nativeState(nativeState)
	, m_globeCameraController(globeCameraController)
{

}

IExample* JavaHudCrossThreadCommunicationExampleFactory::CreateExample() const
{
	Eegeo::Modules::Map::CityThemesModule& cityThemesModule = m_world.GetCityThemesModule();

	return new Examples::JavaHudCrossThreadCommunicationExample(
	           m_nativeState,
	           cityThemesModule.GetCityThemesService(),
	           cityThemesModule.GetCityThemesRepository(),
	           cityThemesModule.GetCityThemesUpdater(),
	           m_globeCameraController);
}

std::string JavaHudCrossThreadCommunicationExampleFactory::ExampleName() const
{
	return Examples::JavaHudCrossThreadCommunicationExample::GetName();
}
