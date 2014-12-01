// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__DebugPrimitiveRenderingExample__
#define __ExampleApp__DebugPrimitiveRenderingExample__

#include "DebugRenderer.h"
#include "GlobeCameraExampleBase.h"

namespace Examples
{
class DebugPrimitiveRenderingExample : public GlobeCameraExampleBase
{
private:
	Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
    float m_frustumDrawTimer;

public:
	DebugPrimitiveRenderingExample(Eegeo::DebugRendering::DebugRenderer &debugRenderer,
	                               Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                   Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	static std::string GetName()
	{
		return "DebugPrimitiveRenderingExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt);
	void Draw();
	void Suspend();
    
    
};
}


#endif /* defined(__ExampleApp__DebugPrimitiveRenderingExample__) */
