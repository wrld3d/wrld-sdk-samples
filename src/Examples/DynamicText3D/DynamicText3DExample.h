// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__DynamicText3DExample__
#define __ExampleApp__DynamicText3DExample__

#include <vector>
#include <string>
#include "GlobeCameraExampleBase.h"

#include "PlaceNameView.h"
#include "EnvironmentFlatteningService.h"
#include "PlaceNameView.h"
#include "PlaceNameViewBuilder.h"
#include "GLState.h"
#include "EegeoWorld.h"
#include "IRenderableFilter.h"

namespace Examples
{

class DynamicText3DExample : public GlobeCameraExampleBase, public Eegeo::Rendering::IRenderableFilter
{
	Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
	Eegeo::Resources::PlaceNames::PlaceNameViewBuilder& m_placeNameViewBuilder;
	Eegeo::EegeoWorld& m_world;
    Eegeo::Rendering::RenderableFilters& m_renderableFilters;

	bool m_initialised;
	std::vector<Eegeo::Resources::PlaceNames::PlaceNameView*> m_views;

public:
	DynamicText3DExample(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
	                     Eegeo::Resources::PlaceNames::PlaceNameViewBuilder& placeNameViewBuilder,
	                     Eegeo::EegeoWorld& world,
	                     Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                         Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                         Eegeo::Rendering::RenderableFilters& renderableFilters);
    
    ~DynamicText3DExample();

	static std::string GetName()
	{
		return "DynamicText3DExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() { }
	void Update(float dt);
	void Draw();
	void Suspend();
    
    
    
    void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);

private:
	void CreateDynamic3DText(const std::string& str,
	                         float fontPointSize,
	                         double latitudeDegrees,
	                         double longitudeDegrees,
	                         const Eegeo::v3& colour,
	                         float alpha);
};
}

#endif /* defined(__ExampleApp__DynamicText3DExample__) */
