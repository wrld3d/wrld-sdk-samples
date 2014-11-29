// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CameraTransitionExampleFactory.h"
#include "CameraTransitionExample.h"

using namespace Examples;

CameraTransitionExampleFactory::CameraTransitionExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
{

}

IExample* CameraTransitionExampleFactory::CreateExample() const
{
	return new Examples::CameraTransitionExample(m_defaultCameraControllerFactory.Create());
}

std::string CameraTransitionExampleFactory::ExampleName() const
{
	return Examples::CameraTransitionExample::GetName();
}

