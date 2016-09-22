// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ExampleApp_IRoutingServiceExampleViewFactory_h
#define ExampleApp_IRoutingServiceExampleViewFactory_h

#include "IRoutingServiceExampleView.h"

namespace Examples
{
class IRoutingServiceExampleViewFactory
{
public:

	virtual ~IRoutingServiceExampleViewFactory() { }

	virtual IRoutingServiceExampleView* CreateRoutingServiceExampleView() const = 0;
};
}



#endif
