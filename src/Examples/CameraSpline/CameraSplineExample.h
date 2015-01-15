// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__CameraSplineExample__
#define __ExampleApp__CameraSplineExample__

#include "IExample.h"
#include "Camera.h"
#include "Geometry.h"
#include "Streaming.h"

namespace Examples
{
/*!
 *  CameraSplineExample demonstrates a camera controller that can animate the camera along a spline
 */
class CameraSplineExample : public IExample, Eegeo::NonCopyable
{
private:
	
    Eegeo::EegeoWorld& m_world;
    Eegeo::Streaming::ResourceCeilingProvider& m_resourceCeilingProvider;
    
    Eegeo::Geometry::CatmullRomSpline* m_pPositionSpline;
	Eegeo::Geometry::CatmullRomSpline* m_pTargetSpline;
    Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController* m_pSplineCameraController;
    
public:
	CameraSplineExample(Eegeo::EegeoWorld& eegeoWorld,
                        Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                        const Eegeo::Rendering::ScreenProperties& initialScreenProperties);
    
	static std::string GetName()
	{
		return "CameraSplineExample";
	}
	std::string Name() const
	{
		return GetName();
	}
    
	void Start();
	void EarlyUpdate(float dt);
	void Update(float dt) { }
    void PreWorldDraw() { }
	void Draw() {}
	void Suspend();
    
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

#endif /* defined(__ExampleApp__CameraSplineExample__) */
