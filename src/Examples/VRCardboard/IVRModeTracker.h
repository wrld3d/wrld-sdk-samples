// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace Examples
{
    class IVRModeTracker
    {
    public:
        virtual ~IVRModeTracker(){};
        virtual void EnterVRMode() = 0;
        virtual void ExitVRMode() = 0;
    };
}
