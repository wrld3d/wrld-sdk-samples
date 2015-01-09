// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CameraTransitionExampleFactory.h"
#include "CameraTransitionExample.h"
#include "DefaultCameraControllerFactory.h"

namespace Examples
{

CameraTransitionExampleFactory::CameraTransitionExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* CameraTransitionExampleFactory::CreateExample() const
{
	return new Examples::CameraTransitionExample(m_defaultCameraControllerFactory.Create(), m_globeCameraTouchController);
}

std::string CameraTransitionExampleFactory::ExampleName() const
{
	return Examples::CameraTransitionExample::GetName();
}

}

