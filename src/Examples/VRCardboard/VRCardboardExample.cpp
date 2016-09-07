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
                                                 Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                                 Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                 const Eegeo::Rendering::ScreenProperties& initialScreenProperties)
    : m_world(eegeoWorld)
    {
        NotifyScreenPropertiesChanged(initialScreenProperties);
        Eegeo::m44 projectionMatrix = Eegeo::m44(pCameraController->GetRenderCamera().GetProjectionMatrix());
        m_pCameraController = new Eegeo::VR::VRCameraController(initialScreenProperties.GetScreenWidth(), initialScreenProperties.GetScreenHeight());
        m_pCameraController->GetCamera().SetProjectionMatrix(projectionMatrix);
        m_eyeDistance = 0.03f;
    }
    
	VRCardboardExample::~VRCardboardExample()
	{
		delete m_pCameraController;
    }
    
    void VRCardboardExample::Start()
    {

        Eegeo::Space::LatLongAltitude eyePosLla = Eegeo::Space::LatLongAltitude::FromDegrees(40.763647, -73.973468, 35);
        m_pCameraController->SetStartLatLongAltitude(eyePosLla);
        
    }
    
    void VRCardboardExample::Suspend()
    {

    }
    
    void VRCardboardExample::UpdateCardboardProfile(float cardboardProfile[])
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
    }
    
    
    const Eegeo::m33& VRCardboardExample::getCurrentCameraOrientation()
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
    
    Eegeo::Camera::RenderCamera& VRCardboardExample::GetRenderCamera(){
        return m_pCameraController->GetCamera();
    }
    
    Eegeo::Camera::CameraState VRCardboardExample::GetCurrentLeftCameraState(float headTansform[]) const
    {
        
        Eegeo::m33 orientation;
        Eegeo::v3 right = Eegeo::v3(headTansform[0],headTansform[4],headTansform[8]);
        Eegeo::v3 up = Eegeo::v3(headTansform[1],headTansform[5],headTansform[9]);
        Eegeo::v3 forward = Eegeo::v3(-headTansform[2],-headTansform[6],-headTansform[10]);
        orientation.SetRow(0, right);
        orientation.SetRow(1, up);
        orientation.SetRow(2, forward);
        
        m_pCameraController->UpdateFromPose(orientation, -m_eyeDistance);
        
        return m_pCameraController->GetCameraState();
    }
    
    Eegeo::Camera::CameraState VRCardboardExample::GetCurrentRightCameraState(float headTansform[]) const
    {
        Eegeo::m33 orientation;
        Eegeo::v3 right = Eegeo::v3(headTansform[0],headTansform[4],headTansform[8]);
        Eegeo::v3 up = Eegeo::v3(headTansform[1],headTansform[5],headTansform[9]);
        Eegeo::v3 forward = Eegeo::v3(-headTansform[2],-headTansform[6],-headTansform[10]);
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
