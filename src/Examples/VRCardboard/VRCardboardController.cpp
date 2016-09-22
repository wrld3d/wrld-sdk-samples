//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#include "VRCardboardController.h"
#include "StreamingVolumeController.h"

namespace Eegeo
{
    namespace VR
    {
		VRCardboardController::VRCardboardController(Eegeo::EegeoWorld* pWorld,
				const Examples::ScreenPropertiesProvider& screenPropertiesProvider,
				Eegeo::Modules::Map::MapModule& mapModule,
				Eegeo::Config::DeviceSpec deviceSpecs,
				Examples::ExampleController* exampleController)
		: m_pExampleController(exampleController)
		, m_screenPropertiesProvider(screenPropertiesProvider)
		, m_nightTParam(0.0f)
		, m_currentClearColor(135.f/255.0f, 206.f/255.0f, 235.f/255.0f)
		, m_startClearColor(0.f/255.f,24.f/255.f,72.f/255.f)
		, m_destClearColor(135.f/255.0f, 206.f/255.0f, 235.f/255.0f)
		{
			#ifdef CARDBOARD
			m_pStreamingVolume = Eegeo_NEW(Eegeo::Streaming::CameraFrustumStreamingVolume)(mapModule.GetResourceCeilingProvider(),
			Eegeo::Config::LodRefinementConfig::GetLodRefinementAltitudesForDeviceSpec(deviceSpecs),
			Eegeo::Streaming::QuadTreeCube::MAX_DEPTH_TO_VISIT,
			mapModule.GetEnvironmentFlatteningService());

			m_pStreamingVolume->setDeepestLevelForAltitudeLodRefinement(11);
			m_pStreamingVolume->SetForceMaximumRefinement(true);

			Eegeo::Modules::Core::RenderingModule& renderingModule = pWorld->GetRenderingModule();
			m_pVRDistortion = Eegeo_NEW(Eegeo::VR::Distortion::VRDistortionModule)(m_screenPropertiesProvider.GetScreenProperties(),
			renderingModule.GetVertexLayoutPool(),
			renderingModule.GetVertexBindingPool(),
			renderingModule.GetShaderIdGenerator(),
			renderingModule.GetMaterialIdGenerator(),
			renderingModule.GetRenderableFilters(),
			renderingModule.GetGlBufferPool());
			m_pVRDistortion->Initialize();

			m_pVRSkybox = Eegeo_NEW(Eegeo::Skybox::SkyboxModule)(renderingModule,
			renderingModule.GetGlBufferPool(),
			renderingModule.GetVertexBindingPool(),
			renderingModule.GetVertexLayoutPool(),
			renderingModule.GetRenderableFilters());
			#endif
		}

		void VRCardboardController::VRUpdate(float dt, const Eegeo::Camera::CameraState& cameraState, Eegeo::EegeoWorld& eegeoWorld, Examples::IVRModeTracker& vrModeTracker)
		{
			#ifdef CARDBOARD
		    if(!m_pVRSkybox->IsShowing())
		    {
		        m_pVRSkybox->Start();
		    }
		    vrModeTracker.EnterVRMode();

		    Eegeo::Camera::RenderCamera& renderCamera = m_pExampleController->GetRenderCamera();


		    std::vector<Eegeo::Geometry::Plane> frustumPlanes(Eegeo::Geometry::Frustum::PLANES_COUNT);
		    BuildFrustumPlanesFromViewProjection(frustumPlanes, renderCamera.GetViewProjectionMatrix());
		    const double d = renderCamera.GetAltitude() * Eegeo::Streaming::StreamingVolumeController::CAMERA_ALTITUDE_TO_FAR_PLANE_DISTANCE_MULTIPLIER;
		    const double cameraFarPlaneD = fmin(fmax(d, Eegeo::Streaming::StreamingVolumeController::MIN_STREAMING_FAR_PLANE_DISTANCE), frustumPlanes[Eegeo::Geometry::Frustum::PLANE_FAR].d);
		    frustumPlanes[Eegeo::Geometry::Frustum::PLANE_FAR].d = static_cast<float>(cameraFarPlaneD);

		    //    Workaround: added 100.0f to FOV to load textures for surroundings even when camera is not looking at it to fix interior loading crash.
		    m_pStreamingVolume->updateStreamingVolume(renderCamera.GetEcefLocation(), frustumPlanes, renderCamera.GetFOV()+100.0f);
		    m_pStreamingVolume->ResetVolume(cameraState.InterestPointEcef());

		    UpdateNightTParam(dt);
		    Eegeo::EegeoUpdateParameters updateParameters(dt,
		    cameraState.LocationEcef(),
		    cameraState.InterestPointEcef(),
		    cameraState.ViewMatrix(),
		    cameraState.ProjectionMatrix(),
		    *m_pStreamingVolume,
		    m_screenPropertiesProvider.GetScreenProperties());
		    eegeoWorld.Update(updateParameters);
			#endif
		}

