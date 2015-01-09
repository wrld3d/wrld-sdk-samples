// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JavaHudCrossThreadCommunicationExampleFactory.h"
#include "JavaHudCrossThreadCommunicationExample.h"
#include "JavaHudCrossThreadCommunicationProxy.h"
#include "DefaultCameraControllerFactory.h"

#include "CityThemesModule.h"

namespace Examples
{

JavaHudCrossThreadCommunicationExampleFactory::JavaHudCrossThreadCommunicationExampleFactory(
    Eegeo::EegeoWorld& world,
    AndroidNativeState& nativeState,
    DefaultCameraControllerFactory& defaultCameraControllerFactory,
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_nativeState(nativeState)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
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
	           m_defaultCameraControllerFactory.Create(),
	           m_globeCameraTouchController);
}

std::string JavaHudCrossThreadCommunicationExampleFactory::ExampleName() const
{
	return Examples::JavaHudCrossThreadCommunicationExample::GetName();
}

}
