// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "Pick3DObjectExample.h"
#include "Plane.h"
#include "RenderCamera.h"
#include "ScreenProperties.h"
#include "DebugRenderer.h"
#include "GlobeCameraController.h"

#define SPHERE_RADIUS 20.0
#define UNPICKED_COLOUR Eegeo::v4(1.0f, 0.0f, 1.0f, 0.8f)
#define PICKED_COLOUR Eegeo::v4(1.0f, 1.0f, 0.0f, 0.8f)

namespace Examples
{
Pick3DObjectExample::Pick3DObjectExample(
                                         Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                         Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                         Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController
                                         )
	: GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_interestLocation(Eegeo::Space::LatLongAltitude::FromECEF(pCameraController->GetEcefInterestPoint()))
    ,m_movingObject(false)
	,m_pObject(NULL)
    ,m_debugRenderer(debugRenderer)
{

}

void Pick3DObjectExample::Start()
{
	m_movingObject = false;

	Eegeo::Space::LatLongAltitude objectStartLocation = m_interestLocation;
	objectStartLocation.SetAltitude(200.0f);
	m_objectLocationEcef = objectStartLocation.ToECEF();

    m_objectColor = UNPICKED_COLOUR;
}

void Pick3DObjectExample::Suspend()
{
	delete m_pObject;
	m_pObject = NULL;
    
    
    
}

void Pick3DObjectExample::Update(float dt)
{
	m_debugRenderer.DrawSphere(m_objectLocationEcef, 50.f, m_objectColor);
}

void Pick3DObjectExample::Draw()
{
}

void Pick3DObjectExample::Event_TouchPan(const AppInterface::PanData& data)
{
	if (m_movingObject)
        return;
    
    GlobeCameraExampleBase::Event_TouchPan(data);
}

void Pick3DObjectExample::Event_TouchDown(const AppInterface::TouchData& data)
{
	bool insideSphere = IsScreenPointInsideModel(data.point);

	if(insideSphere)
	{
		m_objectColor = PICKED_COLOUR;
		m_movingObject = true;
        return;
	}

	GlobeCameraExampleBase::Event_TouchDown(data);
}

void Pick3DObjectExample::Event_TouchUp(const AppInterface::TouchData& data)
{
	m_movingObject = false;

	m_objectColor = UNPICKED_COLOUR;

	GlobeCameraExampleBase::Event_TouchUp(data);
}

void Pick3DObjectExample::CreateWorldSpaceRayFromScreen(const Eegeo::v2& screenPoint, Ray& ray)
{
    const Eegeo::Camera::RenderCamera& renderCamera = GetGlobeCameraController().GetRenderCamera();

    // todo - this assumes viewport origin is 0,0

	//normalize the point
	float nx = 2.0f * screenPoint.GetX() / renderCamera.GetViewportWidth() - 1.f;
	float ny = - 2.0f * screenPoint.GetY() / renderCamera.GetViewportHeight() + 1.f;

	//prepare near and far points
	Eegeo::v4 near(nx, ny, 0.0f, 1.0f);
	Eegeo::v4 far(nx, ny, 1.0f, 1.0f);

	Eegeo::m44 invVP;
	Eegeo::m44::Inverse(invVP, renderCamera.GetViewProjectionMatrix());

	//unproject the points
	Eegeo::v4 unprojectedNear = Eegeo::v4::Mul(near, invVP);
	Eegeo::v4 unprojectedFar = Eegeo::v4::Mul(far, invVP);

	//convert to 3d
	Eegeo::v3 unprojectedNearWorld = unprojectedNear / unprojectedNear.GetW();
	Eegeo::v3 unprojectedFarWorld = unprojectedFar / unprojectedFar.GetW();

	//check intersection with a ray cast from camera position
	ray.origin = renderCamera.GetEcefLocation();
	ray.direction = (unprojectedNearWorld - unprojectedFarWorld).Norm();
}

bool Pick3DObjectExample::IsScreenPointInsideModel(const Eegeo::v2& screenPoint)
{
	Ray ray;
	CreateWorldSpaceRayFromScreen(screenPoint, ray);
	ray.origin -= m_objectLocationEcef; //make object space

	//the following is a standard ray sphere intersection - for other shapes, an appropriate intersection method
	//should be used

	double a =
	    ray.direction.GetX() * ray.direction.GetX()
	    + ray.direction.GetY() * ray.direction.GetY()
	    + ray.direction.GetZ() * ray.direction.GetZ();

	double b =
	    ray.direction.GetX() * (2.0 * ray.origin.GetX())
	    + ray.direction.GetY() * (2.0 * ray.origin.GetY())
	    + ray.direction.GetZ() * (2.0 * ray.origin.GetZ());

	double c =
	    (ray.origin.GetX() * ray.origin.GetX()
	     + ray.origin.GetY() * ray.origin.GetY()
	     + ray.origin.GetZ() * ray.origin.GetZ());

	c -= (SPHERE_RADIUS * SPHERE_RADIUS);

	double d = b * b + (-4.0) * a * c;

	//if determinant is negative sphere is in negative ray direction so can't hit
	if (d < 0.0)
	{
		return false;
	}

	d = sqrt(d);

	double t = (-0.5) * (b - d) / a;

	if (t >= 0.0)
	{
		return false;
	}

	return true;
}

}
