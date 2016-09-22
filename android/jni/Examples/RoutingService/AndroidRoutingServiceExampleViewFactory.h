// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__AndroidRoutingServiceExampleViewFactory__
#define __ExampleApp__AndroidRoutingServiceExampleViewFactory__

#include "Types.h"
#include "IRoutingServiceExampleViewFactory.h"
#include "AndroidNativeState.h"

namespace Examples
{
class AndroidRoutingServiceExampleViewFactory : public IRoutingServiceExampleViewFactory, private Eegeo::NonCopyable
{
	AndroidNativeState& m_nativeState;

public:
	AndroidRoutingServiceExampleViewFactory(AndroidNativeState& androidNativeState);

	virtual ~AndroidRoutingServiceExampleViewFactory();

	virtual IRoutingServiceExampleView* CreateRoutingServiceExampleView() const;
};
}

#endif /* defined(__ExampleApp__AndroidRoutingServiceExampleViewFactory__) */
