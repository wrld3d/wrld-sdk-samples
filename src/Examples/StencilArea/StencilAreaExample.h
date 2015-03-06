// Copyright eeGeo Ltd 2015, All Rights Reserved

#pragma once

#include "StencilArea.h"
#include "StencilAreaViewFactory.h"
#include "StencilAreaModel.h"
#include "StencilAreaController.h"
#include "LatLongAltitude.h"
#include "GlobeCameraExampleBase.h"
#include "VectorMath.h"

namespace Examples
{
    class StencilAreaExample : public GlobeCameraExampleBase
    {
    private:
        Eegeo::Data::StencilArea::StencilAreaModel* m_pDundeeEastWard;
        Eegeo::Data::StencilArea::StencilAreaPaletteModel* m_pDundeeEastPalette;
        
        Eegeo::Data::StencilArea::StencilAreaModel* m_pCircleArea;
        Eegeo::Data::StencilArea::StencilAreaPaletteModel* m_pCirclePalette;
        
        Eegeo::Data::StencilArea::StencilAreaModel* m_pDundeeWestWard;
        Eegeo::Data::StencilArea::StencilAreaPaletteModel* m_pDundeeWestPalette;
        Eegeo::Data::StencilArea::StencilAreaController& m_StencilAreaController;
        
    public:
        StencilAreaExample(
                         Eegeo::Data::StencilArea::StencilAreaController& StencilAreaController,
                         Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                         Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);
        
        static std::string GetName()
        {
            return "StencilAreaExample";
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
        void CreateDundeeEastData();
        void CreateDundeeWestData();
    };
}