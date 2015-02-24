// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <CameraHelpers.h>
#include "GeofenceExample.h"
#include "LatLongAltitude.h"
#include "GeofenceModel.h"
#include "GeofenceRenderer.h"
#include "GeofenceViewFactory.h"
#include "GeofenceController.h"
#include "GlobeCameraController.h"

namespace Examples
{
    namespace
    {
        Eegeo::Data::Geofencing::GeofenceModel* CreateGeofence()
        {
            const size_t BL = 0;
            const size_t BR = 1;
            const size_t TR = 2;
            const size_t TL = 3;

            std::vector<Eegeo::Space::LatLongAltitude> extVerts;
            extVerts.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.803424, -122.431638, 0.0));
            extVerts.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.804280, -122.425287, 0.0));
            extVerts.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.806552, -122.425716, 0.0));
            extVerts.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.805535, -122.432089, 0.0));

            // Lerp between the opposite corners to form an (optional) ring that will not be included in the geofence
            std::vector<Eegeo::Space::LatLongAltitude> intVerts;
            intVerts.push_back(Eegeo::Space::LatLongAltitude::Lerp(extVerts[BL], extVerts[TR], 0.2f));
            intVerts.push_back(Eegeo::Space::LatLongAltitude::Lerp(extVerts[BR], extVerts[TL], 0.2f));
            intVerts.push_back(Eegeo::Space::LatLongAltitude::Lerp(extVerts[BL], extVerts[TR], 1.0f - 0.2f));
            intVerts.push_back(Eegeo::Space::LatLongAltitude::Lerp(extVerts[BR], extVerts[TL], 1.0f - 0.2f));

            const Eegeo::v4 polygonColor(1.0f, 0.0f, 0.0f, 0.5f);

            return Eegeo::Data::Geofencing::GeofenceModel::GeofenceBuilder(
                    "sf_test",
                    polygonColor,
                    extVerts)
                    .AddInteriorRing(intVerts)
                    .AltitudeOffset(20.0f)
                    .Build();
        }
    }

    GeofenceExample::GeofenceExample(
            Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
            Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
            Eegeo::Data::Geofencing::GeofenceController& geofenceController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_geofenceController(geofenceController)
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
            m_geofenceController.Remove(*m_pGeofence);
            Eegeo_DELETE m_pGeofence;
            m_pGeofence = NULL;
        }
    }
    
    void GeofenceExample::Start()
    {
        m_pGeofence = CreateGeofence();
        m_geofenceController.Add(*m_pGeofence);
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
