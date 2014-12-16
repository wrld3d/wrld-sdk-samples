// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ScreenUnprojectExample.h"
#include "EarthConstants.h"
#include "RenderCamera.h"
#include "VectorMath.h"
#include "SphereMesh.h"
#include "TerrainHeightProvider.h"
#include "LatLongAltitude.h"
#include "DebugRenderer.h"
#include "GlobeCameraController.h"

namespace
{
//represents a ray originating from an ecef position
struct Ray
{
	Eegeo::dv3 origin;
	Eegeo::v3 dir;
};

bool TryGetRayIntersectionWithEarthSizedSphereCenteredAtOrigin(const Ray &ray, Eegeo::dv3 &intersectionPoint)
{
	Eegeo::dv3 origin = ray.origin;
	Eegeo::v3 dirInv = -ray.dir;

	double a =
	    dirInv.GetX() * dirInv.GetX()
	    + dirInv.GetY() * dirInv.GetY()
	    + dirInv.GetZ() * dirInv.GetZ();

	double b =
	    dirInv.GetX() * (2.0 * origin.GetX())
	    + dirInv.GetY() * (2.0 * origin.GetY())
	    + dirInv.GetZ() * (2.0 * origin.GetZ());

	double c = 0.0;

	c += origin.GetX() * origin.GetX()
	     + origin.GetY() * origin.GetY()
	     + origin.GetZ() * origin.GetZ();

	c -= Eegeo::Space::EarthConstants::RadiusSquared;

	double d = b * b + (-4.0) * a * c;

	if (d < 0) return false;

	d = sqrt(d);

	double t = (-0.5) * (b - d) / a;

	if (t >= 0.0) return false;

	intersectionPoint.SetX(origin.GetX() + (dirInv.GetX() * t));
	intersectionPoint.SetY(origin.GetY() + (dirInv.GetY() * t));
	intersectionPoint.SetZ(origin.GetZ() + (dirInv.GetZ() * t));

	return true;
}
}

namespace Examples
{
    ScreenUnprojectExample::ScreenUnprojectExample(Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                                   Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                                   Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_debugRenderer(debugRenderer)
	, m_terrainHeightProvider(terrainHeightProvider)
{

}

void ScreenUnprojectExample::Start()
{

}

void ScreenUnprojectExample::Suspend()
{
    
    
}

void ScreenUnprojectExample::Update(float dt)
{
    Eegeo::Camera::RenderCamera renderCamera(GetGlobeCameraController().GetRenderCamera());
    
    //select the middle of the client screen as the position of the sphere
	float screenPointOfInterestX = (renderCamera.GetViewportWidth()/2.0f);
	float screenPointOfInterestY = (renderCamera.GetViewportHeight()/2.0f);

	//normalize this
	float nx = 2.0f * screenPointOfInterestX / renderCamera.GetViewportWidth() - 1.f;
	float ny = - 2.0f * screenPointOfInterestY / renderCamera.GetViewportHeight() + 1.f;

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

	//check intersection with a world space ray from camera position
	Ray ray;
	ray.origin = renderCamera.GetEcefLocation();
	ray.dir = (unprojectedFarWorld - unprojectedNearWorld).Norm();

	Eegeo::dv3 intersectionPoint;
	if(TryGetRayIntersectionWithEarthSizedSphereCenteredAtOrigin(ray, intersectionPoint))
	{
		//we are intersecting the idealised sphere, so get height at the intersection location
		//and set sphere height to result
		float height = 0.f;
		m_terrainHeightProvider.TryGetHeight(intersectionPoint, 0, height);
		Eegeo::Space::LatLongAltitude intersectionLocation = Eegeo::Space::LatLongAltitude::FromECEF(intersectionPoint);
		intersectionLocation.SetAltitude(height);
    
        m_debugRenderer.SetDepthTestEnabled(true);
        m_debugRenderer.DrawSphere(intersectionLocation.ToECEF(), 50.f, Eegeo::v4(1.f, 0.f, 0.f, 1.f));
	}
}

}
