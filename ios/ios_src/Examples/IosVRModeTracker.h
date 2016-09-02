// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IVRModeTracker.h"
namespace Examples
{
    class IosVRModeTracker : public IVRModeTracker
    {
    public:
        IosVRModeTracker();
        ~IosVRModeTracker();
        void EnterVRMode();
        void ExitVRMode();
    };
}