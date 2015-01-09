// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ScreenProperties.h"

namespace Examples
{
    class IScreenPropertiesProvider : public Eegeo::NonCopyable
    {
    public:
        virtual ~IScreenPropertiesProvider() {;}
        virtual const Eegeo::Rendering::ScreenProperties& GetScreenProperties() const = 0;
    };

    class ScreenPropertiesProvider : public IScreenPropertiesProvider
    {
    public:
        ScreenPropertiesProvider(const Eegeo::Rendering::ScreenProperties& screenProperties)
        : m_screenProperties(screenProperties)
        {}
        
        const Eegeo::Rendering::ScreenProperties& GetScreenProperties() const
        {
            return m_screenProperties;
        }
        
        void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
        {
            m_screenProperties = screenProperties;
        }
    private:
        Eegeo::Rendering::ScreenProperties m_screenProperties;
    };
}