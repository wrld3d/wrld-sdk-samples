// Copyright eeGeo Ltd 2016, All Rights Reserved

#ifndef __ExampleApp__RouteSelectionHelper__
#define __ExampleApp__RouteSelectionHelper__

#include <vector>
#include "Route.h"


class RouteSelectionHelper
{
public:
    struct RouteHitTestResult {
        int routeIndex;
        float distance;
        float paramAtClosestPoint;
        int pointIndexBeforeClosestPoint;
        RouteHitTestResult(int index, float dist, float param, float pointIndex)
        {
            routeIndex = index;
            distance = dist;
            paramAtClosestPoint = param;
            pointIndexBeforeClosestPoint = pointIndex;
        }
    };
    static RouteHitTestResult GetRouteClosestToPoint(const std::vector<const Eegeo::Routes::Route*>& routes, const Eegeo::dv3& ecefPoint);

};



#endif /* defined(__ExampleApp__RouteSelectionHelper__) */
