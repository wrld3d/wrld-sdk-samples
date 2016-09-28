//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#pragma once
#include "Modules/SkyboxModule/SkyboxModule.h"
#include "VRDistortionModule.h"
#include "EegeoWorld.h"
#include "MapModule.h"
#include "QuadTreeCube.h"
#include "ExampleController.h"
#include "LodRefinementConfig.h"
#include "IVRModeTracker.h"
#include "ScreenPropertiesProvider.h"
#include "CameraFrustumStreamingVolume.h"
#include "VRCameraState.h"
#include "Types.h"
#include "VRCardboardV1ProfileFactory.h"
#include "VRCameraController.h"
#include "VRCameraState.h"

namespace Eegeo
{
    namespace VR
    {
        class VRCardboardController
        {
        private:
        	const Examples::IScreenPropertiesProvider& m_screenPropertiesProvider;
			#ifdef CARDBOARD
        	Examples::IVRModeTracker& m_vrModeTracker;
        	Eegeo::VR::VRCameraController& m_cameraController;
			Eegeo::Streaming::CameraFrustumStreamingVolume* m_pStreamingVolume;
			Eegeo::VR::Distortion::VRDistortionModule* m_pVRDistortion;
			Eegeo::Skybox::SkyboxModule *m_pVRSkybox;
			Eegeo::VR::Distortion::VRCardboardV1ProfileFactory* m_pVRCardboardV1ProfileFactory;
			#endif
			float m_nightTParam;
			Eegeo::v3 m_currentClearColor;
			Eegeo::v3 m_startClearColor;
			Eegeo::v3 m_destClearColor;

        public:
			VRCardboardController(Eegeo::EegeoWorld& world,
								  const Examples::IScreenPropertiesProvider& screenPropertiesProvider,
								  Eegeo::Modules::Map::MapModule& mapModule,
								  const Eegeo::Config::DeviceSpec& deviceSpecs,
								  Eegeo::VR::VRCameraController& cameraController,
								  Examples::IVRModeTracker& vrModeTracker);
			~VRCardboardController();
			void Update(float dt, const Eegeo::Camera::CameraState cameraState, Eegeo::EegeoWorld& eegeoWorld);
			void UpdateNightTParam(float dt);
			void ToggleNight();
		    void UpdateFogging();
		    void UpdateCardboardProfile(const float cardboardProfile[]);
		    void MagnetTriggered();
		    void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
		    void DrawLeftEye (Eegeo::EegeoWorld& eegeoWorld, const Eegeo::VR::VRCameraState& vrCameraState);
		    void DrawRightEye (Eegeo::EegeoWorld& eegeoWorld, const Eegeo::VR::VRCameraState& vrCameraState);
		    void DrawEyeFromCameraState(const Eegeo::Camera::CameraState& cameraState, Eegeo::EegeoWorld& eegeoWorld, const Eegeo::VR::VRCameraState& vrCameraState);
		    void Draw (Eegeo::EegeoWorld& eegeoWorld, const Eegeo::VR::VRCameraState& vrCameraState);
		    void StopSkybox();
        };
    }
}
