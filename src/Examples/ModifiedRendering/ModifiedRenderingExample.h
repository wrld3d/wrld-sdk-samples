// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ModifiedRenderingExample__
#define __ExampleApp__ModifiedRenderingExample__

#include "GlobeCameraExampleBase.h"

#include <vector>
#include "RenderContext.h"
#include "ShaderCompiler.h"
#include "GlobalLighting.h"
#include "Location.h"
#include "Rendering.h"
#include "SceneElementRepository.h"
#include "IRenderableFilter.h"
#include "GlState.h"
#include "PackedRenderable.h"
#include "GlHelpers.h"
#include "IMaterial.h"
#include "Mesh.h"
#include "IndexBufferRange.h"

namespace Examples
{
typedef Eegeo::Rendering::Renderables::PackedRenderable TRenderable;
typedef TRenderable* TRenderablePtr;
typedef Eegeo::Rendering::Scene::SceneElement<TRenderable> TSceneElement;
typedef TSceneElement* TSceneElementPtr;
typedef std::vector<TSceneElementPtr> TSceneElementPtrVec;
    
inline void RenderPackedRenderableWithMaterial(Eegeo::Rendering::Renderables::PackedRenderable& renderable,
                                               const Eegeo::Rendering::Materials::IMaterial* pMaterial,
                                               const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                               Eegeo::Rendering::GLState& glState)
{
    pMaterial->SetStatePerRenderable(&renderable, glState);
    
    renderable.GetMesh().BindVertexBuffers(&vertexBinding, glState);
    
    const std::vector<Eegeo::Culling::IndexBufferRange>& visibleRanges = renderable.GetVisibleIndexRanges();
    for(std::vector<Eegeo::Culling::IndexBufferRange>::const_iterator range = visibleRanges.begin(); range != visibleRanges.end(); ++range)
    {
        Eegeo_GL(glDrawElements(GL_TRIANGLES, range->NumOfIndices(), GL_UNSIGNED_SHORT, reinterpret_cast<void*>(range->StartIndex() * 2)));
    }
    
    renderable.GetMesh().UnbindVertexBuffers(glState);
}
    
class MyRenderable : public Eegeo::Rendering::RenderableBase
{
public:
    MyRenderable(TRenderable& originalRenderable, Eegeo::Rendering::Materials::IMaterial* pMaterial, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool)
    : Eegeo::Rendering::RenderableBase(Eegeo::Rendering::LayerIds::Buildings, originalRenderable.GetEcefPosition(), pMaterial)
		, m_originalRenderable(originalRenderable)
        , m_vertexBinding(vertexBindingPool.GetVertexBinding(originalRenderable.GetMesh().GetVertexLayout(), pMaterial->GetShader().GetVertexAttributes()))
	{
	}

	void Update(const Eegeo::Rendering::RenderContext& renderContext)
	{
		m_originalRenderable.CalcUnpackMVP(renderContext, 1.0f);
		m_originalRenderable.SetVisible();
	}
                                       
    void Render(Eegeo::Rendering::GLState& glState) const
    {
        Examples::RenderPackedRenderableWithMaterial(m_originalRenderable, m_material, m_vertexBinding, glState);
    }

private:
	TRenderable& m_originalRenderable;
    const Eegeo::Rendering::VertexLayouts::VertexBinding& m_vertexBinding;
};

typedef Eegeo::Rendering::Scene::ISceneElementObserver<Eegeo::Rendering::Renderables::PackedRenderable> TSceneElementObserver;

class ModifiedRenderingExample : public GlobeCameraExampleBase, TSceneElementObserver, Eegeo::Rendering::IRenderableFilter
{
private:

	struct MyPoolFilterCriteria : Eegeo::Rendering::Scene::ISceneElementFilterCriteria<TRenderable>
	{
		MyPoolFilterCriteria(ModifiedRenderingExample* owner):m_pOwner(owner) {}
		virtual bool FiltersOut(const TSceneElement& item) const;
    private:
        ModifiedRenderingExample* m_pOwner;
	};

	MyPoolFilterCriteria* m_pCriteria;

	Eegeo::Rendering::Scene::SceneElementRepository<Eegeo::Rendering::Renderables::PackedRenderable>& m_buildingRepository;
	Eegeo::Rendering::Filters::PackedRenderableFilter& m_buildingFilter;
	Eegeo::Rendering::RenderableFilters& m_renderableFilters;
	Eegeo::Rendering::Shaders::ShaderIdGenerator& m_shaderIdGenerator;
	Eegeo::Rendering::Materials::MaterialIdGenerator& m_materialIdGenerator;
    Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_vertexBindingPool;
	const Eegeo::Helpers::GLHelpers::TextureInfo& m_placeHolderTexture;

	Eegeo::Lighting::GlobalLighting* m_pAlternativeLighting;
	Eegeo::Rendering::Shaders::PackedDiffuseShader* m_pAlternativeShader;
	Eegeo::Rendering::Materials::PackedDiffuseMaterial* m_pAlternativeMaterial;
	typedef std::map<TSceneElementPtr, MyRenderable*> TSceneElementToRenderablePtrMap;
	TSceneElementToRenderablePtrMap m_alternativeRenderables;

	bool IsToBeReplacedWithAlternative(const TSceneElement* pSceneElement)  const;
    void AddAlternativeRenderable(TSceneElement& sceneElement);
    void PopulateAlternativeRenderablesFromInitialSceneGraph();

public:
	ModifiedRenderingExample(Eegeo::Rendering::Scene::SceneElementRepository<Eegeo::Rendering::Renderables::PackedRenderable>& buildingRepository,
	                         Eegeo::Rendering::Filters::PackedRenderableFilter& buildingFilter,
	                         Eegeo::Rendering::RenderableFilters& renderableFilters,
	                         Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
	                         Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                             Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
	                         const Eegeo::Helpers::GLHelpers::TextureInfo& placeHolderTexture,
	                         Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
	                         Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController
	                        );

	//ISceneElementObserver interface.
	typedef Eegeo::Rendering::Scene::SceneElement<Eegeo::Rendering::Renderables::PackedRenderable> TMySceneElement;
	void OnSceneElementAdded(TMySceneElement& sceneElement);
	void OnSceneElementRemoved(TMySceneElement& sceneElement);

	//IRenderableFilter interface.
	void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);

	static std::string GetName()
	{
		return "ModifiedRenderingExample";
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

#endif /* defined(__ExampleApp__ModifiedRenderingExample__) */
