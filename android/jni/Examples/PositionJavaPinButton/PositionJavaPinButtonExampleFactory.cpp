// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PositionJavaPinButtonExampleFactory.h"
#include "PositionJavaPinButtonExample.h"
#include "DefaultCameraControllerFactory.h"
#include "ScreenPropertiesProvider.h"

namespace Examples
{

PositionJavaPinButtonExampleFactory::PositionJavaPinButtonExampleFactory(
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

IExample* PositionJavaPinButtonExampleFactory::CreateExample() const
{
	return new Examples::PositionJavaPinButtonExample(
	           m_world,
	           m_nativeState,
	           m_screenPropertiesProvider.GetScreenProperties(),
	           m_defaultCameraControllerFactory.Create(),
	           m_globeCameraTouchController);
}

std::string PositionJavaPinButtonExampleFactory::ExampleName() const
{
	return Examples::PositionJavaPinButtonExample::GetName();
}

}
