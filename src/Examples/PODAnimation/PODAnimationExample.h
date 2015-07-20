// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__PODAnimationExample__
#define __ExampleApp__PODAnimationExample__

#include "GlobeCameraExampleBase.h"
#include "RenderContext.h"
#include "LatLongAltitude.h"
#include "AsyncTexturing.h"
#include "Helpers.h"

#include "Rendering.h"

namespace Examples
{
    
class PODAnimationExample : public GlobeCameraExampleBase
{
private:

    Eegeo::Rendering::Filters::SceneModelRenderableFilter& m_renderableFilter;
    
    Eegeo::Rendering::SceneModels::SceneModelLoader& m_sceneModelLoader;
    Eegeo::Rendering::SceneModels::SceneModel* m_pModel;
    Eegeo::Rendering::SceneModels::SceneModelAnimator* m_pModelAnimator;

public:
	PODAnimationExample(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                        Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter,
                        Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);
    
    ~PODAnimationExample();

	static std::string GetName()
	{
		return "PODAnimationExample";
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


#endif /* defined(__ExampleApp__PODAnimationExample__) */
