// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DefaultCameraTouchControllerFactory.h"
#include "GlobeCameraTouchControllerConfiguration.h"
#include "GlobeCameraTouchController.h"


namespace Examples
{
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* DefaultCameraTouchControllerFactory::Create()
    {
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchControllerConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
        
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* pTouchController = new Eegeo::Camera::GlobeCamera::GlobeCameraTouchController(touchControllerConfig);
    
        return pTouchController;
    }
}