// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef POSITIONJAVAPINBUTTON_H_
#define POSITIONJAVAPINBUTTON_H_

#include <jni.h>

#include "GlobeCameraExampleBase.h"
#include "AndroidNativeState.h"
#include "RenderContext.h"


namespace Examples
{
class PositionJavaPinButtonExample : public GlobeCameraExampleBase
{
	AndroidNativeState& m_nativeState;
	Eegeo::EegeoWorld& m_world;

	int m_buttonID;
	jclass m_hudPinControllerClass;
	jobject m_hudPinController;
	jmethodID m_updateLocationMethodId;

public:
	PositionJavaPinButtonExample(
	    Eegeo::EegeoWorld& world,
	    AndroidNativeState& pNativeState,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
	    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	static std::string GetName()
	{
		return "PositionJavaPinButtonExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void Update(float dt) {}
	void Draw();
	void Suspend();

private:
	void CreateButton();
	void Project (const Eegeo::Space::LatLongAltitude& location, Eegeo::v3& screenPosition);
};
}

#endif /* POSITIONJAVAPINBUTTON_H_ */
