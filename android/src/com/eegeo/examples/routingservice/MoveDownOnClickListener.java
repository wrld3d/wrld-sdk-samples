package com.eegeo.examples.routingservice;
import com.eegeo.mobilesdkharness.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;
import com.eegeo.examples.routingservice.RoutingServiceJniMethods;

public class MoveDownOnClickListener extends NativeThreadOnClickHandler 
{
	public MoveDownOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread() 
	{
		RoutingServiceJniMethods.MoveDown(m_nativeCallerPointer);
	}
}
