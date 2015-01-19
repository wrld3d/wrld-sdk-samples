// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EegeoWorld.h"
#include "TrafficCongestionExample.h"
#include <string>
#include <GlobeCameraController.h>
#include <CameraHelpers.h>

namespace
{
const std::string congestionLevelNames[] = {"Light", "Normal", "Heavy", "GridLock"};
const int RoadId = 0;
const float NumSecondsEachCongestion = 5.f;
}

namespace Examples
{
TrafficCongestionExample::TrafficCongestionExample(Eegeo::TrafficCongestion::ITrafficCongestionService& trafficCongestionService,
        Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
	, m_trafficCongestionService(trafficCongestionService)
	, m_timeAccumulator(5.f)
	, m_congestionValue(static_cast<int>(Eegeo::TrafficCongestion::CongestionLevel::Light))
	, m_key(Eegeo::Streaming::MortonKey::CreateFromString("01131232132001"))
{
    Eegeo::Space::EcefTangentBasis cameraInterestBasis;

    Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
            Eegeo::Space::LatLongAltitude::FromDegrees(37.787159, -122.400920, 0.0).ToECEF(),
            45.0f,
            cameraInterestBasis);

    pCameraController->SetView(cameraInterestBasis, 200.0f);
}

void TrafficCongestionExample::Suspend()
{
	m_trafficCongestionService.SetCongestionFor(
            m_key,
	        RoadId,
	        Eegeo::TrafficCongestion::CongestionLevel::Normal);
    
    
    
}

void TrafficCongestionExample::Update(float dt)
{
	if(m_timeAccumulator > NumSecondsEachCongestion)
	{
		Eegeo::TrafficCongestion::CongestionLevel::CongestionLevelValues congestionLevel =
		    static_cast<Eegeo::TrafficCongestion::CongestionLevel::CongestionLevelValues>(m_congestionValue);

		m_trafficCongestionService.SetCongestionFor(
                m_key,
                RoadId,
                congestionLevel);

		Eegeo_TTY(
                "Congestion level %s set on road id %d for morton key %s\n",
                congestionLevelNames[m_congestionValue].c_str(),
                RoadId,
                m_key.ToString().c_str());

		if(++m_congestionValue > Eegeo::TrafficCongestion::CongestionLevel::Gridlock)
		{
			m_congestionValue = 0;
		}

		m_timeAccumulator -= NumSecondsEachCongestion;
	}

	m_timeAccumulator += dt;
}
    
}
