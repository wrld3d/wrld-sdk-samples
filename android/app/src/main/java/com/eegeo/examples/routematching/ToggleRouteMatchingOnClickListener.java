package com.eegeo.examples.routematching;


import com.eegeo.mobilesdkharness.INativeMessageRunner;
import com.eegeo.examples.NativeThreadOnClickHandler;

class ToggleRouteMatchingOnClickListener extends NativeThreadOnClickHandler
{
	public ToggleRouteMatchingOnClickListener(
			INativeMessageRunner nativeMessageRunner, 
			long nativeCallerPointer) 
	{
		super(nativeMessageRunner, nativeCallerPointer);
	}

	@Override
	protected void onClickNativeThread() 
	{
		RouteMatchingJniMethods.ToggleRouteMatching(m_nativeCallerPointer);
	}
}