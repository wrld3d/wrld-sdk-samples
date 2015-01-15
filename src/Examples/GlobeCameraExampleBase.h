// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IExample.h"
#include "RenderCamera.h"
#include "GlobeCamera.h"
#include "Rendering.h"

namespace Examples
{
    class GlobeCameraExampleBase : public IExample, Eegeo::NonCopyable
    {
    public:
        GlobeCameraExampleBase(Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                               Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);
        
        virtual ~GlobeCameraExampleBase();
        
        virtual void EarlyUpdate(float dt);
        
        virtual void PreWorldDraw() {}
        
        virtual void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
        
        virtual Eegeo::Camera::CameraState GetCurrentCameraState() const;

        virtual void NotifyViewNeedsLayout() {}
        
        virtual void Event_TouchRotate 			(const AppInterface::RotateData& data);
        virtual void Event_TouchRotate_Start	(const AppInterface::RotateData& data);
        virtual void Event_TouchRotate_End 		(const AppInterface::RotateData& data);
        
        virtual void Event_TouchPinch 			(const AppInterface::PinchData& data);
        virtual void Event_TouchPinch_Start 	(const AppInterface::PinchData& data);
        virtual void Event_TouchPinch_End 		(const AppInterface::PinchData& data);
        
        virtual void Event_TouchPan				(const AppInterface::PanData& data);
        virtual void Event_TouchPan_Start		(const AppInterface::PanData& data);
        virtual void Event_TouchPan_End 		(const AppInterface::PanData& data);
        
        virtual void Event_TouchTap 			(const AppInterface::TapData& data);
        virtual void Event_TouchDoubleTap		(const AppInterface::TapData& data);
        virtual void Event_TouchDown 			(const AppInterface::TouchData& data);
        virtual void Event_TouchMove 			(const AppInterface::TouchData& data);
        virtual void Event_TouchUp 				(const AppInterface::TouchData& data);
        
    protected:
        Eegeo::Camera::GlobeCamera::GlobeCameraController& GetGlobeCameraController() const { return *m_pGlobeCameraController; }
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& GetGlobeCameraTouchController() const { return m_globeCameraTouchController; }
    private:
        Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pGlobeCameraController;
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;
    };
}