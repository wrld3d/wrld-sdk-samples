// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ResourceSpatialQueryExample.h"
#include "RenderCamera.h"

using namespace Examples;

ResourceSpatialQueryExample::ResourceSpatialQueryExample(Eegeo::Resources::ResourceSpatialQueryService& resourceSpatialQueryService,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController)
	:m_resourceSpatialQueryService(resourceSpatialQueryService)
    ,m_cameraController(cameraController)
	,m_numBuildings(0)
	,m_key(0)
	,m_globeCameraStateRestorer(cameraController)
{

}

void ResourceSpatialQueryExample::Update(float dt)
{
	Eegeo::dv3 ecefPointOfInterest = m_cameraController.GetEcefInterestPoint();

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

const Eegeo::Camera::RenderCamera& ResourceSpatialQueryExample::GetRenderCamera() const
{
    return *m_cameraController.GetCamera();
}