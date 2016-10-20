// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "VRCardboardExample.h"
#include "VectorMath.h"
#include "LatLongAltitude.h"
#include "CatmullRomSpline.h"
#include "CameraSplinePlaybackController.h"
#include "ResourceCeilingProvider.h"
#include "GlobeCameraController.h"
#include "EegeoWorld.h"
#include "EarthConstants.h"
#include "ScreenProperties.h"

#define INTERIOR_NEAR_MULTIPLIER 0.025f
#define EXTERIOR_NEAR_MULTIPLIER 0.1f

#include "Logger.h"

namespace Examples
{

	VRCardboardExample::VRCardboardExample(Eegeo::EegeoWorld& eegeoWorld,
                                           const Eegeo::Config::DeviceSpec& deviceSpecs,
                                           Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                           Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                           const IScreenPropertiesProvider& initialScreenProperties,
										   Examples::IVRModeTracker& vrModeTracker)
    : m_world(eegeoWorld)
    , m_pVRCardboardController(NULL)
    {
        Eegeo::m44 projectionMatrix = Eegeo::m44(pCameraController->GetRenderCamera().GetProjectionMatrix());
        m_pCameraController = new Eegeo::VR::VRCameraController(initialScreenProperties.GetScreenProperties().GetScreenWidth(), initialScreenProperties.GetScreenProperties().GetScreenHeight());
        m_pCameraController->GetCamera().SetProjectionMatrix(projectionMatrix);
        m_eyeDistance = 0.03f;
        m_pVRCardboardController = Eegeo_NEW((Eegeo::VR::VRCardboardController)(m_world, initialScreenProperties, m_world.GetMapModule(), deviceSpecs, *m_pCameraController, vrModeTracker));
        NotifyScreenPropertiesChanged(initialScreenProperties.GetScreenProperties());
    }
    
	VRCardboardExample::~VRCardboardExample()
	{
		delete m_pCameraController;
	    Eegeo_DELETE m_pVRCardboardController;
    }
    
    void VRCardboardExample::Start()
    {
        Eegeo::Space::LatLongAltitude eyePosLla = Eegeo::Space::LatLongAltitude::FromDegrees(37.795185, -122.402780, 305);
        m_pCameraController->SetStartLatLongAltitude(eyePosLla);
        
    }
    
    void VRCardboardExample::Suspend()
    {
    	m_pVRCardboardController->StopSkybox();
    }

    void VRCardboardExample::UpdateWorld(float dt, Eegeo::EegeoWorld& world, Eegeo::Camera::CameraState cameraState, Examples::ScreenPropertiesProvider& screenPropertyProvider, Eegeo::Streaming::IStreamingVolume& streamingVolume)
    {
    	m_pVRCardboardController->Update(dt, GetCurrentCameraState(), m_world);
    }

    void VRCardboardExample::DrawWorld(Eegeo::EegeoWorld& world,  Eegeo::Camera::CameraState cameraState, Examples::ScreenPropertiesProvider& screenPropertyProvider)
    {
    	m_pVRCardboardController->Draw(m_world, m_vrCameraState);
    }
    
    void VRCardboardExample::UpdateCardboardProfile(const float cardboardProfile[])
    {
        //9th parameter is eye distance in meters.
        m_eyeDistance = cardboardProfile[9]/2.0f;
    }
    
    void VRCardboardExample::EarlyUpdate(float dt)
    {
        m_pCameraController->Update(dt);
        m_pCameraController->SetNearMultiplier(EXTERIOR_NEAR_MULTIPLIER);
    }
    
    void VRCardboardExample::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
    	m_pVRCardboardController->NotifyScreenPropertiesChanged(screenProperties);
    }
    
    
    void VRCardboardExample::SetVRCameraState(const float headTransform[])
    {
    	Eegeo::Camera::CameraState leftCameraState = GetCurrentLeftCameraState(headTransform);
    	Eegeo::Camera::CameraState rightCameraState = GetCurrentRightCameraState(headTransform);
    	const Eegeo::m33& currentCameraOrientation = GetCurrentCameraOrientation();
    	const Eegeo::m33& baseOrientation = GetBaseOrientation();
    	const Eegeo::m33& headTrackerOrientation = GetHeadTrackerOrientation();
    	m_vrCameraState = Eegeo::VR::VRCameraState(currentCameraOrientation, baseOrientation, headTrackerOrientation, leftCameraState, rightCameraState);
    }

    const Eegeo::m33& VRCardboardExample::GetCurrentCameraOrientation()
    {
        return m_pCameraController->GetOrientation();
    }
    
    const Eegeo::m33& VRCardboardExample::GetBaseOrientation()
    {
        return m_pCameraController->GetCameraOrientation();
    }
    
    const Eegeo::m33& VRCardboardExample::GetHeadTrackerOrientation()
    {
        return m_pCameraController->GetHeadTrackerOrientation();
    }
    
    
    Eegeo::Camera::CameraState VRCardboardExample::GetCurrentLeftCameraState(const float headTransform[]) const
    {
        Eegeo::m33 orientation;
        Eegeo::v3 right = Eegeo::v3(headTransform[0],headTransform[4],headTransform[8]);
        Eegeo::v3 up = Eegeo::v3(headTransform[1],headTransform[5],headTransform[9]);
        Eegeo::v3 forward = Eegeo::v3(-headTransform[2],-headTransform[6],-headTransform[10]);
        orientation.SetRow(0, right);
        orientation.SetRow(1, up);
        orientation.SetRow(2, forward);
        
        m_pCameraController->UpdateFromPose(orientation, -m_eyeDistance);
        return m_pCameraController->GetCameraState();
    }
    
    Eegeo::Camera::CameraState VRCardboardExample::GetCurrentRightCameraState(const float headTransform[]) const
    {
        Eegeo::m33 orientation;
        Eegeo::v3 right = Eegeo::v3(headTransform[0],headTransform[4],headTransform[8]);
        Eegeo::v3 up = Eegeo::v3(headTransform[1],headTransform[5],headTransform[9]);
        Eegeo::v3 forward = Eegeo::v3(-headTransform[2],-headTransform[6],-headTransform[10]);
        orientation.SetRow(0, right);
        orientation.SetRow(1, up);
        orientation.SetRow(2, forward);

        m_pCameraController->UpdateFromPose(orientation, m_eyeDistance);
        return m_pCameraController->GetCameraState();
    }
    
    Eegeo::Camera::CameraState VRCardboardExample::GetCurrentCameraState() const
    {
        return m_pCameraController->GetCameraState();
    }
}
