// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ScreenPickExample.h"
#include "CameraHelpers.h"
#include "EarthConstants.h"
#include "SphereMesh.h"
#include "TerrainHeightProvider.h"
#include "RenderCamera.h"
#include "TerrainRayPicker.h"
#include "DebugRenderer.h"
#include "GlobeCameraController.h"

namespace Examples
{
ScreenPickExample::ScreenPickExample(Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                     const Eegeo::Resources::Terrain::Collision::ICollisionMeshResourceProvider& collisionMeshResourceProvider,
                                     Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                     Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_debugRenderer(debugRenderer)
{
	m_pRayPicker = new Eegeo::Resources::Terrain::Collision::TerrainRayPicker(terrainHeightProvider, collisionMeshResourceProvider);
}

ScreenPickExample::~ScreenPickExample()
{
	delete m_pRayPicker;
}

void ScreenPickExample::Start()
{

}

void ScreenPickExample::Suspend()
{
    
    
}

void ScreenPickExample::Update(float dt)
{
    m_debugRenderer.DrawSphere(m_spherePosition, 50.f, Eegeo::v4(1.f, 0.f, 0.f, 1.f));
}

void ScreenPickExample::Draw()
{
	
}
    
   
void ScreenPickExample::Event_TouchTap(const AppInterface::TapData& data)
{
    Eegeo::Camera::RenderCamera renderCamera(GetGlobeCameraController().GetRenderCamera());

	float screenPixelX = data.point.GetX();
	float screenPixelY = data.point.GetY();

	Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
	Eegeo::dv3 rayDirection;
	Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);

	Eegeo::dv3 rayIntersectionPoint;
	double intersectionParam;
	bool rayPick = m_pRayPicker->TryGetRayIntersection(rayOrigin, rayDirection, rayIntersectionPoint, intersectionParam);
	if (rayPick)
	{
        m_spherePosition = rayIntersectionPoint;
	}
    
    GlobeCameraExampleBase::Event_TouchTap(data);
}

}