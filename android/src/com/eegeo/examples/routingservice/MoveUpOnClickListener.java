package com.eegeo.examples.routingservice;
import com.eegeo.mobilesdkharness.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;
import com.eegeo.examples.routingservice.RoutingServiceJniMethods;

public class MoveUpOnClickListener extends NativeThreadOnClickHandler 
{
	public MoveUpOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread() 
	{
		RoutingServiceJniMethods.MoveUp(m_nativeCallerPointer);
	}
}
