// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__IRoutingServiceExampleView__
#define __ExampleApp__IRoutingServiceExampleView__

#include "Types.h"
#include "IUIActionHandler.h"

namespace Examples
{
class IRoutingServiceExampleView
{
public:

	virtual ~IRoutingServiceExampleView() { }
    
    virtual void AddToggleExpandedHandler(IUIActionHandler& handler)=0;
    
    virtual void RemoveToggleExpandedHandler(IUIActionHandler& handler)=0;
    
    virtual void ToggleExpanded()=0;

	virtual void AddMoveUpHandler(IUIActionHandler& handler)=0;

	virtual void RemoveMoveUpHandler(IUIActionHandler& handler)=0;

    virtual void MoveUp()=0;

	virtual void AddMoveDownHandler(IUIActionHandler& handler)=0;

	virtual void RemoveMoveDownHandler(IUIActionHandler& handler)=0;

    virtual void MoveDown()=0;

	virtual void AddGetRouteHandler(IUIActionHandler& handler)=0;

	virtual void RemoveGetRouteHandler(IUIActionHandler& handler)=0;

    virtual void GetRoute()=0;

    virtual void NotifyNeedsLayout()=0;

};
}


#endif /* defined(__ExampleApp__IRoutingServiceExampleView__) */
