// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "GlobeCameraExampleBase.h"
#include "Geofencing.h"

#include <vector>

namespace Examples
{
    class GeofenceExample : public GlobeCameraExampleBase
    {
    public:
        GeofenceExample(
                Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                Eegeo::Data::Geofencing::GeofenceController& geofenceController);
        
        virtual ~GeofenceExample();
        
        static std::string GetName()
        {
            return "GeofenceExample";
        }
        
        std::string Name() const
        {
            return GetName();
        }
        
        void Start();
        void Update(float dt);

        void Draw() {}
        void Suspend() {}
    private:
        Eegeo::Data::Geofencing::GeofenceController& m_geofenceController;
        Eegeo::Data::Geofencing::GeofenceModel* m_pGeofence;
        float m_elapsedTime;
    };
}
