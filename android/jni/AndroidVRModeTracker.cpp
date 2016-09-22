// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <jni.h>
#include "AndroidVRModeTracker.h"

namespace Examples
{
    
    AndroidVRModeTracker::AndroidVRModeTracker(AndroidNativeState& nativeState)
    :m_nativeState(nativeState)
    {
    }
    
    void AndroidVRModeTracker::EnterVRMode()
    {

		AndroidSafeNativeThreadAttachment attached(m_nativeState);
		JNIEnv* pEnv = attached.envForThread;

		jmethodID enterVRModeMethod = pEnv->GetMethodID(m_nativeState.activityClass, "enterVRMode", "()V");
		pEnv->CallVoidMethod(m_nativeState.activity, enterVRModeMethod);

    }

    void AndroidVRModeTracker::ExitVRMode()
    {

		AndroidSafeNativeThreadAttachment attached(m_nativeState);
		JNIEnv* pEnv = attached.envForThread;

		jmethodID exitVRModeMethod = pEnv->GetMethodID(m_nativeState.activityClass, "exitVRMode", "()V");
		pEnv->CallVoidMethod(m_nativeState.activity, exitVRModeMethod);

    }

}


