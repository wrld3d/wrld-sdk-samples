// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <CameraHelpers.h>
#include "GeofenceExample.h"
#include "LatLongAltitude.h"
#include "IGeofenceModel.h"
#include "IGeofenceService.h"
#include "GlobeCameraController.h"
#include "GeofenceBuilder.h"

namespace Examples
{
    namespace
    {
        Eegeo::Data::Geofencing::IGeofenceModel* CreateGeofence(Eegeo::Data::Geofencing::IGeofenceService& geofenceService)
        {
            Eegeo::Data::Geofencing::GeofenceBuilder builder;
            builder
                .SetOuterRing({
                    Eegeo::Space::LatLong::FromDegrees(37.803424, -122.431638),
                    Eegeo::Space::LatLong::FromDegrees(37.804280, -122.425287),
                    Eegeo::Space::LatLong::FromDegrees(37.806552, -122.425716),
                    Eegeo::Space::LatLong::FromDegrees(37.805535, -122.432089)
                })
                .AddInnerRing({
                    Eegeo::Space::LatLong::FromDegrees(37.804050, -122.430454),
                    Eegeo::Space::LatLong::FromDegrees(37.804531, -122.426647),
                    Eegeo::Space::LatLong::FromDegrees(37.805926, -122.426900),
                    Eegeo::Space::LatLong::FromDegrees(37.805284, -122.430729)
                })
                .SetPolygonColor({1.0f, 0.0f, 0.0f, 0.5f})
                .SetElevation(20.f);

            const Eegeo::Data::Geofencing::IGeofenceModel::IdType geofenceId = geofenceService.Create(builder.Build());
            
            return &geofenceService.Get(geofenceId);
        }
    }

    GeofenceExample::GeofenceExample(
            Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
            Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
            Eegeo::Data::Geofencing::IGeofenceService& geofenceService)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_geofenceService(geofenceService)
    , m_elapsedTime(0.0f)
    {
        Eegeo::Space::EcefTangentBasis cameraInterestBasis;

        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
                Eegeo::Space::LatLong::FromDegrees(37.804845, -122.428961).ToECEF(),
                16.472872f,
                cameraInterestBasis);

        pCameraController->SetView(cameraInterestBasis, 1200.0f);
    }

    GeofenceExample::~GeofenceExample()
    {
        if(m_pGeofence != NULL)
        {
            m_geofenceService.Destroy(m_pGeofence->GetId());
            m_pGeofence = NULL;
        }
    }
    
    void GeofenceExample::Start()
    {
        m_pGeofence = CreateGeofence(m_geofenceService);
    }
    
    void GeofenceExample::Update(float dt)
    {
        m_elapsedTime += dt;

        const float alpha = (Eegeo::Math::Sin(m_elapsedTime) + 1.0f) / 2.0f;

        Eegeo::v4 currentColor = m_pGeofence->GetPolygonColor();
        currentColor.w = alpha;
        m_pGeofence->SetPolygonColor(currentColor);
    }
}
