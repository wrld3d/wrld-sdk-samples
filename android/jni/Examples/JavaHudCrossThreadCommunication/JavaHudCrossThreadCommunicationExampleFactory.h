// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLEFACTORY_H_
#define JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLEFACTORY_H_

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"
#include "AndroidNativeState.h"
#include "MessageQueue.h"

namespace Examples
{
class JavaHudCrossThreadCommunicationExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	AndroidNativeState& m_nativeState;
	DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;

public:
	JavaHudCrossThreadCommunicationExampleFactory(
	    Eegeo::EegeoWorld& world,
	    AndroidNativeState& nativeState,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* JAVAHUDCROSSTHREADCOMMUNICATIONEXAMPLEFACTORY_H_ */