		void VRCardboardController::Draw (float dt, Eegeo::EegeoWorld& eegeoWorld)
		{
			#ifdef CARDBOARD
			if(eegeoWorld.Validated())
			{
				m_pVRDistortion->BeginRendering();
				DrawLeftEye(dt, eegeoWorld);
				m_pVRDistortion->RegisterRenderable();
				DrawRightEye(dt, eegeoWorld);
				m_pVRDistortion->UnRegisterRenderable();
			}
			#endif
		}

		void VRCardboardController::UpdateNightTParam(float dt)
		{
			#ifdef CARDBOARD
		    m_nightTParam += dt;
		    if(m_nightTParam>1.0f)
		    m_nightTParam = 0.99f;

		    m_nightTParam = Eegeo::Math::Clamp01(m_nightTParam);
		    m_currentClearColor = Eegeo::v3::Lerp(m_startClearColor, m_destClearColor, m_nightTParam);

		    m_pVRSkybox->UpdateSkyColor(m_currentClearColor);
			#endif
		}

		void VRCardboardController::DrawLeftEye (float dt, Eegeo::EegeoWorld& eegeoWorld)
		{
		    m_pExampleController->PreWorldDraw();

		    glViewport(0, 0, m_screenPropertiesProvider.GetScreenProperties().GetScreenWidth()/2.0f, m_screenPropertiesProvider.GetScreenProperties().GetScreenHeight());

		    Eegeo::Camera::CameraState cameraState(m_pExampleController->GetVRCameraState().GetCurrentLeftCameraState());

		    DrawEyeFromCameraState(dt, cameraState, eegeoWorld);

		}

		void VRCardboardController::DrawRightEye (float dt, Eegeo::EegeoWorld& eegeoWorld)
		{
		    m_pExampleController->PreWorldDraw();

		    glViewport(m_screenPropertiesProvider.GetScreenProperties().GetScreenWidth()/2.0f, 0, m_screenPropertiesProvider.GetScreenProperties().GetScreenWidth()/2.0f, m_screenPropertiesProvider.GetScreenProperties().GetScreenHeight());

		    Eegeo::Camera::CameraState cameraState(m_pExampleController->GetVRCameraState().GetCurrentRightCameraState());

		    DrawEyeFromCameraState(dt, cameraState, eegeoWorld);

		}

		void VRCardboardController::DrawEyeFromCameraState(float dt, const Eegeo::Camera::CameraState& cameraState, Eegeo::EegeoWorld& eegeoWorld)
		{
		    Eegeo::EegeoDrawParameters drawParameters(cameraState.LocationEcef(),
		    cameraState.InterestPointEcef(),
		    cameraState.ViewMatrix(),
		    cameraState.ProjectionMatrix(),
		    m_screenPropertiesProvider.GetScreenProperties());

		    Eegeo::v3 forward(m_pExampleController->GetVRCameraState().GetBaseOrientation().GetRow(2));
		    Eegeo::dv3 position(cameraState.LocationEcef() + (forward*50));

		    eegeoWorld.Draw(drawParameters);

		    m_pExampleController->Draw();
		}

		void VRCardboardController::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
		{
			#ifdef CARDBOARD
		    m_pVRDistortion->NotifyScreenPropertiesChanged(screenProperties);
			#endif
		}

		void VRCardboardController::UpdateCardboardProfile(const float cardboardProfile[])
		{
			#ifdef CARDBOARD
		    m_pExampleController->UpdateCardboardProfile(cardboardProfile);
		    m_pVRDistortion->UpdateCardboardProfile(cardboardProfile);
			#endif
		}

		void VRCardboardController::MagnetTriggered()
		{

		}

		void VRCardboardController::StopSkybox(Examples::IVRModeTracker& vrModeTracker)
		{
			#ifdef CARDBOARD
			if(m_pVRSkybox->IsShowing())
			{
				m_pVRSkybox->Stop();
			}
			vrModeTracker.ExitVRMode();
			#endif
		}

		VRCardboardController::~VRCardboardController()
		{
			#ifdef CARDBOARD
			Eegeo_DELETE m_pVRSkybox;
			Eegeo_DELETE m_pVRDistortion;
			Eegeo_DELETE m_pStreamingVolume;
			#endif
		}
    }
}
