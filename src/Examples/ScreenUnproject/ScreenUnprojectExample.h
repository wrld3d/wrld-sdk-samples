// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ScreenUnprojectExample__
#define __ExampleApp__ScreenUnprojectExample__

#include "IExample.h"
#include "Rendering.h"
#include "Terrain.h"
#include "Camera.h"
#include "DebugRendering.h"

namespace Examples
{
    
class ScreenUnprojectExample : public IExample
{
private:
    Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
	Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;
    Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;

public:
	ScreenUnprojectExample(Eegeo::DebugRendering::DebugRenderer& debugRenderer,
	                       Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
	                       Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

	static std::string GetName()
	{
		return "ScreenUnprojectExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt);

	void Draw(){}
	void Suspend();
    const Eegeo::Camera::RenderCamera& GetRenderCamera() const;
};
}


#endif /* defined(__ExampleApp__DebugSphereExample__) */
