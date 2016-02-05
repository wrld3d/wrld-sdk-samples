// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EnvironmentNotifierExample.h"
#include "CubeMapCellInfo.h"

#include "DebugRenderer.h"

#define SPHERE_HEIGHT_ABOVE_SEA 10.0

namespace Examples
{
//EnvironmentNotifierExample//
EnvironmentNotifierExample::EnvironmentNotifierExample(Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                                       Eegeo::Resources::Terrain::TerrainStreaming& terrainStreaming,
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
	, m_terrainStreaming(terrainStreaming)
	, m_pObserver(NULL)
    , m_debugRenderer(debugRenderer)
{
}

void EnvironmentNotifierExample::Start()
{
	m_pObserver = new EnvironmentNotifierExampleTerrainStreamObserver(m_spheres);
	m_terrainStreaming.AddStreamingObserver(m_pObserver);
}

void EnvironmentNotifierExample::Suspend()
{
	m_terrainStreaming.RemoveStreamingObserver(m_pObserver);
	delete m_pObserver;
	m_pObserver = NULL;
    
    
}

void EnvironmentNotifierExample::Update(float dt)
{

}


void EnvironmentNotifierExample::Draw()
{
    for (TKeySphereMap::iterator it = m_spheres.begin(); it != m_spheres.end(); ++it)
    {
        const SphereData& sphere = it->second;
        
        m_debugRenderer.DrawSphere(sphere.spherePosition, 100.f, sphere.sphereColor);
    }
}

//EnvironmentNotifierExampleTerrainStreamObserver///
void EnvironmentNotifierExampleTerrainStreamObserver::AddSphere(const Eegeo::Streaming::MortonKey& key)
{
	Eegeo::Space::CubeMap::CubeMapCellInfo cellInfo(key);
	const Eegeo::dv2& resourceQuadtreeCellCenter = cellInfo.GetFaceCentre();
	Eegeo::dv3 worldSpaceCellCenter = Eegeo::Space::CubeMap::FacePointToWorld(cellInfo.GetFaceIndex(),
	                                  resourceQuadtreeCellCenter,
	                                  Eegeo::Space::EarthConstants::CubeSideLengthHalf);


	Eegeo::dv3 up = worldSpaceCellCenter.Norm();
	Eegeo::dv3 spherePosition = Eegeo::dv3::Scale(up, Eegeo::Space::EarthConstants::Radius + SPHERE_HEIGHT_ABOVE_SEA);

	Eegeo::v4 color(1.f, 0.f, 1.f, 0.75f);
    
    SphereData sphereData(spherePosition, color);

	m_spheres.insert(std::make_pair(key,sphereData));
}

void EnvironmentNotifierExampleTerrainStreamObserver::AddedStreamingResourceToSceneGraph(const Eegeo::Streaming::MortonKey& key)
{
	Eegeo_TTY("Adding Terrain Resource :: %s\n", key.ToString().c_str());
	AddSphere(key);
}

void EnvironmentNotifierExampleTerrainStreamObserver::RemovedStreamingResourceFromSceneGraph(const Eegeo::Streaming::MortonKey& key)
{
	Eegeo_TTY("Removing Terrain Resource :: %s\n", key.ToString().c_str());
	m_spheres.erase(key);
}
    

}
