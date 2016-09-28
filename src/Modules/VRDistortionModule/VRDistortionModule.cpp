// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include <vector>
#include "Mesh.h"
#include "Quad.h"
#include "GlBufferPool.h"
#include "VertexLayout.h"
#include "VRDistortionModule.h"
#include "RenderContext.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "RenderableFilters.h"
#include "VertexBindingPool.h"
#include "ScreenProperties.h"
#include "LayerIds.h"
#include "VRDistortionMeshHelper.h"
#include "VRDistortionShader.h"
#include "VRDistortionMaterial.h"
#include "VRDistortionRenderable.h"
#include "VRDistortionRenderer.h"
#include "VRCardboardDeviceProfile.h"

#include "Logger.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            struct PositionUvVertex
            {
                float x;
                float y;
                float z;
                float u;
                float v;
            };
            
            inline PositionUvVertex MakePositionUvVertex(const Eegeo::v3& pos, const Eegeo::v2& uv)
            {
                PositionUvVertex v;
                v.x = pos.x;
                v.y = pos.y;
                v.z = pos.z;
                v.u = uv.x;
                v.v = uv.y;
                return v;
            }
            
            inline PositionUvVertex GeometryHelpersVertexToPositionUvVertex(const Eegeo::VR::Distortion::Vertex& v)
            {
                return MakePositionUvVertex(v.position, v.uv);
            }
            
            Eegeo::Rendering::VertexLayouts::VertexLayout* CreatePositionUvVertexLayout()
            {
                using namespace Eegeo::Rendering::VertexLayouts;
                VertexLayout* pLayout = new (VertexLayout)(sizeof(PositionUvVertex));
                
                int positionOffset = offsetof(PositionUvVertex, x);
                pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::Position, 3, GL_FLOAT,  positionOffset));
                
                int uvOffset = offsetof(PositionUvVertex, u);
                pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::UV, 2, GL_FLOAT, uvOffset));
                
                return pLayout;
            }
            
            
            VRDistortionModule::VRDistortionModule(
                                        			const Eegeo::Rendering::ScreenProperties& screenProperties,
													Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
													Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
													Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
													Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
													Eegeo::Rendering::RenderableFilters& renderableFilters,
													Eegeo::Rendering::GlBufferPool& glBufferPool,
													Eegeo::VR::Distortion::IVRCardboardDeviceProfileFactory& vrCardboardDeviceProfileFactory)
            : m_screenProperties(screenProperties)
            , m_vertexLayoutPool(vertexLayoutPool)
            , m_vertexBindingPool(vertexBindingPool)
            , m_shaderIdGenerator(shaderIdGenerator)
            , m_materialIdGenerator(materialIdGenerator)
            , m_renderableFilters(renderableFilters)
            , m_glBufferPool(glBufferPool)
            , m_pVRDistortionShader(NULL)
            , m_pVRDistortionMaterial(NULL)
            , m_pRenderable(NULL)
            , m_pVRDistortionRenderer(NULL)
            , m_pRenderTexture(NULL)
            , m_meshUpdateRequried(false)
            , m_visibilityParamChangedCallback(this, &VRDistortionModule::UpdateMaterialFadeMultiplier)
            {
                m_pCardboardProfile = vrCardboardDeviceProfileFactory.GetCardboardDeviceProfile();
                m_pPositionUvVertexLayout = CreatePositionUvVertexLayout();

                m_pTransitionModel = Eegeo_NEW(VRDistortionTransitionModel)();
            }

            VRDistortionModule::~VRDistortionModule()
            {
                Eegeo_DELETE m_pTransitionModel;

                Eegeo_DELETE m_pCardboardProfile;
                Eegeo_DELETE m_pPositionUvVertexLayout;
            }

            Eegeo::Rendering::Mesh* CreateUnlitDistortionMesh(float width, float height, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool, VRCardboardDeviceProfile& cardboardProfile)
            {
                std::vector<Eegeo::VR::Distortion::Vertex> boxVertices;
                std::vector<u16> triangleIndices;
                

                BuildDistortionMesh(boxVertices, triangleIndices, width, height, cardboardProfile);
                
                std::vector<PositionUvVertex> unlitVertices;
                
                std::transform(boxVertices.begin(), boxVertices.end(), std::back_inserter(unlitVertices), GeometryHelpersVertexToPositionUvVertex);
                
                size_t vertexBufferSizeBytes = sizeof(PositionUvVertex) * unlitVertices.size();
                size_t indexBufferSizeBytes = sizeof(u16) * triangleIndices.size();
                
                return new (Eegeo::Rendering::Mesh)(
                                                    vertexLayout,
                                                    glBufferPool,
                                                    unlitVertices.data(),
                                                    vertexBufferSizeBytes,
                                                    triangleIndices.data(),
                                                    indexBufferSizeBytes,
                                                    static_cast<u32>(triangleIndices.size()),
                                                    "UnlitBoxMesh"
                                                    );
            }
            
            void VRDistortionModule::Initialize()
            {
                
                m_pRenderTexture = Eegeo_NEW(Eegeo::Rendering::RenderTexture)(static_cast<u32>(m_screenProperties.GetScreenWidth()),
                                                                              static_cast<u32>(m_screenProperties.GetScreenHeight()),
                                                                              true);
                
                m_pVRDistortionShader = VRDistortionShader::Create(m_shaderIdGenerator.GetNextId());

                m_pVRDistortionMaterial = Eegeo_NEW(VRDistortionMaterial)(m_materialIdGenerator.GetNextId(),
                                                                             "VRDistortionMaterial",
                                                                             *m_pVRDistortionShader,
                                                                             *m_pRenderTexture,
                                                                             m_screenProperties);
                
                Eegeo::Rendering::Mesh* pRenderableMesh = CreateUnlitDistortionMesh(m_screenProperties.GetScreenWidth(), m_screenProperties.GetScreenHeight(), *m_pPositionUvVertexLayout, m_glBufferPool, *m_pCardboardProfile);
                
                const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout = pRenderableMesh->GetVertexLayout();
                const Eegeo::Rendering::VertexLayouts::VertexAttribs& vertexAttributes = m_pVRDistortionShader->GetVertexAttributes();
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = m_vertexBindingPool.GetVertexBinding(vertexLayout, vertexAttributes);
                
                m_pRenderable = Eegeo_NEW(VRDistortionRenderable)(Eegeo::Rendering::LayerIds::AfterAll,
                                                                         m_pVRDistortionMaterial,
                                                                         vertexBinding,
                                                                         pRenderableMesh);
                
                m_pVRDistortionRenderer = Eegeo_NEW(VRDistortionRenderer)(*m_pRenderable);
                m_pRenderable->SetFadeModifier(m_pTransitionModel->GetVisibilityParam());
                m_pTransitionModel->RegisterVisibilityChangedCallback(m_visibilityParamChangedCallback);
            }
            
            void VRDistortionModule::Suspend()
            {
                m_pTransitionModel->UnregisterVisibilityChangedCallback(m_visibilityParamChangedCallback);

                Eegeo_DELETE m_pVRDistortionRenderer;
                m_pVRDistortionRenderer = NULL;
                
                Eegeo_DELETE m_pRenderable;
                m_pRenderable = NULL;
                
                Eegeo_DELETE m_pVRDistortionMaterial;
                m_pVRDistortionMaterial = NULL;
                
                Eegeo_DELETE m_pVRDistortionShader;
                m_pVRDistortionShader = NULL;
                
                Eegeo_DELETE m_pRenderTexture;
                m_pRenderTexture = NULL;
            }
            
            
            void VRDistortionModule::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
            {
                if (m_screenProperties.GetScreenWidth() != screenProperties.GetScreenWidth() ||
                    m_screenProperties.GetScreenHeight() != screenProperties.GetScreenHeight())
                {
                    m_screenProperties = screenProperties;
                    
                    Suspend();
                    Initialize();
                }
            }
            
            void VRDistortionModule::UpdateCardboardProfile(const float cardboardProfile[])
            {
                m_pCardboardProfile->SetupProfile(cardboardProfile);
                m_meshUpdateRequried = true;
            }
            
            void VRDistortionModule::BeginRendering()
            {
                if(m_meshUpdateRequried)
                {
                    Suspend();
                    Initialize();
                    m_meshUpdateRequried = false;
                }
                
                m_pVRDistortionMaterial->SetIsRenderingEnded(false);
                m_pRenderTexture->BeginRendering();
            }
            
            void VRDistortionModule::RegisterRenderable()
            {
                m_renderableFilters.AddRenderableFilter(*m_pVRDistortionRenderer);
                
            }
            
            void VRDistortionModule::UnRegisterRenderable()
            {
                m_renderableFilters.RemoveRenderableFilter(*m_pVRDistortionRenderer);
                if(!m_pVRDistortionMaterial->IsRenderingEnded())
                {
                    m_pRenderTexture->EndRendering();
                }
            }

            VRDistortionTransitionModel& VRDistortionModule::GetTransionModel() const
            {
                return *m_pTransitionModel;
            }

            void VRDistortionModule::UpdateMaterialFadeMultiplier()
            {
                m_pRenderable->SetFadeModifier(m_pTransitionModel->GetVisibilityParam());
            }
            
        }
    }
}

