// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__SpatialResourceQueryExample__
#define __ExampleApp__SpatialResourceQueryExample__

#include "IExample.h"
#include "ResourceSpatialQueryService.h"
#include "Location.h"
#include "MortonKey.h"

namespace Examples
{
class ResourceSpatialQueryExample : public IExample
{
private:
	Eegeo::Resources::ResourceSpatialQueryService& m_resourceSpatialQueryService;
	Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pCameraController;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

	Eegeo::Streaming::MortonKey m_key;
	int m_numBuildings;

public:
	ResourceSpatialQueryExample(Eegeo::Resources::ResourceSpatialQueryService& resourceSpatialQueryService,
	                            Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController);

	static std::string GetName()
	{
		return "ResourceSpatialQueryExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void Update(float dt);
	void Draw() {}
	void Suspend() {}
    const Eegeo::Camera::RenderCamera& GetRenderCamera() const;
    Eegeo::dv3 GetInterestPoint() const;
};
}

#endif /* defined(__ExampleApp__SpatialResourceQueryExample__) */
