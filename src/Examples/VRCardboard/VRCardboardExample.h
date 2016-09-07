// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__VRCardboardExample__
#define __ExampleApp__VRCardboardExample__

#include "VRCameraController.h"
#include "IExample.h"
#include "Camera.h"
#include "Geometry.h"
#include "Streaming.h"
#include "GlobeCamera.h"
#include "ICallback.h"

namespace Examples
{
/*!
 *  VRCardboardExample demonstrates a camera controller that can animate the camera along a spline
 */
class VRCardboardExample : public IExample, Eegeo::NonCopyable
{
private:
	
    float m_eyeDistance;
    Eegeo::EegeoWorld& m_world;
    
    Eegeo::VR::VRCameraController* m_pCameraController;
    
public:
    
    VRCardboardExample(Eegeo::EegeoWorld& eegeoWorld,
                          Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                          Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                          const Eegeo::Rendering::ScreenProperties& initialScreenProperties);
    
    virtual ~VRCardboardExample();
    
	static std::string GetName()
	{
		return "VRCardboardExample";
	}
	std::string Name() const
	{
		return GetName();
	}
    
	void Start();
    void OrientationUpdate();
	void EarlyUpdate(float dt);
	void Update(float dt) { }
    void PreWorldDraw() { }
	void Draw() {}
	void Suspend();
    
    const Eegeo::m33& getCurrentCameraOrientation();
    const Eegeo::m33& GetBaseOrientation();
    const Eegeo::m33& GetHeadTrackerOrientation();
    
    void UpdateCardboardProfile(float cardboardProfile[]);
    
    virtual Eegeo::Camera::RenderCamera& GetRenderCamera();
    virtual Eegeo::Camera::CameraState GetCurrentLeftCameraState(float headTansform[]) const;
    virtual Eegeo::Camera::CameraState GetCurrentRightCameraState(float headTansform[]) const;
    virtual Eegeo::Camera::CameraState GetCurrentCameraState() const;
    
    virtual void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);

    void NotifyViewNeedsLayout() {}
    

    
    void Event_TouchRotate 			(const AppInterface::RotateData& data) { }
    void Event_TouchRotate_Start	(const AppInterface::RotateData& data) { }
    void Event_TouchRotate_End 		(const AppInterface::RotateData& data) { }
    
    void Event_TouchPinch 			(const AppInterface::PinchData& data) { }
    void Event_TouchPinch_Start 	(const AppInterface::PinchData& data) { }
    void Event_TouchPinch_End 		(const AppInterface::PinchData& data) { }
    
    void Event_TouchPan				(const AppInterface::PanData& data) { }
    void Event_TouchPan_Start		(const AppInterface::PanData& data) { }
    void Event_TouchPan_End 		(const AppInterface::PanData& data) { }
    
    void Event_TouchTap 			(const AppInterface::TapData& data) { }
    void Event_TouchDoubleTap		(const AppInterface::TapData& data) { }
    void Event_TouchDown 			(const AppInterface::TouchData& data) { }
    void Event_TouchMove 			(const AppInterface::TouchData& data) { }
    void Event_TouchUp 				(const AppInterface::TouchData& data) { }

};
}

#endif /* defined(__ExampleApp__VRCardboardExample__) */
