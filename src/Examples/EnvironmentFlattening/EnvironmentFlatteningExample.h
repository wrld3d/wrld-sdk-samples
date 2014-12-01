// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__EnvironmentFlatteningExample__
#define __ExampleApp__EnvironmentFlatteningExample__

#include "GlobeCameraExampleBase.h"
#include "EnvironmentFlatteningService.h"

namespace Examples
{
class EnvironmentFlatteningExample : public GlobeCameraExampleBase
{
private:
	long long m_lastToggle;
	bool m_scaleUp;
	Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
	float m_initialEnvironmentScale;

public:
	EnvironmentFlatteningExample(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
	                             Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

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
    
    
};
}


#endif /* defined(__ExampleApp__EnvironmentFlatteningExample__) */
