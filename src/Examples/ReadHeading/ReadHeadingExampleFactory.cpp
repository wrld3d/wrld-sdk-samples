// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ReadHeadingExampleFactory.h"
#include "ReadHeadingExample.h"
#include "Location.h"
#include "EegeoWorld.h"

using namespace Examples;

ReadHeadingExampleFactory::ReadHeadingExampleFactory(
	Eegeo::EegeoWorld& world,
	Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
: m_world(world)
, m_globeCameraController(globeCameraController)
{

}

IExample* ReadHeadingExampleFactory::CreateExample() const
{
	return new Examples::ReadHeadingExample(
		m_world,
		m_globeCameraController,
		m_world.GetDebugRenderer(),
		m_world.GetLocationService()
	);
}

std::string ReadHeadingExampleFactory::ExampleName() const
{
	return Examples::ReadHeadingExample::GetName();
}
