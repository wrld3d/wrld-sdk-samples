// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__PinsExample__
#define __ExampleApp__PinsExample__

#include "GlobeCameraExampleBase.h"

#include "Rendering.h"
#include "Camera.h"
#include "ITextureFileLoader.h"

#include "Markers.h"
#include <string>


namespace Examples
{
/*!
 *  MarkersExample demonstrates the display of Markers within the 3D world.
 *  Markers can be placed on the terrain, up in the air or within indoor maps, and can be styled via the "labels style sheet" resource
 *  This example also demonstrates how Markers can be selected via tap gesture.
 */
class MarkersExample : public GlobeCameraExampleBase
{

public:
    MarkersExample(
        Eegeo::Markers::IMarkerService& markerService,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
        const Eegeo::Rendering::ScreenProperties& initialScreenProperties
	);
	virtual ~MarkersExample();

	static std::string GetName()
	{
		return "MarkersExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt);
	void Draw();
	void Suspend();
    
    virtual void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
    

	void Event_TouchTap(const AppInterface::TapData& data);

private:
	void CreateExampleMarkers();
    void DestroyExampleMarkers();
    
    Eegeo::Markers::IMarkerService& m_markerService;
    
    int m_markerId0;
    int m_markerId1;
    int m_markerId2;
    int m_markerId3;
    
    float m_wobbleTimer;
};
}

#endif /* defined(__ExampleApp__PinsExample__) */
