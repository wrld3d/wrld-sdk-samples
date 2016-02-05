// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__EnvironmentNotifierExample__
#define __ExampleApp__EnvironmentNotifierExample__

#include <map>

#include "GlobeCameraExampleBase.h"
#include "RenderContext.h"
#include "SphereMesh.h"
#include "LatLongAltitude.h"
#include "TerrainStreaming.h"
#include "IStreamingObserver.h"
#include "MortonKey.h"

namespace Examples
{
    struct SphereData
    {
        SphereData(const Eegeo::dv3& position, const Eegeo::v4& color)
        : spherePosition(position)
        , sphereColor(color)
        {
            
        }
        
        Eegeo::dv3 spherePosition;
        Eegeo::v4 sphereColor;
    };
    
    typedef std::map<Eegeo::Streaming::MortonKey, SphereData> TKeySphereMap;
    
class EnvironmentNotifierExampleTerrainStreamObserver : public Eegeo::Streaming::IStreamingObserver
{
private:
	TKeySphereMap& m_spheres;

	void AddSphere(const Eegeo::Streaming::MortonKey& key);
public:
	EnvironmentNotifierExampleTerrainStreamObserver(TKeySphereMap& spheres)
    : m_spheres(spheres)
	{

	}
    
    ~EnvironmentNotifierExampleTerrainStreamObserver() {}

	void AddedStreamingResourceToSceneGraph(const Eegeo::Streaming::MortonKey& key);
	void RemovedStreamingResourceFromSceneGraph(const Eegeo::Streaming::MortonKey& key);
};

class EnvironmentNotifierExample : public GlobeCameraExampleBase
{
private:
	Eegeo::Resources::Terrain::TerrainStreaming& m_terrainStreaming;
	EnvironmentNotifierExampleTerrainStreamObserver* m_pObserver;
    Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;

	TKeySphereMap m_spheres;


public:
	EnvironmentNotifierExample(Eegeo::DebugRendering::DebugRenderer& debugRenderer,
	                           Eegeo::Resources::Terrain::TerrainStreaming& terrainStreaming,
	                           Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	static std::string GetName()
	{
		return "EnvironmentNotifierExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt);
	void Draw();
	void Suspend();
    
    
};
}


#endif /* defined(__ExampleApp__EnvironmentNotifierExample__) */
