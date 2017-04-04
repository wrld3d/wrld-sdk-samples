// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EnvironmentFlatteningExample.h"
#include "TimeHelpers.h"


using namespace Eegeo::Rendering;
using namespace Eegeo::Helpers::Time;


namespace Examples
{

const int ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS = 5000;

EnvironmentFlatteningExample::EnvironmentFlatteningExample(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                           Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
	, m_environmentFlatteningService(environmentFlatteningService)
	,m_lastToggle(MillisecondsSinceEpoch())
{
}

void EnvironmentFlatteningExample::Suspend()
{
	m_environmentFlatteningService.SetIsFlattened(false);
}

void EnvironmentFlatteningExample::Update(float dt)
{
	long long ms = MillisecondsSinceEpoch();
	long long delta = ms - m_lastToggle;

	while(delta > ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS)
	{
		m_lastToggle = ms;
		delta -= ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS;
        
        m_environmentFlatteningService.SetIsFlattened(!m_environmentFlatteningService.IsFlattened());
	}

}

}
