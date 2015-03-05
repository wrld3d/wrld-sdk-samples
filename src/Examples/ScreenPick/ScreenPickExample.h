// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ScreenPickExample__
#define __ExampleApp__ScreenPickExample__

#include "GlobeCameraExampleBase.h"
#include "Rendering.h"
#include "Terrain.h"
#include "Camera.h"
#include "DebugRendering.h"
#include "Collision.h"

namespace Examples
{
/*!
 *  ScreenPickExample demonstrates projecting a ray through the camera origin and
 *  a screen pixel when the touch screen is tapped.
 *  We attempt to intersect the ray with the collision meshes of any currently
 *  streamed terrain resources, making use of Eegeo::Resources::Terrain::Collision::TerrainRayPicker.
 *  We draw a red marker sphere at the intersection point if found.
 */
class ScreenPickExample : public GlobeCameraExampleBase
{
private:

	Eegeo::Resources::Terrain::Collision::TerrainRayPicker* m_pRayPicker;
    Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
    
    
    Eegeo::dv3 m_spherePosition;

public:
	ScreenPickExample(Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
	                  const Eegeo::Collision::ICollisionBvhProvider& collisionMeshResourceProvider,
                      Eegeo::DebugRendering::DebugRenderer& debugRenderer,
	                  Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

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
    
    

	void Event_TouchTap(const AppInterface::TapData& data);
};
}

#endif /* defined(__ExampleApp__ScreenPickExample__) */
