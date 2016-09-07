// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SkyboxModule.h"
#include "RenderingModule.h"
#include "RenderableFilters.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "Colors.h"
#include "LayerIds.h"
#include "Mesh.h"
#include "Quad.h"
#include "VertexBindingPool.h"
#include "RenderContext.h"
#include "RenderQueue.h"



namespace Eegeo
{
    namespace Skybox
    {
        SkyboxModule::SkyboxModule(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                   Eegeo::Rendering::GlBufferPool& glBufferPool,
                                   Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                                   Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
                                   Eegeo::Rendering::RenderableFilters& renderableFilters):
        m_renderingModule(renderingModule),
        m_glBufferPool(glBufferPool),
        m_vertexLayoutPool(vertexLayoutPool),
        m_vertexBindingPool(vertexBindingPool),
        m_renderableFilters(renderableFilters),
        m_pRenderable(NULL),
		m_pShader(NULL),
		m_pMaterial(NULL),
		m_isShowing(false)
        {
            m_backgroundColor = Eegeo::v4(0.0f/255.f,24.0f/255.f,72.0f/255.f,1.0f);
        }
        
        SkyboxModule::~SkyboxModule()
        {
        	if(m_isShowing)
        		Stop();
            Eegeo_DELETE m_pMaterial;
            Eegeo_DELETE m_pShader;
            Eegeo_DELETE m_pRenderable;
        }
        
        void SkyboxModule::Start()
        {
        	if(m_pRenderable == NULL)
        	{
				m_pShader = Eegeo::Rendering::Shaders::ColorShader::Create(m_renderingModule.GetShaderIdGenerator().GetNextId());
				m_pMaterial = new (Eegeo::Rendering::Materials::ColorMaterial) (
																			   m_renderingModule.GetMaterialIdGenerator().GetNextId(),
																			   "SkyboxMat",
																			   *m_pShader,
																			   m_backgroundColor
																			   );

				Eegeo::Rendering::Mesh* pRenderableMesh = Eegeo::Rendering::Geometry::CreatePositionQuad(1.0f, m_glBufferPool, m_vertexLayoutPool);
				const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout = pRenderableMesh->GetVertexLayout();
				const Eegeo::Rendering::VertexLayouts::VertexAttribs& vertexAttributes = m_pShader->GetVertexAttributes();
				const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = m_vertexBindingPool.GetVertexBinding(vertexLayout, vertexAttributes);

				m_pRenderable = Eegeo_NEW(Eegeo::Rendering::Renderables::MeshRenderable)(Eegeo::Rendering::LayerIds::BeforeWorldTranslucency,
																						 Eegeo::dv3(),
																						 m_pMaterial,
																						 pRenderableMesh,
																						 vertexBinding
																						 );
        	}
            m_renderableFilters.AddRenderableFilter(*this);
            m_isShowing = true;
        }
        
        void SkyboxModule::Stop()
        {
        	m_renderableFilters.RemoveRenderableFilter(*this);
        	m_isShowing = false;
        }

        void SkyboxModule::UpdateSkyColor(const Eegeo::v3 color)
        {
            m_backgroundColor.Set(color.GetX(), color.GetY(), color.GetZ(), 1.0f);
            m_pMaterial->SetColor(m_backgroundColor);
        }
        
        void SkyboxModule::Update(float dt){}
        
        void SkyboxModule::Draw()
        {}
        
        void SkyboxModule::Suspend()
        {

        }
        
        // IRenderableFilter interface
        void SkyboxModule::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
        {
            renderQueue.EnqueueRenderable(m_pRenderable);
        }

        bool SkyboxModule::IsShowing()
        {
        	return m_isShowing;
        }
    }
}
