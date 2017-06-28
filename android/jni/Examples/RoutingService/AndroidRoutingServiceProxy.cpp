// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidRoutingServiceProxy.h"
#include "AndroidRoutingServiceExampleView.h"


JNIEXPORT void JNICALL Java_com_eegeo_examples_routingservice_RoutingServiceJniMethods_MoveUp(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    Examples::AndroidRoutingServiceExampleView* pExample = (Examples::AndroidRoutingServiceExampleView*)(nativeObjectPtr);

    pExample->MoveUp();
}


JNIEXPORT void JNICALL Java_com_eegeo_examples_routingservice_RoutingServiceJniMethods_MoveDown(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    Examples::AndroidRoutingServiceExampleView* pExample = (Examples::AndroidRoutingServiceExampleView*)(nativeObjectPtr);

    pExample->MoveDown();
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_routingservice_RoutingServiceJniMethods_GetRoute(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    Examples::AndroidRoutingServiceExampleView* pExample = (Examples::AndroidRoutingServiceExampleView*)(nativeObjectPtr);

    pExample->GetRoute();
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_routingservice_RoutingServiceJniMethods_ToggleExpanded(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    Examples::AndroidRoutingServiceExampleView* pExample = (Examples::AndroidRoutingServiceExampleView*)(nativeObjectPtr);

    pExample->ToggleExpanded();
}
