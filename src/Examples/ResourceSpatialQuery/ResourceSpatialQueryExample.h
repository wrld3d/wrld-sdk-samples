// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__SpatialResourceQueryExample__
#define __ExampleApp__SpatialResourceQueryExample__

#include "GlobeCameraExampleBase.h"
#include "ResourceSpatialQueryService.h"
#include "Location.h"
#include "MortonKey.h"

namespace Examples
{
class ResourceSpatialQueryExample : public GlobeCameraExampleBase
{
private:
	Eegeo::Resources::ResourceSpatialQueryService& m_resourceSpatialQueryService;
	

	Eegeo::Streaming::MortonKey m_key;
	int m_numBuildings;

public:
	ResourceSpatialQueryExample(Eegeo::Resources::ResourceSpatialQueryService& resourceSpatialQueryService,
	                            Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

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
    
    
};
}

#endif /* defined(__ExampleApp__SpatialResourceQueryExample__) */
