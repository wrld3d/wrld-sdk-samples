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

namespace Eegeo
{
    namespace VR
    {
        class VRCardboardController
        {
        private:
        	Examples::ExampleController* m_pExampleController;
        	const Examples::ScreenPropertiesProvider& m_screenPropertiesProvider;
			#ifdef CARDBOARD
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
			VRCardboardController(Eegeo::EegeoWorld* pWorld,
								  const Examples::ScreenPropertiesProvider& screenPropertiesProvider,
								  Eegeo::Modules::Map::MapModule& mapModule,
								  const Eegeo::Config::DeviceSpec& deviceSpecs,
								  Examples::ExampleController* exampleController);
			~VRCardboardController();
			void Update(float dt, const Eegeo::Camera::CameraState& cameraState, Eegeo::EegeoWorld& eegeoWorld, Examples::IVRModeTracker& vrModeTracker);
			void UpdateNightTParam(float dt);
			void ToggleNight();
		    void UpdateFogging();
		    void UpdateCardboardProfile(const float cardboardProfile[]);
		    void MagnetTriggered();
		    void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
		    void DrawLeftEye (float dt, Eegeo::EegeoWorld& eegeoWorld);
		    void DrawRightEye (float dt, Eegeo::EegeoWorld& eegeoWorld);
		    void DrawEyeFromCameraState(float dt, const Eegeo::Camera::CameraState& cameraState, Eegeo::EegeoWorld& eegeoWorld);
		    void Draw (float dt, Eegeo::EegeoWorld& eegeoWorld);
		    void StopSkybox(Examples::IVRModeTracker& vrModeTracker);
        };
    }
}
