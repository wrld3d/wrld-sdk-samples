// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__PODAnimationExample__
#define __ExampleApp__PODAnimationExample__

#include "IExample.h"
#include "RenderContext.h"
#include "LatLongAltitude.h"
#include "RenderableBase.h"
#include "IRenderableFilter.h"

#include "Model.h"

namespace Examples
{
    
class PODAnimationExample : public IExample
{
private:
    class MyModelRenderable : public Eegeo::Rendering::RenderableBase
	{
		Eegeo::Model& m_model;
		Eegeo::Lighting::GlobalFogging& m_globalFogging;
        const Eegeo::Camera::RenderCamera& m_renderCamera;
        
	public:
		MyModelRenderable(Eegeo::Model& model,
		                  Eegeo::Lighting::GlobalFogging& globalFogging,
		                  Eegeo::Rendering::Materials::NullMaterial& nullMaterial,
                          const Eegeo::Camera::RenderCamera& renderCamera);
        
		void Render(Eegeo::Rendering::GLState& glState) const;
	};
    
    class MyRenderableFilter : public Eegeo::Rendering::IRenderableFilter
	{
		Eegeo::Rendering::RenderableBase& m_renderable;
	public:
		MyRenderableFilter(Eegeo::Rendering::RenderableBase& renderable);
        
		void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
	};
    
	Eegeo::Helpers::IFileIO& m_fileIO;
	Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& m_textureRequestor;
	Eegeo::Lighting::GlobalFogging& m_globalFogging;
    Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pCameraController;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;
    Eegeo::Rendering::RenderableFilters& m_renderableFilters;
    Eegeo::Rendering::Materials::NullMaterialFactory& m_nullMaterialFactory;
    Eegeo::Rendering::Materials::NullMaterial* m_pNullMaterial;
    
	Eegeo::Model* m_pModel;
    
    MyModelRenderable* m_pMyModelRenderable;
    MyRenderableFilter* m_pMyRenderableFilter;

public:
	PODAnimationExample(Eegeo::Helpers::IFileIO& fileIO,
                        Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
                        Eegeo::Lighting::GlobalFogging& fogging,
                        Eegeo::Rendering::RenderableFilters& renderableFilters,
                        Eegeo::Rendering::Materials::NullMaterialFactory& nullMaterialFactory,
                        Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController);
    
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
    const Eegeo::Camera::RenderCamera& GetRenderCamera() const;
    Eegeo::dv3 GetInterestPoint() const;
};
}


#endif /* defined(__ExampleApp__PODAnimationExample__) */
