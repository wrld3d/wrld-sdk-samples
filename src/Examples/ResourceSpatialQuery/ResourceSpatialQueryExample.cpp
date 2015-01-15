// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ResourceSpatialQueryExample.h"
#include "RenderCamera.h"
#include "CameraState.h"

namespace Examples
{
ResourceSpatialQueryExample::ResourceSpatialQueryExample(Eegeo::Resources::ResourceSpatialQueryService& resourceSpatialQueryService,
        Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
	, m_resourceSpatialQueryService(resourceSpatialQueryService)
	,m_numBuildings(0)
	,m_key(0)
{

}

void ResourceSpatialQueryExample::Update(float dt)
{
    Eegeo::dv3 ecefPointOfInterest(GetCurrentCameraState().InterestPointEcef());

	Eegeo::Streaming::MortonKey lastKey = m_key;

	std::vector<const Eegeo::Rendering::Scene::SceneElement<Eegeo::Rendering::Renderables::PackedRenderable>*> buildings = m_resourceSpatialQueryService.GetBuildingByEcefPoint(ecefPointOfInterest,
	        15,
	        10,
	        m_key);

	if(!(lastKey == m_key) || buildings.size() != m_numBuildings)
	{
		m_numBuildings = static_cast<int>(buildings.size());

		if(m_numBuildings == 0)
		{
			Eegeo_TTY("No resources detected\n");
		}
		else
		{
			Eegeo_TTY("%d buildings detected at camera focus point --> %s! (LOD %d)\n",
			          m_numBuildings,
			          m_key.ToString().c_str(),
			          m_key.Depth());
		}
	}
}

}