// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ScreenUnprojectExample__
#define __ExampleApp__ScreenUnprojectExample__

#include "GlobeCameraExampleBase.h"
#include "Rendering.h"
#include "Terrain.h"
#include "Camera.h"
#include "DebugRendering.h"

namespace Examples
{
    
class ScreenUnprojectExample : public GlobeCameraExampleBase
{
private:
    Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
	Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
    

public:
	ScreenUnprojectExample(Eegeo::DebugRendering::DebugRenderer& debugRenderer,
	                       Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
	                       Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

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
    
    
};
}


#endif /* defined(__ExampleApp__DebugSphereExample__) */
