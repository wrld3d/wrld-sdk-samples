// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ReadHeadingExample__
#define __ExampleApp__ReadHeadingExample__

#include "IExample.h"
#include "Location.h"
#include "Camera.h"
#include "DebugRendering.h"

namespace Examples
{
class ReadHeadingExample : public IExample
{
private:

    Eegeo::EegeoWorld& m_world;
	Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
    Eegeo::Location::ILocationService& m_locationService;
    Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pCameraController;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

public:
    ReadHeadingExample(
		Eegeo::EegeoWorld& eegeoWorld,
		Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
		Eegeo::DebugRendering::DebugRenderer& debugRenderer,
		Eegeo::Location::ILocationService& locationService
	);

	static std::string GetName()
	{
		return "ReadHeadingExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start(){}
	void EarlyUpdate(float dt) {};
	void Update(float dt);
	void Draw() {}
	void Suspend(){}
    const Eegeo::Camera::RenderCamera& GetRenderCamera() const;
    Eegeo::dv3 GetInterestPoint() const;
};
}

#endif /* defined(__ExampleApp__ReadHeadingExample__) */
