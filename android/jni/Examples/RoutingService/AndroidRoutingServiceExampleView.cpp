// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidRoutingServiceExampleView.h"
#include "UIHelpers.h"
#include "AndroidRoutingServiceProxy.h"

namespace Examples
{
AndroidRoutingServiceExampleView::AndroidRoutingServiceExampleView(
    AndroidNativeState& androidNativeState)
	: m_nativeState(androidNativeState)
{
	//get an env for the current thread
	//
	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//get the java RoutingServiceExampleHud class
	jstring strClassName = env->NewStringUTF("com/eegeo/examples/routingservice/RoutingServiceExampleHud");
	jclass routingServiceExampleHudClass = m_nativeState.LoadClass(env, strClassName);
	env->DeleteLocalRef(strClassName);

	//create a persistent reference to the class
	m_routingServiceExampleHudClass = static_cast<jclass>(env->NewGlobalRef(routingServiceExampleHudClass));

	//get the constructor for the RoutingServiceExampleHud, which takes the activity, a pointer to 'this' as
	//a parameter, and a flag to indicate if currently in follow mode.
	jmethodID routingServiceExampleHudConstructor = env->GetMethodID(routingServiceExampleHudClass, "<init>", "(Lcom/eegeo/mobilesdkharness/MainActivity;J)V");

	jobject instance = env->NewObject(
	                       m_routingServiceExampleHudClass,
	                       routingServiceExampleHudConstructor,
	                       m_nativeState.activity,
	                       (jlong)(this));

	m_routingServiceExampleHud = env->NewGlobalRef(instance);
}

AndroidRoutingServiceExampleView::~AndroidRoutingServiceExampleView()
{
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//Get a reference to the 'removeHud' method and call it to remove the HUD.
	jmethodID removeHudMethod = env->GetMethodID(m_routingServiceExampleHudClass, "removeHud", "()V");
	env->CallVoidMethod(m_routingServiceExampleHud, removeHudMethod);

	//Destroy the cached global references.
	env->DeleteGlobalRef(m_routingServiceExampleHud);
	env->DeleteGlobalRef(m_routingServiceExampleHudClass);
}

void AndroidRoutingServiceExampleView::AddMoveUpHandler(IUIActionHandler& handler)
{
	m_moveUpHandlers.push_back(&handler);
}

void AndroidRoutingServiceExampleView::RemoveMoveUpHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_moveUpHandlers, &handler);
}

void AndroidRoutingServiceExampleView::MoveUp()
{
	InvokeAllHandlers(m_moveUpHandlers);
}

void AndroidRoutingServiceExampleView::AddMoveDownHandler(IUIActionHandler& handler)
{
	m_moveDownHandlers.push_back(&handler);
}

void AndroidRoutingServiceExampleView::RemoveMoveDownHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_moveDownHandlers, &handler);
}

void AndroidRoutingServiceExampleView::MoveDown()
{
	InvokeAllHandlers(m_moveDownHandlers);
}

void AndroidRoutingServiceExampleView::AddGetRouteHandler(IUIActionHandler& handler)
{
	m_getRouteHandlers.push_back(&handler);
}

void AndroidRoutingServiceExampleView::RemoveGetRouteHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_getRouteHandlers, &handler);
}

void AndroidRoutingServiceExampleView::GetRoute()
{
	InvokeAllHandlers(m_getRouteHandlers);
}

}

