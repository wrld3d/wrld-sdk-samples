// Copyright eeGeo Ltd 2015, All Rights Reserved

#pragma once

#include "Heatmaps.h"
#include "HeatmapViewFactory.h"
#include "HeatmapModel.h"
#include "HeatmapController.h"
#include "LatLongAltitude.h"
#include "GlobeCameraExampleBase.h"
#include "ITextureFileLoader.h"
#include "VectorMath.h"

namespace Examples
{
    class HeatmapExample : public GlobeCameraExampleBase
    {
    public:
        HeatmapExample(
                         Eegeo::Data::Heatmaps::HeatmapController& heatmapController,
                         Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                         Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                         Eegeo::Helpers::ITextureFileLoader& textureLoader);
        
        static std::string GetName()
        {
            return "HeatmapExample";
        }
        
        std::string Name() const
        {
            return GetName();
        }
        
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();
        
        void Event_TouchPan				(const AppInterface::PanData& data);
        void Event_TouchDown            (const AppInterface::TouchData& data);
        void Event_TouchUp              (const AppInterface::TouchData& data);
        
    private:
        Eegeo::Data::Heatmaps::HeatmapModel* m_pSfCrimeHeatmap;
        Eegeo::Data::Heatmaps::HeatmapController& m_heatmapController;
        Eegeo::Helpers::ITextureFileLoader& m_textureLoader;
        Eegeo::Helpers::GLHelpers::TextureInfo m_heatmapTexture;
        Eegeo::Helpers::GLHelpers::TextureInfo m_gradientTexture;
    };
}