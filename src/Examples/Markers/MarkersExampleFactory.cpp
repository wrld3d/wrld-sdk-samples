// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MarkersExampleFactory.h"
#include "MarkersExample.h"
#include "DefaultCameraControllerFactory.h"
#include "MapModule.h"
#include "MarkersModule.h"

namespace Examples
{

    MarkersExampleFactory::MarkersExampleFactory(Eegeo::EegeoWorld& world,
                                                 DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                 Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                                 const IScreenPropertiesProvider& screenPropertiesProvider)
	: m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
	, m_screenPropertiesProvider(screenPropertiesProvider)
{

}

IExample* MarkersExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    Eegeo::Markers::MarkersModule& markersModule = mapModule.GetMarkersModule();
    
    const Eegeo::Rendering::ScreenProperties& initialScreenProperties = m_screenPropertiesProvider.GetScreenProperties();
    
	return new Examples::MarkersExample(markersModule.GetMarkerService(),
                                        m_defaultCameraControllerFactory.Create(),
                                        m_globeCameraTouchController,
                                        initialScreenProperties
                                        );
}

std::string MarkersExampleFactory::ExampleName() const
{
	return Examples::MarkersExample::GetName();
}

}

