// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ScreenPickExample__
#define __ExampleApp__ScreenPickExample__

#include "IExample.h"
#include "Rendering.h"
#include "Terrain.h"
#include "Camera.h"
#include "DebugRendering.h"

namespace Examples
{
/*!
 *  ScreenPickExample demonstrates projecting a ray through the camera origin and
 *  a screen pixel when the touch screen is tapped.
 *  We attempt to intersect the ray with the collision meshes of any currently
 *  streamed terrain resources, making use of Eegeo::Resources::Terrain::Collision::TerrainRayPicker.
 *  We draw a red marker sphere at the intersection point if found.
 */
class ScreenPickExample : public IExample
{
private:

	Eegeo::Resources::Terrain::Collision::TerrainRayPicker* m_pRayPicker;
    Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
    Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pCameraController;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;
    
    Eegeo::dv3 m_spherePosition;

public:
	ScreenPickExample(Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
	                  const Eegeo::Resources::Terrain::Collision::ICollisionMeshResourceProvider& collisionMeshResourceProvider,
                      Eegeo::DebugRendering::DebugRenderer& debugRenderer,
	                  Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController);

	virtual ~ScreenPickExample();

	static std::string GetName()
	{
		return "ScreenPickExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt);
	void Draw();
	void Suspend();
    const Eegeo::Camera::RenderCamera& GetRenderCamera() const;
    Eegeo::dv3 GetInterestPoint() const;

	bool Event_TouchTap(const AppInterface::TapData& data);
};
}

#endif /* defined(__ExampleApp__ScreenPickExample__) */
