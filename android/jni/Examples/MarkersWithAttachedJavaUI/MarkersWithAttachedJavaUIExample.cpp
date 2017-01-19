// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MarkersWithAttachedJavaUIExample.h"
#include "VectorMath.h"
#include "IMarkerService.h"
#include "MarkerBuilder.h"
#include "IMarker.h"
#include "CameraHelpers.h"
#include "Logger.h"
#include "Geometry.h"
#include "GlobeCameraController.h"

namespace Examples
{
MarkersWithAttachedJavaUIExample::MarkersWithAttachedJavaUIExample(
    Eegeo::EegeoWorld& world,
    AndroidNativeState& nativeState,
    Eegeo::Markers::IMarkerService& markerService,
    Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
    const Eegeo::Rendering::ScreenProperties& screenProperties
)
	: GlobeCameraExampleBase(pCameraController, cameraTouchController)
	, m_nativeState(nativeState)
	, m_markerService(markerService)
	, m_world(world)
	, m_buttonID(0)
	, m_markerId(0)
	, m_hudPinControllerClass(NULL)
	, m_hudPinController(NULL)
	, m_updateLocationMethodId(NULL)
{
}

MarkersWithAttachedJavaUIExample::~MarkersWithAttachedJavaUIExample()
{

}

void MarkersWithAttachedJavaUIExample::CreateExampleMarkers()
{
	// Create the marker using the MarkerService & MarkerBuilder
	m_markerId = m_markerService.Create(Eegeo::Markers::MarkerBuilder().SetLabelStyle("marker_default")
			.SetEntityName("marker")
			.SetLabelText("Marker text")
			.SetLabelIcon("park")
			.SetLocation(37.795796, -122.397380).Build());
}

void MarkersWithAttachedJavaUIExample::Start()
{
	CreateExampleMarkers();
	EXAMPLE_LOG("MarkersWithAttachedJavaUIExample::Start()");
}

void MarkersWithAttachedJavaUIExample::Suspend()
{
	// Remove the marker
	m_markerService.Destroy(m_markerId);

	//if we have not started and don't have a button handle, nothing to do in suspend()
	if(m_buttonID == 0)
	{
		return;
	}

	//get an env for the current thread
	//
	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//get the method to remove a pin, and remove the pins with our cached IDs
	jmethodID removeJavaPinButton = env->GetMethodID(m_hudPinControllerClass, "removeJavaPinButton", "(I)V");

	env->CallVoidMethod(m_hudPinController, removeJavaPinButton, m_buttonID);

	//delete the persistent references to the class and object
	env->DeleteGlobalRef(m_hudPinControllerClass);
	env->DeleteGlobalRef(m_hudPinController);

	//reset the button handle
	m_buttonID = 0;
}

void MarkersWithAttachedJavaUIExample::Update(float dt)
{
}

void MarkersWithAttachedJavaUIExample::Draw()
{
	//lazily create the pin button when we start drawing so it is not displayed on top of the loading screen
	if(m_world.Initialising())
	{
		return;
	}
	else if(m_buttonID == 0)
	{
		CreateJavaUIButton();
	}

	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	Eegeo_ASSERT(m_buttonID != 0);

	// Get the marker position on the screen
	const Eegeo::Markers::IMarker& marker = m_markerService.Get(m_markerId);
	Eegeo::v3 screenPosition = Eegeo::Camera::CameraHelpers::GetScreenPositionFromLatLongAlt(marker.GetAnchorLocation(), GetGlobeCameraController().GetRenderCamera());

	// now update the java ui to be in sync with the marker, positioned above it on screen.
	// the pixel nudging is hard-coded for simplicity; you should probably do something more sophisticated
	// (based on the size of your marker & java ui assets)
	const int buttonOffsetPixelsX = 40;
	const int buttonOffsetPixelsY = 110;

	env->CallVoidMethod(
	    m_hudPinController,
	    m_updateLocationMethodId,
	    m_buttonID,
	    screenPosition.GetX() - buttonOffsetPixelsX,
	    screenPosition.GetY() - buttonOffsetPixelsY
	);
}


void MarkersWithAttachedJavaUIExample::Event_TouchTap(const AppInterface::TapData& data)
{
	Eegeo::v2 screenTapPoint = Eegeo::v2(data.point.GetX(), data.point.GetY());

	Eegeo_TTY("Searching for Pins intersecting tap point %d,%d...", (int) screenTapPoint.GetX(), (int) screenTapPoint.GetY());

	int markerId = -1;
	if(m_markerService.TryPick(screenTapPoint, markerId))
	{
		const Eegeo::Markers::IMarker& marker = m_markerService.Get(markerId);
		Eegeo_TTY("Tapped marker %d with name %s", markerId, marker.GetEntityName().c_str());
	}
	else
	{
		Eegeo_TTY("None found.\n");
	}
	GlobeCameraExampleBase::Event_TouchTap(data);
}

void MarkersWithAttachedJavaUIExample::CreateJavaUIButton()
{
	//get an env for the current thread
	//
	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//get the java HudPinController class
	jstring strClassName = env->NewStringUTF("com/eegeo/examples/hudpincontroller/HudPinController");
	jclass hudPinControllerClass = m_nativeState.LoadClass(env, strClassName);
	env->DeleteLocalRef(strClassName);

	//create a persistent reference to the class
	m_hudPinControllerClass = static_cast<jclass>(env->NewGlobalRef(hudPinControllerClass));

	//cache the update method as we will call it frequently
	m_updateLocationMethodId = env->GetMethodID(m_hudPinControllerClass, "updatePinButtonScreenLocation", "(IFF)V");

	//get the method to add a pin - only keep a local reference as we wont use again
	jmethodID addJavaPinButton = env->GetMethodID(m_hudPinControllerClass, "addJavaPinButton", "()I");

	//get the constructor for the HudPinController, which takes the activity as a parameter
	jmethodID hudPinControllerConstructor = env->GetMethodID(m_hudPinControllerClass, "<init>", "(Lcom/eegeo/mobilesdkharness/MainActivity;)V");

	//construct an instance of the HudPinController, and create and cache a persistent reference to it.
	//we will make calls on to this instance, and it will add elements to the UI for us form Java.
	jobject instance = env->NewObject(m_hudPinControllerClass, hudPinControllerConstructor, m_nativeState.activity);
	m_hudPinController = env->NewGlobalRef(instance);

	//use the addJavaPinButton method on the hudPinController instance to add a pin to the hud.
	//we will get back an integer reference to the pin which we can use to update and remove it later,
	//so cache this
	m_buttonID = env->CallIntMethod(m_hudPinController, addJavaPinButton);
}
}



