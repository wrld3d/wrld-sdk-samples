// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ToggleTrafficExample.h"
#include "TimeHelpers.h"

using namespace Examples;
using namespace Eegeo::Traffic;
using namespace Eegeo::Helpers::Time;

#define TRAFFIC_ENABLED_SWITCH_DELAY_MILLISECONDS 5000

ToggleTrafficExample::ToggleTrafficExample(Eegeo::Traffic::TrafficSimulationController& trafficSimulation,
        Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController)
	:m_trafficSimulation(trafficSimulation)
	,m_lastToggle(MillisecondsSinceEpoch())
    ,m_pCameraController(pCameraController)
	,m_globeCameraStateRestorer(*pCameraController)
{
}

void ToggleTrafficExample::Suspend()
{
	m_trafficSimulation.SetEnabled(true);
    
    delete m_pCameraController;
    m_pCameraController = NULL;
}

void ToggleTrafficExample::Update(float dt)
{
	long long ms = MillisecondsSinceEpoch();

	if(ms - m_lastToggle > TRAFFIC_ENABLED_SWITCH_DELAY_MILLISECONDS)
	{
		m_lastToggle = ms;

		Eegeo_TTY("Toggling Traffic - Setting enabled = %s\n", m_trafficSimulation.Enabled() ? "false!" : "true!");
		m_trafficSimulation.SetEnabled(!m_trafficSimulation.Enabled());
	}
}

const Eegeo::Camera::RenderCamera& ToggleTrafficExample::GetRenderCamera() const
{
    return *m_pCameraController->GetCamera();
}

Eegeo::dv3 ToggleTrafficExample::GetInterestPoint() const
{
    return m_pCameraController->GetEcefInterestPoint();
}