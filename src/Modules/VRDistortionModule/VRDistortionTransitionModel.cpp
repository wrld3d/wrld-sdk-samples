// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "VRDistortionTransitionModel.h"
#include "MathFunc.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            VRDistortionTransitionModel::VRDistortionTransitionModel()
            : m_visibilityParam(1.0f)
            {
            }

            void VRDistortionTransitionModel::SetVisibilityParam(float param)
            {
                float oldParam = m_visibilityParam;
                m_visibilityParam = Eegeo::Math::Clamp01(param);

                if (oldParam != m_visibilityParam)
                {
                    NotifyStateChange();
                }
            }

            void VRDistortionTransitionModel::RegisterVisibilityChangedCallback(Helpers::ICallback0 &callback)
            {
                m_stateChangedCallbacks.AddCallback(callback);
            }

            void VRDistortionTransitionModel::UnregisterVisibilityChangedCallback(Helpers::ICallback0 &callback)
            {
                m_stateChangedCallbacks.RemoveCallback(callback);
            }

            void VRDistortionTransitionModel::NotifyStateChange()
            {
                m_stateChangedCallbacks.ExecuteCallbacks();
            }

        }
    }
}
