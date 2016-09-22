// Copyright eeGeo Ltd (2012-2014), All Rights Reserved
#pragma once

#include <jni.h>
#include "AndroidNativeState.h"
#include "IVRModeTracker.h"

namespace Examples
{
    class AndroidVRModeTracker : public IVRModeTracker
    {
        AndroidNativeState& m_nativeState;
        
    public:
        
        AndroidVRModeTracker(AndroidNativeState& nativeState);
        virtual void EnterVRMode() ;
        virtual void ExitVRMode() ;
    };
}
