// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__DebugPrimitiveRenderingExample__
#define __ExampleApp__DebugPrimitiveRenderingExample__

#include "DebugRenderer.h"
#include "IExample.h"

namespace Examples
{
class DebugPrimitiveRenderingExample : public Examples::IExample
{
private:
	Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
    Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pCameraController;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;
    float m_frustumDrawTimer;

public:
	DebugPrimitiveRenderingExample(Eegeo::DebugRendering::DebugRenderer &debugRenderer,
	                               Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController);

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
    const Eegeo::Camera::RenderCamera& GetRenderCamera() const;
    Eegeo::dv3 GetInterestPoint() const;
};
}


#endif /* defined(__ExampleApp__DebugPrimitiveRenderingExample__) */
