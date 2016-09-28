//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#include "VRCardboardController.h"
#include "StreamingVolumeController.h"

namespace Eegeo
{
    namespace VR
    {
		VRCardboardController::VRCardboardController(Eegeo::EegeoWorld& world,
													 const Examples::IScreenPropertiesProvider& screenPropertiesProvider,
													 Eegeo::Modules::Map::MapModule& mapModule,
													 const Eegeo::Config::DeviceSpec& deviceSpecs,
													 Eegeo::VR::VRCameraController& cameraController,
													 Examples::IVRModeTracker& vrModeTracker)
		: m_screenPropertiesProvider(screenPropertiesProvider)
		, m_cameraController(cameraController)
		, m_vrModeTracker(vrModeTracker)
		, m_nightTParam(0.0f)
		, m_currentClearColor(135.f/255.0f, 206.f/255.0f, 235.f/255.0f)
		, m_startClearColor(0.f/255.f,24.f/255.f,72.f/255.f)
		, m_destClearColor(135.f/255.0f, 206.f/255.0f, 235.f/255.0f)
		{
			#ifdef CARDBOARD
			m_pVRCardboardV1ProfileFactory = Eegeo_NEW(Eegeo::VR::Distortion::VRCardboardV1ProfileFactory)();
			m_pStreamingVolume = Eegeo_NEW(Eegeo::Streaming::CameraFrustumStreamingVolume)(mapModule.GetResourceCeilingProvider(),
																						   Eegeo::Config::LodRefinementConfig::GetLodRefinementAltitudesForDeviceSpec(deviceSpecs),
																						   Eegeo::Streaming::QuadTreeCube::MAX_DEPTH_TO_VISIT,
																						   mapModule.GetEnvironmentFlatteningService());

			m_pStreamingVolume->setDeepestLevelForAltitudeLodRefinement(11);
			m_pStreamingVolume->SetForceMaximumRefinement(true);

			Eegeo::Modules::Core::RenderingModule& renderingModule = world.GetRenderingModule();
			m_pVRDistortion = Eegeo_NEW(Eegeo::VR::Distortion::VRDistortionModule)(m_screenPropertiesProvider.GetScreenProperties(),
																				   renderingModule.GetVertexLayoutPool(),
																				   renderingModule.GetVertexBindingPool(),
																				   renderingModule.GetShaderIdGenerator(),
																				   renderingModule.GetMaterialIdGenerator(),
																				   renderingModule.GetRenderableFilters(),
																				   renderingModule.GetGlBufferPool(),
																				   *m_pVRCardboardV1ProfileFactory);
			m_pVRDistortion->Initialize();

			m_pVRSkybox = Eegeo_NEW(Eegeo::Skybox::SkyboxModule)(renderingModule,
																 renderingModule.GetGlBufferPool(),
																 renderingModule.GetVertexBindingPool(),
																 renderingModule.GetVertexLayoutPool(),
																 renderingModule.GetRenderableFilters());
			#endif
		}

		VRCardboardController::~VRCardboardController()
		{
			#ifdef CARDBOARD
			m_pVRDistortion->Suspend();
			Eegeo_DELETE m_pVRSkybox;
			Eegeo_DELETE m_pVRDistortion;
			Eegeo_DELETE m_pStreamingVolume;
			Eegeo_DELETE m_pVRCardboardV1ProfileFactory;
			#endif
		}

		void VRCardboardController::Update(float dt, const Eegeo::Camera::CameraState cameraState, Eegeo::EegeoWorld& eegeoWorld)
		{
			#ifdef CARDBOARD
		    if(!m_pVRSkybox->IsShowing())
		    {
		        m_pVRSkybox->Start();
		    }
		    m_vrModeTracker.EnterVRMode();

		    Eegeo::Camera::RenderCamera& renderCamera = m_cameraController.GetCamera();


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

		void VRCardboardController::Draw (Eegeo::EegeoWorld& eegeoWorld, const Eegeo::VR::VRCameraState& vrCameraState)
		{
			#ifdef CARDBOARD
			if(eegeoWorld.Validated())
			{
				m_pVRDistortion->BeginRendering();
				DrawLeftEye(eegeoWorld, vrCameraState);
				m_pVRDistortion->RegisterRenderable();
				DrawRightEye(eegeoWorld, vrCameraState);
				m_pVRDistortion->UnRegisterRenderable();
			}
			#endif
		}

		void VRCardboardController::UpdateNightTParam(float dt)
		{
			#ifdef CARDBOARD
		    m_nightTParam += dt;
		    if(m_nightTParam>1.0f)
		    {
		    	m_nightTParam = 0.99f;
		    }

		    m_nightTParam = Eegeo::Math::Clamp01(m_nightTParam);
		    m_currentClearColor = Eegeo::v3::Lerp(m_startClearColor, m_destClearColor, m_nightTParam);

		    m_pVRSkybox->UpdateSkyColor(m_currentClearColor);
			#endif
		}

		void VRCardboardController::DrawLeftEye (Eegeo::EegeoWorld& eegeoWorld, const Eegeo::VR::VRCameraState& vrCameraState)
		{

		    glViewport(0, 0, m_screenPropertiesProvider.GetScreenProperties().GetScreenWidth()/2.0f, m_screenPropertiesProvider.GetScreenProperties().GetScreenHeight());
		    Eegeo::Camera::CameraState cameraState(vrCameraState.GetCurrentLeftCameraState());

		    DrawEyeFromCameraState(cameraState, eegeoWorld, vrCameraState);

		}

		void VRCardboardController::DrawRightEye (Eegeo::EegeoWorld& eegeoWorld, const Eegeo::VR::VRCameraState& vrCameraState)
		{

		    glViewport(m_screenPropertiesProvider.GetScreenProperties().GetScreenWidth()/2.0f, 0, m_screenPropertiesProvider.GetScreenProperties().GetScreenWidth()/2.0f, m_screenPropertiesProvider.GetScreenProperties().GetScreenHeight());

		    Eegeo::Camera::CameraState cameraState(vrCameraState.GetCurrentRightCameraState());

		    DrawEyeFromCameraState(cameraState, eegeoWorld, vrCameraState);

		}

		void VRCardboardController::DrawEyeFromCameraState(const Eegeo::Camera::CameraState& cameraState, Eegeo::EegeoWorld& eegeoWorld, const Eegeo::VR::VRCameraState& vrCameraState)
		{
		    Eegeo::EegeoDrawParameters drawParameters(cameraState.LocationEcef(),
		    										  cameraState.InterestPointEcef(),
													  cameraState.ViewMatrix(),
													  cameraState.ProjectionMatrix(),
													  m_screenPropertiesProvider.GetScreenProperties());

		    Eegeo::v3 forward(vrCameraState.GetBaseOrientation().GetRow(2));
		    Eegeo::dv3 position(cameraState.LocationEcef() + (forward*50));

		    eegeoWorld.Draw(drawParameters);
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
		    m_pVRDistortion->UpdateCardboardProfile(cardboardProfile);
			#endif
		}

		void VRCardboardController::MagnetTriggered()
		{

		}

		void VRCardboardController::StopSkybox()
		{
			#ifdef CARDBOARD
			if(m_pVRSkybox->IsShowing())
			{
				m_pVRSkybox->Stop();
			}
			m_vrModeTracker.ExitVRMode();
			#endif
		}
    }
}
