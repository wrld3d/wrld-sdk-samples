// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MarkersExample.h"
#include "GlobeCameraController.h"
#include "IMarkerService.h"
#include "MarkerBuilder.h"
#include "CameraHelpers.h"

namespace Examples
{
    MarkersExample::MarkersExample(
    Eegeo::Markers::IMarkerService& markerService,
    Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
    const Eegeo::Rendering::ScreenProperties& initialScreenProperties
)
	: GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_markerService(markerService)
    , m_markerId0(-1)
    , m_markerId1(-1)
    , m_markerId2(-1)
    , m_markerId3(-1)
	, m_wobbleTimer(0.0f)
{
}

MarkersExample::~MarkersExample()
{
	
}

void MarkersExample::CreateExampleMarkers()
{
    // First, use the MarkerBuilder to create the creation params for creating a marker.
    Eegeo::Markers::MarkerCreateParams params0 = Eegeo::Markers::MarkerBuilder().SetLabelStyle("marker_default")
                                                                                .SetEntityName("marker_0")
                                                                                .SetLabelText("Marker text")
                                                                                .SetLabelIcon("park")
                                                                                .SetLocation(37.796021, -122.396043)
                                                                                .Build();
    
    // Then pass this param object to the MarkerService.  Keep a reference to the generated Id.
    m_markerId0 = m_markerService.Create(params0);
    
    // Styles are defined in the label_style_sheet.json file, configured in PlatformConfig along with the icon resources.
    // The icon set defined in pin_sheet.json can be referenced to add icons to labels too.
    // You can add new styles to the label style sheet and reference them like so.
    m_markerId1 = m_markerService.Create(Eegeo::Markers::MarkerBuilder().SetLabelStyle("marker_alternate")
                                                                        .SetEntityName("marker_1")
                                                                        .SetLabelText("Different style")
                                                                        .SetLocation(37.789404, -122.395194)
                                                                        .Build());
    
    // You can specify a vertical offset or anchor height like so
    m_markerId2 = m_markerService.Create(Eegeo::Markers::MarkerBuilder().SetLabelStyle("marker_default")
                                                                        .SetEntityName("marker_2")
                                                                        .SetLabelText("Marker with altitude")
                                                                        .SetLabelIcon("airport")
                                                                        .SetLocation(37.795207, -122.402760)
                                                                        .SetAnchorHeight(280.0f)
                                                                        .SetAnchorHeightMode(Eegeo::Markers::AnchorHeight::HeightAboveGround)
                                                                        .Build());
    
    // This one will have its position changed in update();
    m_markerId3 = m_markerService.Create(Eegeo::Markers::MarkerBuilder().SetLabelStyle("marker_default")
                                                                        .SetEntityName("marker_3")
                                                                        .SetLabelText("Wobbly marker")
                                                                        .SetLabelIcon("toilets")
                                                                        .SetLocation(37.795920, -122.393023)
                                                                        .Build());
    
	
}
    
void MarkersExample::DestroyExampleMarkers()
{
    m_markerService.Destroy(m_markerId0);
    m_markerService.Destroy(m_markerId1);
    m_markerService.Destroy(m_markerId2);
    m_markerService.Destroy(m_markerId3);
}

void MarkersExample::Start()
{
    CreateExampleMarkers();
    
    Eegeo::Space::EcefTangentBasis cameraInterestBasis;
    
    Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(Eegeo::Space::LatLongAltitude::FromDegrees(37.796021, -122.396043, 0.0).ToECEF(),
                                                                      -20.0f,
                                                                      cameraInterestBasis);
    
    GetGlobeCameraController().SetView(cameraInterestBasis, 2200.0f);
}

void MarkersExample::Suspend()
{
    DestroyExampleMarkers();
}

void MarkersExample::Update(float dt)
{
    m_wobbleTimer += dt;
    Eegeo::Space::LatLong position = Eegeo::Space::LatLong::FromDegrees(37.795920 + sinf(m_wobbleTimer)*0.001, -122.393023);
    
    Eegeo::Markers::IMarker& marker = m_markerService.Get(m_markerId3);
    marker.SetLocation(position.GetLatitudeInDegrees(), position.GetLongitudeInDegrees());
}
    
void MarkersExample::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties &screenProperties)
{
    GlobeCameraExampleBase::NotifyScreenPropertiesChanged(screenProperties);
}

void MarkersExample::Draw()
{
}


void MarkersExample::Event_TouchTap(const AppInterface::TapData& data)
{
	Eegeo::v2 screenTapPoint = Eegeo::v2(data.point.GetX(), data.point.GetY());
    Eegeo_TTY("Searching for Pins intersecting tap point %d,%d...", (int) screenTapPoint.GetX(), (int) screenTapPoint.GetY());
    
    // Avoid repositioning the Wobbly Marker as its position is being updated in the Update function
    int pickedMarkerId = -1;
    if(m_markerService.TryPick(screenTapPoint, pickedMarkerId) && pickedMarkerId != m_markerId3)
    {
        Eegeo::Markers::IMarker& pickedMarker = m_markerService.Get(pickedMarkerId);
        Eegeo_TTY("Picked marker: %s", pickedMarker.GetEntityName().c_str());
        
        // Reposition the marker
        Eegeo::Space::LatLongAltitude position = pickedMarker.GetAnchorLocation();
        position.SetLatitude(position.GetLatitude()+0.00001);
        pickedMarker.SetLocation(position.GetLatitudeInDegrees(), position.GetLongitudeInDegrees());
    }


    GlobeCameraExampleBase::Event_TouchTap(data);
}
}
