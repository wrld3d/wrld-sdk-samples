// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef SHOWJAVAPLACEJUMPUIEXAMPLEFACTORY_H_
#define SHOWJAVAPLACEJUMPUIEXAMPLEFACTORY_H_

#include "IExampleFactory.h"
#include "IExample.h"
#include "ExampleCameraJumpController.h"
#include "AndroidNativeState.h"
#include "GlobeCameraController.h"

namespace Examples
{
class ShowJavaPlaceJumpUIExampleFactory : public IExampleFactory
{
	DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;
	AndroidNativeState& m_nativeState;

public:
	ShowJavaPlaceJumpUIExampleFactory(
		AndroidNativeState& nativeState,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController
	    );

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* SHOWJAVAPLACEJUMPUIEXAMPLEFACTORY_H_ */
