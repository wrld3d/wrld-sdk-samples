// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ShowJavaPlaceJumpUIExampleFactory.h"
#include "ShowJavaPlaceJumpUIExample.h"
#include "DefaultCameraControllerFactory.h"

namespace Examples
{

ShowJavaPlaceJumpUIExampleFactory::ShowJavaPlaceJumpUIExampleFactory(
    ExampleCameraJumpController& exampleCameraJumpController,
    DefaultCameraControllerFactory& defaultCameraControllerFactory,
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
    AndroidNativeState& nativeState)
	: m_exampleCameraJumpController(exampleCameraJumpController)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
	, m_globeCameraTouchController(globeCameraTouchController)
	, m_nativeState(nativeState)
{

}

IExample* ShowJavaPlaceJumpUIExampleFactory::CreateExample() const
{
	return new Examples::ShowJavaPlaceJumpUIExample(
	           m_nativeState,
	           m_defaultCameraControllerFactory.Create(),
	           m_globeCameraTouchController,
	           m_exampleCameraJumpController);
}

std::string ShowJavaPlaceJumpUIExampleFactory::ExampleName() const
{
	return Examples::ShowJavaPlaceJumpUIExample::GetName();
}

}
