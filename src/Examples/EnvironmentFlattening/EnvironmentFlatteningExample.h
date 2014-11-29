// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__EnvironmentFlatteningExample__
#define __ExampleApp__EnvironmentFlatteningExample__

#include "IExample.h"
#include "EnvironmentFlatteningService.h"

namespace Examples
{
class EnvironmentFlatteningExample : public IExample
{
private:
	long long m_lastToggle;
	bool m_scaleUp;
	Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
	float m_initialEnvironmentScale;
    Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pCameraController;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

public:
	EnvironmentFlatteningExample(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
	                             Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController);

	static std::string GetName()
	{
		return "EnvironmentFlatteningExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void Update(float dt);
	void Draw() {}
	void Suspend();
    const Eegeo::Camera::RenderCamera& GetRenderCamera() const;
    Eegeo::dv3 GetInterestPoint() const;
};
}


#endif /* defined(__ExampleApp__EnvironmentFlatteningExample__) */
