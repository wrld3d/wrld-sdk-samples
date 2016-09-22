// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__iOSRoutingServiceExampleViewFactory__
#define __ExampleApp__iOSRoutingServiceExampleViewFactory__

#include "Types.h"
#include "IRoutingServiceExampleViewFactory.h"
#include "IRoutingServiceExampleView.h"
#import <UIKit/UIKit.h>

namespace Examples
{
class iOSRoutingServiceExampleViewFactory : public IRoutingServiceExampleViewFactory, private Eegeo::NonCopyable
{
	UIView* m_pView;

public:
	iOSRoutingServiceExampleViewFactory(UIView* pView);

	~iOSRoutingServiceExampleViewFactory();

	IRoutingServiceExampleView* CreateRoutingServiceExampleView() const;
};
}

#endif /* defined(__ExampleApp__iOSRoutingServiceExampleViewFactory__) */
