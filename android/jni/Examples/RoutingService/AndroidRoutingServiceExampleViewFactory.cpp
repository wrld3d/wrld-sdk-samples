// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidRoutingServiceExampleViewFactory.h"
#include "AndroidRoutingServiceExampleView.h"

namespace Examples
{

AndroidRoutingServiceExampleViewFactory::AndroidRoutingServiceExampleViewFactory(
    AndroidNativeState& nativeState)
	: m_nativeState(nativeState)
{

}

AndroidRoutingServiceExampleViewFactory::~AndroidRoutingServiceExampleViewFactory()
{

}

IRoutingServiceExampleView* AndroidRoutingServiceExampleViewFactory::CreateRoutingServiceExampleView() const
{
	return Eegeo_NEW(AndroidRoutingServiceExampleView)(m_nativeState);
}

}
