// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef POSITIONJAVAPINBUTTON_H_
#define POSITIONJAVAPINBUTTON_H_

#include <jni.h>
#include "EegeoWorld.h"
#include "IExample.h"
#include "AndroidNativeState.h"
#include "RenderContext.h"


namespace Examples
{
class PositionJavaPinButtonExample : public IExample
{
	AndroidNativeState& m_nativeState;
	Eegeo::EegeoWorld& m_world;
	const Eegeo::Rendering::ScreenProperties& m_screenProperties;
	Eegeo::Camera::GlobeCamera::GlobeCameraController& m_cameraController;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

	int m_buttonID;
	jclass m_hudPinControllerClass;
	jobject m_hudPinController;
	jmethodID m_updateLocationMethodId;

public:
	PositionJavaPinButtonExample(
	    Eegeo::EegeoWorld& world,
	    AndroidNativeState& pNativeState,
	    const Eegeo::Rendering::ScreenProperties& screenProperties,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);

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
	const Eegeo::Camera::RenderCamera& GetRenderCamera() const;

private:
	void CreateButton();
	void Project (const Eegeo::Space::LatLongAltitude& location, Eegeo::v3& screenPosition);
};
}

#endif /* POSITIONJAVAPINBUTTON_H_ */
