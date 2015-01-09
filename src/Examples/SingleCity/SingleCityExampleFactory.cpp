// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SingleCityExampleFactory.h"
#include "SingleCityExample.h"
#include "DefaultCameraControllerFactory.h"
#include "MapModule.h"
#include "StreamingModule.h"

namespace Examples
{



SingleCityExampleFactory::SingleCityExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* SingleCityExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::StreamingModule& streamingModule = m_world.GetStreamingModule();
    
	return new Examples::SingleCityExample(
	                                       streamingModule.GetPrecachingService(),
	                                       streamingModule.GetStreamingVolumeController(),
	                                       m_world,
	                                       m_defaultCameraControllerFactory.Create(),
                                           m_globeCameraTouchController);
}

std::string SingleCityExampleFactory::ExampleName() const
{
	return Examples::SingleCityExample::GetName();
}

}
