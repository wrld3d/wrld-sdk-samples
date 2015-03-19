// Copyright eeGeo Ltd 2015, All Rights Reserved

#pragma once

#include "StencilArea.h"
#include "StencilAreaViewFactory.h"
#include "StencilAreaModel.h"
#include "StencilAreaController.h"
#include "LatLongAltitude.h"
#include "GlobeCameraExampleBase.h"
#include "VectorMath.h"
#include <vector>

namespace Examples
{
    class StencilAreaExample : public GlobeCameraExampleBase
    {
    private:
        typedef std::vector<Eegeo::Data::StencilArea::StencilAreaPaletteModel*> TPalettes;
        typedef std::vector<Eegeo::Data::StencilArea::StencilAreaModel*> TOutlines;
        
        TPalettes m_palettes;
        TOutlines m_outlines;
        
        Eegeo::Data::StencilArea::StencilAreaController& m_controller;
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
    };
}