// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "GlobeCameraExampleBase.h"
#include "ScreenProperties.h"
#include "GlobeCameraController.h"
#include "GlobeCameraTouchController.h"
#include "ScreenProperties.h"

namespace Examples
{
    GlobeCameraExampleBase::GlobeCameraExampleBase(Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                   Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : m_pGlobeCameraController(pCameraController)
    , m_globeCameraTouchController(cameraTouchController)
    {
    }
    
    GlobeCameraExampleBase::~GlobeCameraExampleBase()
    {
        delete m_pGlobeCameraController;
    }

    void GlobeCameraExampleBase::EarlyUpdate(float dt)
    {
        m_pGlobeCameraController->Update(dt);
    }
    
    void GlobeCameraExampleBase::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
        m_pGlobeCameraController->UpdateScreenProperties(screenProperties);
    }
    
    Eegeo::Camera::CameraState GlobeCameraExampleBase::GetCurrentCameraState() const
    {
        return m_pGlobeCameraController->GetCameraState();
    }
    
    void GlobeCameraExampleBase::Event_TouchRotate(const AppInterface::RotateData& data)
    {
        m_globeCameraTouchController.Event_TouchRotate(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchRotate_Start(const AppInterface::RotateData& data)
    {
        m_globeCameraTouchController.Event_TouchRotate_Start(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchRotate_End(const AppInterface::RotateData& data)
    {
        m_globeCameraTouchController.Event_TouchRotate_End(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchPinch(const AppInterface::PinchData& data)
    {
        m_globeCameraTouchController.Event_TouchPinch(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchPinch_Start(const AppInterface::PinchData& data)
    {
        m_globeCameraTouchController.Event_TouchPinch_Start(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchPinch_End(const AppInterface::PinchData& data)
    {
        m_globeCameraTouchController.Event_TouchPinch_End(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchPan(const AppInterface::PanData& data)
    {
        m_globeCameraTouchController.Event_TouchPan(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchPan_Start(const AppInterface::PanData& data)
    {
        m_globeCameraTouchController.Event_TouchPan_Start(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchPan_End(const AppInterface::PanData& data)
    {
        m_globeCameraTouchController.Event_TouchPan_End(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchTap(const AppInterface::TapData& data)
    {
        m_globeCameraTouchController.Event_TouchTap(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchDoubleTap(const AppInterface::TapData& data)
    {
        m_globeCameraTouchController.Event_TouchDoubleTap(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchDown(const AppInterface::TouchData& data)
    {
        m_globeCameraTouchController.Event_TouchDown(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchMove(const AppInterface::TouchData& data)
    {
        m_globeCameraTouchController.Event_TouchMove(data);
    }
    
    void GlobeCameraExampleBase::Event_TouchUp(const AppInterface::TouchData& data)
    {
        m_globeCameraTouchController.Event_TouchUp(data);
    }
}