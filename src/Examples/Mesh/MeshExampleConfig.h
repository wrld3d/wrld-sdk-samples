// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace Examples
{
    struct MeshExampleConfig
    {
        std::string textureFilename;
        std::string asyncTextureUrl;
        std::pair<double, double> originLatLong;
        float altitude;
        float spacing;
        int meshRows;
        int meshColumns;
        
        float boxWidth;
        float boxHeight;
        
        float revsPerMinuteA;
        float revsPerMinuteB;
        
        float environmentFlatteningCyclesPerMinute;
        float secondsDelayBeforeTextureWebRequest;
        
        MeshExampleConfig()
        : originLatLong(std::make_pair(0, 0))
        , altitude(0.f)
        , spacing(0.f)
        , meshRows(0)
        , meshColumns(0)
        , boxWidth(0.f)
        , boxHeight(0.f)
        , revsPerMinuteA(0.f)
        , revsPerMinuteB(0.f)
        , environmentFlatteningCyclesPerMinute(0.f)
        , secondsDelayBeforeTextureWebRequest(0.f)
        {
            
        }
    };
}