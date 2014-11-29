// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ScreenPickExample.h"
#include "CameraHelpers.h"
#include "EarthConstants.h"
#include "SphereMesh.h"
#include "TerrainHeightProvider.h"
#include "RenderCamera.h"
#include "TerrainRayPicker.h"
#include "DebugRenderer.h"

namespace Examples
{
ScreenPickExample::ScreenPickExample(Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                     const Eegeo::Resources::Terrain::Collision::ICollisionMeshResourceProvider& collisionMeshResourceProvider,
                                     Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                     Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController)
    : m_pCameraController(pCameraController)
    , m_debugRenderer(debugRenderer)
	, m_globeCameraStateRestorer(*pCameraController)
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
    delete m_pCameraController;
    m_pCameraController = NULL;
}

void ScreenPickExample::Update(float dt)
{
    m_debugRenderer.DrawSphere(m_spherePosition, 50.f, Eegeo::v4(1.f, 0.f, 0.f, 1.f));
}

void ScreenPickExample::Draw()
{
	
}
    
const Eegeo::Camera::RenderCamera& ScreenPickExample::GetRenderCamera() const
{
    return *m_pCameraController->GetCamera();
}

Eegeo::dv3 ScreenPickExample::GetInterestPoint() const
{
    return m_pCameraController->GetEcefInterestPoint();
}
    
bool ScreenPickExample::Event_TouchTap(const AppInterface::TapData& data)
{
	const Eegeo::Camera::RenderCamera& renderCamera = *m_pCameraController->GetCamera();

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

	return true;
}
}