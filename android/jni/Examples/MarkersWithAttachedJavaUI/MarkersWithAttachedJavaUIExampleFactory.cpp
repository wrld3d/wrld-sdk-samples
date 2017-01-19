// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MarkersWithAttachedJavaUIExampleFactory.h"
#include "MarkersWithAttachedJavaUIExample.h"
#include "DefaultCameraControllerFactory.h"
#include "MapModule.h"
#include "MarkersModule.h"

namespace Examples
{

MarkersWithAttachedJavaUIExampleFactory::MarkersWithAttachedJavaUIExampleFactory(
    Eegeo::EegeoWorld& world,
    AndroidNativeState& nativeState,
    DefaultCameraControllerFactory& defaultCameraControllerFactory,
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
    const IScreenPropertiesProvider& screenPropertiesProvider)
	: m_world(world)
	, m_nativeState(nativeState)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
	, m_globeCameraTouchController(globeCameraTouchController)
	, m_screenPropertiesProvider(screenPropertiesProvider)
{

}

IExample* MarkersWithAttachedJavaUIExampleFactory::CreateExample() const
{
	Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
	Eegeo::Markers::MarkersModule& markersModule = mapModule.GetMarkersModule();

	return new MarkersWithAttachedJavaUIExample(
	           m_world,
	           m_nativeState,
			   markersModule.GetMarkerService(),
	           m_defaultCameraControllerFactory.Create(),
	           m_globeCameraTouchController,
	           m_screenPropertiesProvider.GetScreenProperties());
}

std::string MarkersWithAttachedJavaUIExampleFactory::ExampleName() const
{
	return MarkersWithAttachedJavaUIExample::GetName();
}
}
