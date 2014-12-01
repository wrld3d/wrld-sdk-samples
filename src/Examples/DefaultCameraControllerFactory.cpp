// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DefaultCameraControllerFactory.h"
#include "GlobeCameraController.h"
#include "TerrainModelModule.h"
#include "MapModule.h"
#include "RenderCamera.h"
#include "LatLongAltitude.h"
#include "CameraHelpers.h"

namespace Examples
{
    Eegeo::Camera::GlobeCamera::GlobeCameraController* DefaultCameraControllerFactory::Create()
    {
        Eegeo::Camera::GlobeCamera::GlobeCameraController* pController = new Eegeo::Camera::GlobeCamera::GlobeCameraController(
                                                                     m_terrainModelModule.GetTerrainHeightProvider(),
                                                                     m_mapModule.GetEnvironmentFlatteningService(),
                                                                     m_mapModule.GetResourceCeilingProvider(),
                                                                     m_touchController,
                                                                     m_config);
        
        // override default configuration to enable two-finger pan gesture to control additional camera pitch
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchSettings touchSettings = pController->GetTouchSettings();
        touchSettings.TiltEnabled = m_tiltEnabled;
        pController->SetTouchSettings(touchSettings);
        
        
        Eegeo::Camera::RenderCamera* renderCamera = pController->GetCamera();
        const Eegeo::Rendering::ScreenProperties& screenProperties = m_screenPropertiesProvider.GetScreenProperties();
        renderCamera->SetViewport(0.f, 0.f, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());
        
        
        Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude::FromDegrees(m_interestPointLatitudeDegrees,
                                                                                            m_interestPointLongitudeDegrees,
                                                                                            m_interestPointAltitudeMeters);
        
        
        
        Eegeo::Space::EcefTangentBasis cameraInterestBasis;
        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(location.ToECEF(), m_cameraControllerOrientationDegrees, cameraInterestBasis);
        
        pController->SetView(cameraInterestBasis, m_cameraControllerDistanceFromInterestPointMeters);
        
        return pController;
    }
}