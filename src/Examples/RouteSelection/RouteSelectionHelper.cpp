// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "RouteSelectionHelper.h"


using namespace Eegeo;
using namespace Eegeo::Routes;


RouteSelectionHelper::RouteHitTestResult RouteSelectionHelper::GetRouteClosestToPoint(const std::vector<const Routes::Route*>& routes, const Eegeo::dv3& ecefPoint)
    {
        int closestRouteIndex = -1;
        int indexBeforeNearest = -1;
        double paramAtNearest = -1.0;
        double closestRouteDistance = DBL_MAX;
        for (int i=0; i<routes.size(); i++)
        {
            double currentParamAtNearest;
            int currentIndexBeforeNearest;
            double distance = Routes::Route::DistanceToRoute(routes[i]->GetPoints(), ecefPoint, currentParamAtNearest, currentIndexBeforeNearest);
            if (distance < closestRouteDistance)
            {
                closestRouteIndex = i;
                indexBeforeNearest = currentIndexBeforeNearest;
                paramAtNearest = currentParamAtNearest;
                closestRouteDistance = distance;
            }
            
        }
        return RouteSelectionHelper::RouteHitTestResult(closestRouteIndex, closestRouteDistance, paramAtNearest, indexBeforeNearest);
    }

