// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "GlobeCameraExampleBase.h"

#include "Rendering.h"
#include "Camera.h"
#include "ITextureFileLoader.h"

#include "Markers.h"
#include <string>

#include <jni.h>
#include "EegeoWorld.h"
#include "AndroidNativeState.h"
#include "RenderContext.h"

namespace Examples
{
/*!
 *  MarkersWithAttachedJavaUIExample demonstrates how to place a marker in the 3D world, with some Java UI anchored to it
 *
 *  This is a combination of the MarkersExample & the PositionJavaPinButtonExample
 */
class MarkersWithAttachedJavaUIExample : public GlobeCameraExampleBase
{
private:

	// java ui stuff
	AndroidNativeState& m_nativeState;
	Eegeo::EegeoWorld& m_world;

	// Marker stuff
	Eegeo::Markers::IMarkerService& m_markerService;
	int m_markerId;

	int m_buttonID;
	jclass m_hudPinControllerClass;
	jobject m_hudPinController;
	jmethodID m_updateLocationMethodId;

public:
	MarkersWithAttachedJavaUIExample(
	    Eegeo::EegeoWorld& world,
	    AndroidNativeState& nativeState,
	    Eegeo::Markers::IMarkerService& markerService,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
	    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
	    const Eegeo::Rendering::ScreenProperties& screenProperties
	);
	virtual ~MarkersWithAttachedJavaUIExample();

	static std::string GetName()
	{
		return "MarkersWithAttachedJavaUIExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt);
	void Draw();
	void Suspend();

	void Event_TouchTap(const AppInterface::TapData& data);

private:
	void CreateExampleMarkers();
	void CreateJavaUIButton();
};
}
