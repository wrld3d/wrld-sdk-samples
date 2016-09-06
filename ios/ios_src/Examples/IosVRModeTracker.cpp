// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "IosVRModeTracker.h"

namespace Examples
{
    IosVRModeTracker::IosVRModeTracker()
    {
    
    }
    IosVRModeTracker::~IosVRModeTracker()
    {
    
    }
    void IosVRModeTracker::EnterVRMode()
    {
        UIDeviceOrientation currentOrientation = [[UIDevice currentDevice] orientation];
        if (currentOrientation != UIDeviceOrientationLandscapeRight)
        {
            NSNumber *value = [NSNumber numberWithInt:UIDeviceOrientationLandscapeRight];
            [[UIDevice currentDevice] setValue:value forKey:@"orientation"];
        }
    }
    void IosVRModeTracker::ExitVRMode()
    {
        UIDeviceOrientation currentOrientation = [[UIDevice currentDevice] orientation];
        if (currentOrientation != UIDeviceOrientationPortraitUpsideDown)
        {
            NSNumber *value = [NSNumber numberWithInt:UIDeviceOrientationPortraitUpsideDown];
            [[UIDevice currentDevice] setValue:value forKey:@"orientation"];
        }
    }
}