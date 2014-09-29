// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SingleCityExampleFactory.h"
#include "SingleCityExample.h"

using namespace Examples;

#include "MapModule.h"
#include "StreamingModule.h"

SingleCityExampleFactory::SingleCityExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* SingleCityExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::StreamingModule& streamingModule = m_world.GetStreamingModule();
    
	return new Examples::SingleCityExample(m_globeCameraController,
	                                       streamingModule.GetPrecachingService(),
	                                       streamingModule.GetStreamingVolumeController(),
	                                       m_world,
	                                       m_globeCameraController);
}

std::string SingleCityExampleFactory::ExampleName() const
{
	return Examples::SingleCityExample::GetName();
}
