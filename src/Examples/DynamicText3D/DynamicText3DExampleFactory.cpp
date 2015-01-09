// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DynamicText3DExampleFactory.h"
#include "DynamicText3DExample.h"
#include "RenderContext.h"
#include "DefaultCameraControllerFactory.h"
#include "PlacenamesStreamingModule.h"
#include "MapModule.h"
#include "RenderingModule.h"

namespace Examples
{

DynamicText3DExampleFactory::DynamicText3DExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* DynamicText3DExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    Eegeo::Modules::Map::Layers::PlaceNamesStreamingModule& placenamesStreamingModule = mapModule.GetPlaceNamesStreamingModule();
    Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
    Eegeo::Rendering::RenderableFilters& renderableFilters = renderingModule.GetRenderableFilters();
    
    return new Examples::DynamicText3DExample(mapModule.GetEnvironmentFlatteningService(),
                                              placenamesStreamingModule.GetPlaceNameViewBuilder(),
                                              m_world,
                                              m_defaultCameraControllerFactory.Create(),
                                              m_globeCameraTouchController,
                                              renderableFilters);

}

std::string DynamicText3DExampleFactory::ExampleName() const
{
	return Examples::DynamicText3DExample::GetName();
}

}

