// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VRCameraController.h"
#include "ExampleHandler.h"
#include "Camera.h"
#include "Geometry.h"
#include "Streaming.h"
#include "GlobeCamera.h"
#include "ICallback.h"
#include "ConfigSections.h"
#include "VRCardboardController.h"
#include "IVRModeTracker.h"
#include "ScreenPropertiesProvider.h"
#include "Types.h"

namespace Examples
{

	class VRCardboardExample : public ExampleHandler, Eegeo::NonCopyable
	{
	private:

		float m_eyeDistance;
		Eegeo::EegeoWorld& m_world;

		Eegeo::VR::VRCameraController* m_pCameraController;
		Eegeo::VR::VRCameraState m_vrCameraState;
		Eegeo::VR::VRCardboardController* m_pVRCardboardController;

	public:

		VRCardboardExample(Eegeo::EegeoWorld& eegeoWorld,
						   const Eegeo::Config::DeviceSpec& deviceSpecs,
						   Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
						   Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
						   const IScreenPropertiesProvider& initialScreenProperties,
						   Examples::IVRModeTracker& vrModeTracker);

		virtual ~VRCardboardExample();

		static std::string GetName()
		{
			return "VRCardboardExample";
		}
		std::string Name() const
		{
			return GetName();
		}

		void Start();
		void OrientationUpdate();
		void EarlyUpdate(float dt);
		void Update(float dt) { }
		void PreWorldDraw() { }
		void Draw() {}
		void Suspend();

		const Eegeo::m33& GetCurrentCameraOrientation();
		const Eegeo::m33& GetBaseOrientation();
		const Eegeo::m33& GetHeadTrackerOrientation();
		virtual void SetVRCameraState(const float headTransform[]);

		virtual void UpdateWorld(float dt, Eegeo::EegeoWorld& world, Eegeo::Camera::CameraState cameraState, Examples::ScreenPropertiesProvider& screenPropertyProvider, Eegeo::Streaming::IStreamingVolume& streamingVolume);
		virtual void DrawWorld(Eegeo::EegeoWorld& world,  Eegeo::Camera::CameraState cameraState, Examples::ScreenPropertiesProvider& screenPropertyProvider);
		void UpdateCardboardProfile(const float cardboardProfile[]);

		virtual Eegeo::Camera::CameraState GetCurrentLeftCameraState(const float headTransform[]) const;
		virtual Eegeo::Camera::CameraState GetCurrentRightCameraState(const float headTransform[]) const;
		virtual Eegeo::Camera::CameraState GetCurrentCameraState() const;

		virtual void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);

		void NotifyViewNeedsLayout() {}



		void Event_TouchRotate (const AppInterface::RotateData& data) { }
		void Event_TouchRotate_Start (const AppInterface::RotateData& data) { }
		void Event_TouchRotate_End (const AppInterface::RotateData& data) { }

		void Event_TouchPinch (const AppInterface::PinchData& data) { }
		void Event_TouchPinch_Start (const AppInterface::PinchData& data) { }
		void Event_TouchPinch_End (const AppInterface::PinchData& data) { }

		void Event_TouchPan (const AppInterface::PanData& data) { }
		void Event_TouchPan_Start (const AppInterface::PanData& data) { }
		void Event_TouchPan_End (const AppInterface::PanData& data) { }

		void Event_TouchTap (const AppInterface::TapData& data) { }
		void Event_TouchDoubleTap (const AppInterface::TapData& data) { }
		void Event_TouchDown (const AppInterface::TouchData& data) { }
		void Event_TouchMove (const AppInterface::TouchData& data) { }
		void Event_TouchUp (const AppInterface::TouchData& data) { }
	
	};
}
