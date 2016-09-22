package com.eegeo.examples.routingservice;
import com.eegeo.mobilesdkharness.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;
import com.eegeo.examples.routingservice.RoutingServiceJniMethods;

public class GetRouteOnClickListener extends NativeThreadOnClickHandler 
{
	public GetRouteOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread() 
	{
		RoutingServiceJniMethods.GetRoute(m_nativeCallerPointer);
	}
}
