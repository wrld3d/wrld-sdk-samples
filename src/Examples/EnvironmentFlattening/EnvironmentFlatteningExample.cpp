// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EnvironmentFlatteningExample.h"
#include "TimeHelpers.h"


using namespace Eegeo::Rendering;
using namespace Eegeo::Helpers::Time;


namespace Examples
{

const int ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS = 5000;
const float MINIMUM_ENVIRONMENT_SCALE = 0.015f;

EnvironmentFlatteningExample::EnvironmentFlatteningExample(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                           Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
	, m_environmentFlatteningService(environmentFlatteningService)
	,m_lastToggle(MillisecondsSinceEpoch())
	,m_scaleUp(true)
	,m_initialEnvironmentScale(environmentFlatteningService.GetCurrentScale())
{
}

void EnvironmentFlatteningExample::Suspend()
{
	m_environmentFlatteningService.SetCurrentScale(m_initialEnvironmentScale);
    
    
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
    
    scale = MINIMUM_ENVIRONMENT_SCALE + (1-MINIMUM_ENVIRONMENT_SCALE)*scale;
	m_environmentFlatteningService.SetCurrentScale(scale);
}

}
