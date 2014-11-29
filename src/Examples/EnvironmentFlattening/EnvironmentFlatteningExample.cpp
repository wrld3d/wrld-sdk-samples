// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EnvironmentFlatteningExample.h"
#include "TimeHelpers.h"

using namespace Examples;
using namespace Eegeo::Rendering;
using namespace Eegeo::Helpers::Time;

#define ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS 5000

EnvironmentFlatteningExample::EnvironmentFlatteningExample(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
        Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController)
	:m_environmentFlatteningService(environmentFlatteningService)
	,m_lastToggle(MillisecondsSinceEpoch())
	,m_scaleUp(true)
	,m_initialEnvironmentScale(environmentFlatteningService.GetCurrentScale())
	,m_globeCameraStateRestorer(*pCameraController)
    ,m_pCameraController(pCameraController)
{
}

void EnvironmentFlatteningExample::Suspend()
{
	m_environmentFlatteningService.SetCurrentScale(m_initialEnvironmentScale);
    delete m_pCameraController;
    m_pCameraController = NULL;
}

void EnvironmentFlatteningExample::Update(float dt)
{
	long long ms = MillisecondsSinceEpoch();
	long long delta = ms - m_lastToggle;

	while(delta > ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS)
	{
		m_lastToggle = ms;
		delta -= ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS;
		m_scaleUp = !m_scaleUp;
	}

	float scale = (float)delta/ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS;

	if(!m_scaleUp)
	{
		scale = 1.f - scale;
	}

	m_environmentFlatteningService.SetCurrentScale(scale);
}

const Eegeo::Camera::RenderCamera& EnvironmentFlatteningExample::GetRenderCamera() const
{
    return *m_pCameraController->GetCamera();
}

Eegeo::dv3 EnvironmentFlatteningExample::GetInterestPoint() const
{
    return m_pCameraController->GetEcefInterestPoint();
}