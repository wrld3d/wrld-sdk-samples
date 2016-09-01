// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__IVRModeTracker__
#define __ExampleApp__IVRModeTracker__

namespace Examples
{
    class IVRModeTracker
    {
    public:
        virtual void EnterVRMode() = 0;
        virtual void ExitVRMode() = 0;
    };
}


#endif /* defined(__ExampleApp__IVRModeTracker__) */
