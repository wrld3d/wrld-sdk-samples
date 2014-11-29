// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Modules.h"
#include "GlobeCameraControllerConfiguration.h"
#include "ScreenPropertiesProvider.h"


namespace Examples
{
    class DefaultCameraControllerFactory
    {
    public:
        DefaultCameraControllerFactory(Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule,
                                       Eegeo::Modules::Map::MapModule& mapModule,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                       const IScreenPropertiesProvider& screenPropertiesProvider,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration config,
                                       bool tiltEnabled,
                                       float interestPointLatitudeDegrees,
                                       float interestPointLongitudeDegrees,
                                       float interestPointAltitudeMeters,
                                       float cameraControllerOrientationDegrees,
                                       float cameraControllerDistanceFromInterestPointMeters)
        : m_terrainModelModule(terrainModelModule)
        , m_mapModule(mapModule)
        , m_touchController(touchController)
        , m_screenPropertiesProvider(screenPropertiesProvider)
        , m_config(config)
        , m_tiltEnabled(tiltEnabled)
        , m_interestPointLatitudeDegrees(interestPointLatitudeDegrees)
        , m_interestPointLongitudeDegrees(interestPointLongitudeDegrees)
        , m_interestPointAltitudeMeters(interestPointAltitudeMeters)
        , m_cameraControllerOrientationDegrees(cameraControllerOrientationDegrees)
        , m_cameraControllerDistanceFromInterestPointMeters(cameraControllerDistanceFromInterestPointMeters)
        {}
        Eegeo::Camera::GlobeCamera::GlobeCameraController* Create();
    private:
        Eegeo::Modules::Map::MapModule& m_mapModule;
        Eegeo::Modules::Map::Layers::TerrainModelModule& m_terrainModelModule;
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_touchController;
        const IScreenPropertiesProvider& m_screenPropertiesProvider;
        const Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration m_config;
        const bool m_tiltEnabled;
        const float m_interestPointLatitudeDegrees;
        const float m_interestPointLongitudeDegrees;
        const float m_interestPointAltitudeMeters;
        const float m_cameraControllerOrientationDegrees;
        const float m_cameraControllerDistanceFromInterestPointMeters;
    };
}