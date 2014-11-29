// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "Pick3DObjectExample.h"
#include "Plane.h"
#include "RenderCamera.h"
#include "ScreenProperties.h"
#include "DebugRenderer.h"

#define SPHERE_RADIUS 20.0
#define UNPICKED_COLOUR Eegeo::v4(1.0f, 0.0f, 1.0f, 0.8f)
#define PICKED_COLOUR Eegeo::v4(1.0f, 1.0f, 0.0f, 0.8f)

namespace Examples
{
Pick3DObjectExample::Pick3DObjectExample(
                                         Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                         Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController
                                         )
	:m_interestLocation(Eegeo::Space::LatLongAltitude::FromECEF(pCameraController->GetEcefInterestPoint()))
    ,m_movingObject(false)
	,m_pObject(NULL)
	,m_globeCameraStateRestorer(*pCameraController)
    ,m_pCameraController(pCameraController)
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
    
    delete m_pCameraController;
    m_pCameraController = NULL;
}

void Pick3DObjectExample::Update(float dt)
{
	m_debugRenderer.DrawSphere(m_objectLocationEcef, 50.f, m_objectColor);
}

void Pick3DObjectExample::Draw()
{
}

bool Pick3DObjectExample::Event_TouchPan(const AppInterface::PanData& data)
{
	return m_movingObject;
}

bool Pick3DObjectExample::Event_TouchDown(const AppInterface::TouchData& data)
{
	bool insideSphere = IsScreenPointInsideModel(data.point);

	if(insideSphere)
	{
		m_objectColor = PICKED_COLOUR;
		m_movingObject = true;
	}

	return m_movingObject;
}

bool Pick3DObjectExample::Event_TouchUp(const AppInterface::TouchData& data)
{
	m_movingObject = false;

	m_objectColor = UNPICKED_COLOUR;

	return m_movingObject;
}

void Pick3DObjectExample::CreateWorldSpaceRayFromScreen(const Eegeo::v2& screenPoint, Ray& ray)
{
	const Eegeo::Camera::RenderCamera& renderCamera = *m_pCameraController->GetCamera();

    // todo - this assumes viewport origin is 0,0

	//normalize the point
	double nx = 2.0 * screenPoint.GetX() / renderCamera.GetViewportWidth() - 1;
	double ny = - 2.0 * screenPoint.GetY() / renderCamera.GetViewportHeight() + 1;

	//prepare near and far points
	Eegeo::v4 near(nx, ny, 0.0f, 1.0);
	Eegeo::v4 far(nx, ny, 1.0f, 1.0);

	Eegeo::m44 invVP;
	Eegeo::m44::Inverse(invVP, renderCamera.GetViewProjectionMatrix());

	//unproject the points
	Eegeo::v4 unprojectedNear = Eegeo::v4::Mul(near, invVP);
	Eegeo::v4 unprojectedFar = Eegeo::v4::Mul(far, invVP);

	//convert to 3d
	Eegeo::v3 unprojectedNearWorld = unprojectedNear / unprojectedNear.GetW();
	Eegeo::v3 unprojectedFarWorld = unprojectedFar / unprojectedFar.GetW();

	//check intersection with a ray cast from camera position
	ray.m_origin = renderCamera.GetEcefLocation();
	ray.m_direction = (unprojectedNearWorld - unprojectedFarWorld).Norm();
}

bool Pick3DObjectExample::IsScreenPointInsideModel(const Eegeo::v2& screenPoint)
{
	Ray ray;
	CreateWorldSpaceRayFromScreen(screenPoint, ray);
	ray.m_origin -= m_objectLocationEcef; //make object space

	//the following is a standard ray sphere intersection - for other shapes, an appropriate intersection method
	//should be used

	float a =
	    ray.m_direction.GetX() * ray.m_direction.GetX()
	    + ray.m_direction.GetY() * ray.m_direction.GetY()
	    + ray.m_direction.GetZ() * ray.m_direction.GetZ();

	float b =
	    ray.m_direction.GetX() * (2.0 * ray.m_origin.GetX())
	    + ray.m_direction.GetY() * (2.0 * ray.m_origin.GetY())
	    + ray.m_direction.GetZ() * (2.0 * ray.m_origin.GetZ());

	float c =
	    (ray.m_origin.GetX() * ray.m_origin.GetX()
	     + ray.m_origin.GetY() * ray.m_origin.GetY()
	     + ray.m_origin.GetZ() * ray.m_origin.GetZ());

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
    
const Eegeo::Camera::RenderCamera& Pick3DObjectExample::GetRenderCamera() const
{
    return *m_pCameraController->GetCamera();
}

Eegeo::dv3 Pick3DObjectExample::GetInterestPoint() const
{
    return m_pCameraController->GetEcefInterestPoint();
}

}
