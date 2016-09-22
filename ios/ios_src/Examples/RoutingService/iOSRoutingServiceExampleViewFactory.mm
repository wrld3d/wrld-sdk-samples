// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "iOSRoutingServiceExampleViewFactory.h"
#include "iOSRoutingServiceExampleView.h"

namespace Examples
{

iOSRoutingServiceExampleViewFactory::iOSRoutingServiceExampleViewFactory(UIView* pView)
	: m_pView(pView)
{

}

iOSRoutingServiceExampleViewFactory::~iOSRoutingServiceExampleViewFactory()
{

}

IRoutingServiceExampleView* iOSRoutingServiceExampleViewFactory::CreateRoutingServiceExampleView() const
{
	return Eegeo_NEW(iOSRoutingServiceExampleView)(m_pView);
}

}
