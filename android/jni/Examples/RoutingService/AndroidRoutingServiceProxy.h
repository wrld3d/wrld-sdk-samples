// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ANDROIDROUTESIMULATIONPROXY_H_
#define ANDROIDROUTESIMULATIONPROXY_H_

#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_routingservice_RoutingServiceJniMethods_MoveUp(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_routingservice_RoutingServiceJniMethods_MoveDown(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_routingservice_RoutingServiceJniMethods_GetRoute(
	    JNIEnv* jenv, jobject obj,
	    jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_routingservice_RoutingServiceJniMethods_ToggleExpanded(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr);
}

#endif /* ANDROIDROUTESIMULATIONPROXY_H_ */
