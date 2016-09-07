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
        if (currentOrientation != UIDeviceOrientationLandscapeLeft)
        {
            NSNumber *pValue = [NSNumber numberWithInt:UIDeviceOrientationLandscapeLeft];
            [[UIDevice currentDevice] setValue:pValue forKey:@"orientation"];
        }
    }
    void IosVRModeTracker::ExitVRMode()
    {
        UIDeviceOrientation currentOrientation = [[UIDevice currentDevice] orientation];
        if (currentOrientation != UIDeviceOrientationPortraitUpsideDown)
        {
            NSNumber *pValue = [NSNumber numberWithInt:UIDeviceOrientationPortraitUpsideDown];
            [[UIDevice currentDevice] setValue:pValue forKey:@"orientation"];
        }
    }
}