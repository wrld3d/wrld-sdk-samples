// Copyright eeGeo Ltd (2012-2014), All Rights Reserved
#pragma once

namespace Eegeo
{
	namespace VR
	{
		class VRCameraState
		{
		private:
			Eegeo::m33 m_currentCameraOrientation;
			Eegeo::m33 m_baseOrientation;
			Eegeo::m33 m_headTrackerOrientation;
			Eegeo::Camera::CameraState m_leftCameraState;
			Eegeo::Camera::CameraState m_rightCameraState;
		public:

			VRCameraState(const Eegeo::m33& currentCameraOrientation,
					const Eegeo::m33& baseOrientation,
					const Eegeo::m33& headTrackerOrientation,
					Eegeo::Camera::CameraState leftCameraState,
					Eegeo::Camera::CameraState rightCameraState)
			: m_currentCameraOrientation(currentCameraOrientation)
			, m_baseOrientation(baseOrientation)
			, m_headTrackerOrientation(headTrackerOrientation)
			, m_leftCameraState(leftCameraState)
			, m_rightCameraState(rightCameraState)
			{

			}

			VRCameraState()
			: m_leftCameraState(Eegeo::dv3::Zero(), Eegeo::dv3::Zero(), Eegeo::m44::CreateIdentity(), Eegeo::m44::CreateIdentity())
			, m_rightCameraState(Eegeo::dv3::Zero(), Eegeo::dv3::Zero(), Eegeo::m44::CreateIdentity(), Eegeo::m44::CreateIdentity())
			{

			}

	        const Eegeo::m33& GetCurrentCameraOrientation()const{return m_currentCameraOrientation;}
	        const Eegeo::m33& GetBaseOrientation()const{return m_baseOrientation;}
	        const Eegeo::m33& GetHeadTrackerOrientation()const{return m_headTrackerOrientation;}

	        const Eegeo::Camera::CameraState& GetCurrentLeftCameraState()const{return m_leftCameraState;}
	        const Eegeo::Camera::CameraState& GetCurrentRightCameraState()const{return m_rightCameraState;}

		};
	}
}
