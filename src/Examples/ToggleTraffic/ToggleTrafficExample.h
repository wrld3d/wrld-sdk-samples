// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ToggleTrafficExample__
#define __ExampleApp__ToggleTrafficExample__

#include "GlobeCameraExampleBase.h"
#include "TrafficSimulationController.h"

namespace Examples
{
class ToggleTrafficExample : public GlobeCameraExampleBase
{
private:
	long long m_lastToggle;
	Eegeo::Traffic::TrafficSimulationController& m_trafficSimulation;
    

public:
	ToggleTrafficExample(Eegeo::Traffic::TrafficSimulationController& trafficSimulation,
	                     Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	static std::string GetName()
	{
		return "ToggleTrafficExample";
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

#endif /* defined(__ExampleApp__ToggleTrafficExample__) */
