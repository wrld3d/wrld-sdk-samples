// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "VRDistortionMaterial.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            class IVRDistortionTransitionModel
            {
            public:
                virtual ~IVRDistortionTransitionModel(){}

                virtual void SetVisibilityParam(float param) = 0;
                virtual float GetVisibilityParam() const = 0;

                virtual void RegisterVisibilityChangedCallback(Helpers::ICallback0& callback) = 0;
                virtual void UnregisterVisibilityChangedCallback(Helpers::ICallback0& callback) = 0;
            };
        }
    }
}