// Copyright eeGeo Ltd 2015, All Rights Reserved

#pragma once

#include "IRouteThicknessPolicy.h"
#include "Routes.h"

namespace Examples
{
    class ExampleRouteThicknessPolicy : public Eegeo::Routes::Style::Thickness::IRouteThicknessPolicy
    {
    public:
        float GetThicknessScale(const Eegeo::Routes::Fitting::FittedRoute& route) const
        {
            return 5.0f;
        }
    };
}
