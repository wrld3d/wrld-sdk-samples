// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__PinOverModelExample__
#define __ExampleApp__PinOverModelExample__

#include "GlobeCameraExampleBase.h"

#include "Rendering.h"
#include "Camera.h"
#include "ITextureFileLoader.h"
#include "IFileIO.h"
#include "PinsModule.h"
#include <string>
#include "IAsyncTextureRequestor.h"
#include "GlobalFogging.h"
#include "Model.h"
#include "NullMaterial.h"
#include "IRenderableFilter.h"
#include "RenderableBase.h"
#include "NullMaterial.h"

namespace Examples
{
class PinOverModelExample : public GlobeCameraExampleBase
{
private:

	class MyModelRenderable : public Eegeo::Rendering::RenderableBase
	{
		Eegeo::Model& m_model;
        Eegeo::Lighting::GlobalFogging& m_globalFogging;
        Eegeo::dv3 m_observerLocationEcef;

	public:
		MyModelRenderable(Eegeo::Model& model,
		                  Eegeo::Lighting::GlobalFogging& globalFogging,
		                  Eegeo::Rendering::Materials::NullMaterial& nullMat);
        
        void UpdateObserverLocation(const Eegeo::dv3& observerLocationEcef);
        
		void Render(Eegeo::Rendering::GLState& glState) const;
	};

	class MyRenderableFilter : public Eegeo::Rendering::IRenderableFilter
	{
		Eegeo::Rendering::RenderableBase& m_renderable;
	public:
		MyRenderableFilter(Eegeo::Rendering::RenderableBase& renderable);

		void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
	};

	Eegeo::Rendering::ITexturePageLayout* m_pPinIconsTexturePageLayout;
	Eegeo::Helpers::GLHelpers::TextureInfo m_pinIconsTexture;
	Eegeo::Pins::PinsModule* m_pPinsModule;
	std::string m_pin0UserData;

	Eegeo::Pins::Pin* m_pPin0;
    
	Eegeo::Helpers::IFileIO& m_fileIO;
	Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& m_textureRequestor;
	Eegeo::Lighting::GlobalFogging& m_globalFogging;
	Eegeo::Rendering::RenderableFilters& m_renderableFilters;
    

	Eegeo::Model* m_pModel;
	Eegeo::Rendering::Materials::NullMaterialFactory& m_nullMaterialFactory;
    
    Eegeo::Rendering::Materials::NullMaterial* m_pNullMaterial;
	MyModelRenderable* m_pMyModelRenderable;
	MyRenderableFilter* m_pMyRenderableFilter;

public:
	PinOverModelExample(
	    Eegeo::Helpers::ITextureFileLoader& textureLoader,
	    Eegeo::Rendering::GlBufferPool& glBufferPool,
	    Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
	    Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
	    Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
	    Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
	    Eegeo::Rendering::RenderableFilters& renderableFilters,
	    Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
	    Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
	    Eegeo::Helpers::IFileIO& fileIO,
	    Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
	    Eegeo::Lighting::GlobalFogging& fogging,
	    Eegeo::Rendering::Materials::NullMaterialFactory& nullMaterialFactory,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
        const Eegeo::Rendering::ScreenProperties& initialScreenProperties
	);

	virtual ~PinOverModelExample();

	static std::string GetName()
	{
		return "PinOverModelExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt);
	void Draw();
	void Suspend();
    
    virtual void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
    
    

private:
	void CreateExamplePins();
};
}

#endif /* defined(__ExampleApp__PinOverModelExample__) */
