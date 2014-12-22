// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef POSITIONJAVAPINBUTTONEXAMPLEFACTORY_H_
#define POSITIONJAVAPINBUTTONEXAMPLEFACTORY_H_

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"
#include "AndroidNativeState.h"

namespace Examples
{
	class IScreenPropertiesProvider;

	class PositionJavaPinButtonExampleFactory : public IExampleFactory
	{
		Eegeo::EegeoWorld& m_world;
		AndroidNativeState& m_nativeState;
		DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
		Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;

	public:
		PositionJavaPinButtonExampleFactory(
			Eegeo::EegeoWorld& world,
			AndroidNativeState& nativeState,
			DefaultCameraControllerFactory& defaultCameraControllerFactory,
			Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController);

		std::string ExampleName() const;

		IExample* CreateExample() const;
	};
}


#endif /* POSITIONJAVAPINBUTTONEXAMPLEFACTORY_H_ */
