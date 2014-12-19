// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ShowJavaPlaceJumpUIExampleFactory.h"
#include "ShowJavaPlaceJumpUIExample.h"
#include "DefaultCameraControllerFactory.h"

namespace Examples
{

ShowJavaPlaceJumpUIExampleFactory::ShowJavaPlaceJumpUIExampleFactory(
	AndroidNativeState& nativeState,
    DefaultCameraControllerFactory& defaultCameraControllerFactory,
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_defaultCameraControllerFactory(defaultCameraControllerFactory)
	, m_globeCameraTouchController(globeCameraTouchController)
	, m_nativeState(nativeState)
{

}

IExample* ShowJavaPlaceJumpUIExampleFactory::CreateExample() const
{
	Eegeo::Camera::GlobeCamera::GlobeCameraController* pGlobeCameraController = m_defaultCameraControllerFactory.Create();
	Examples::ExampleCameraJumpController* pExampleCameraJumpController = new ExampleCameraJumpController(
			*pGlobeCameraController,
			m_globeCameraTouchController);

	return new Examples::ShowJavaPlaceJumpUIExample(
	           m_nativeState,
	           pGlobeCameraController,
	           m_globeCameraTouchController,
	           pExampleCameraJumpController);
}

std::string ShowJavaPlaceJumpUIExampleFactory::ExampleName() const
{
	return Examples::ShowJavaPlaceJumpUIExample::GetName();
}

}
