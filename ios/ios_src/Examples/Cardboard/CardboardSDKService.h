// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Helpers.h"
#include "ICallback.h"
#include "HeadTracker.h"
#include "MagnetSensor.h"
#include "CallbackCollection.h"
namespace Examples
{

    class CardboardSDKService
    {
    public:
        CardboardSDKService();
        ~CardboardSDKService();
        void HeadViewValue(float value[]);
        void UpdatedCardboardProfile(float profileValue[]);
        void RegisterMagnetTrigreedCallBack(Eegeo::Helpers::ICallback0& callback);
        void UnRegisterMagnetTrigreedCallBack(Eegeo::Helpers::ICallback0& callback);
        CardboardSDK::HeadTracker & GetHeadTracker();

    private:
        CardboardSDK::MagnetSensor *m_pMangnetSensor;
        CardboardSDK::HeadTracker *m_pCardBoardHeadTracker;
        Eegeo::Helpers::CallbackCollection0 m_appModeChangedCallbacks;


    };

}
