// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SingleCityExampleFactory.h"
#include "SingleCityExample.h"

using namespace Examples;

#include "MapModule.h"
#include "StreamingModule.h"

SingleCityExampleFactory::SingleCityExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
{

}

IExample* SingleCityExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::StreamingModule& streamingModule = m_world.GetStreamingModule();
    
	return new Examples::SingleCityExample(
	                                       streamingModule.GetPrecachingService(),
	                                       streamingModule.GetStreamingVolumeController(),
	                                       m_world,
	                                       m_defaultCameraControllerFactory.Create());
}

std::string SingleCityExampleFactory::ExampleName() const
{
	return Examples::SingleCityExample::GetName();
}
