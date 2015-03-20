// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__LoadModelExample__
#define __ExampleApp__LoadModelExample__

#include "GlobeCameraExampleBase.h"
#include "RenderCamera.h"
#include "LatLongAltitude.h"
#include "IAsyncTextureRequestor.h"
#include "Rendering.h"
#include "SceneModelFactory.h"
#include "DebugRendering.h"

namespace Examples
{
class LoadModelExample : public GlobeCameraExampleBase
{
private:

	Eegeo::Helpers::IFileIO& m_fileIO;
	Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& m_textureRequestor;
	Eegeo::Space::LatLongAltitude m_interestLocation;
    Eegeo::Rendering::SceneModels::SceneModelFactory& m_sceneModelFactory;
    Eegeo::Rendering::SceneModels::SceneModelFactory::TMaterialRepo& m_sceneModelMaterials;

	Eegeo::Rendering::SceneModels::SceneModel* m_pModel;
    Eegeo::Rendering::SceneModels::SceneModelMaterialResource* m_pDiscMaterialResource;
    Eegeo::Rendering::Filters::SceneModelRenderableFilter& m_sceneModelRenderableFilter;
    Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
    Eegeo::m44 m_transform;
	float m_elapsedTime;

public:
	LoadModelExample(
	                 Eegeo::Helpers::IFileIO& fileIO,
	                 Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
                     Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory,
                     Eegeo::Rendering::SceneModels::SceneModelFactory::TMaterialRepo& sceneModelMaterials,
                     Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter,
                     Eegeo::DebugRendering::DebugRenderer& debugRenderer,
	                 Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                     Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	static std::string GetName()
	{
		return "LoadModelExample";
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


#endif /* defined(__ExampleApp__LoadModelExample__) */
