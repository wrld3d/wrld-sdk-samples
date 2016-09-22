package com.eegeo.examples.routingservice;

public class RoutingServiceJniMethods 
{
	public static native void MoveUp(long nativeCallerPointer);
	public static native void MoveDown(long nativeCallerPointer);
	public static native void GetRoute(long nativeCallerPointer);
}
