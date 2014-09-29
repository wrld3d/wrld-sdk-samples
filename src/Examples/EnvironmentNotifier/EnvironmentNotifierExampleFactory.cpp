// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EnvironmentNotifierExampleFactory.h"
#include "EnvironmentNotifierExample.h"

#include "DebugRenderingModule.h"
#include "TerrainStreamingModule.h"

using namespace Examples;

EnvironmentNotifierExampleFactory::EnvironmentNotifierExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* EnvironmentNotifierExampleFactory::CreateExample() const
{
    Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule = m_world.GetDebugRenderingModule();
    Eegeo::Modules::Map::Layers::TerrainStreamingModule& terrainStreamingModule = m_world.GetTerrainStreamingModule();
    
	return new Examples::EnvironmentNotifierExample(debugRenderingModule.GetDebugRenderer(),
	        terrainStreamingModule.GetTerrainStream(),
	        m_globeCameraController);
}

std::string EnvironmentNotifierExampleFactory::ExampleName() const
{
	return Examples::EnvironmentNotifierExample::GetName();
}

