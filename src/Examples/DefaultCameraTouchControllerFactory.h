// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "GlobeCameraTouchController.h"


namespace Examples
{
    class DefaultCameraTouchControllerFactory : public Eegeo::NonCopyable
    {
    public:
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* Create();
    };
}