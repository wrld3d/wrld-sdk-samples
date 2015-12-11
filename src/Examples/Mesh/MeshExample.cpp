// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MeshExample.h"
#include "ExampleMeshRenderable.h"
#include "ExampleMeshUnlitTexturedMaterial.h"
#include "GeometryHelpers.h"


#include "RenderingModule.h"
#include "ITextureFileLoader.h"
#include "GlobeCameraController.h"
#include "VertexLayoutPool.h"
#include "VertexLayout.h"
#include "VertexLayoutElement.h"
#include "Mesh.h"
#include "LayerIds.h"
#include "TexturedUniformColoredShader.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "Colors.h"

#include "VertexBindingPool.h"
#include "LatLongAltitude.h"
#include "CoordinateConversion.h"
#include "RenderQueue.h"
#include "RenderableFilters.h"
#include "EnvironmentFlatteningService.h"
#include "CameraHelpers.h"
#include "RenderContext.h"
#include "RenderCamera.h"
#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"



#include <algorithm>
#include <cmath>

namespace Examples
{
    namespace
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
        
        inline PositionUvVertex GeometryHelpersVertexToPositionUvVertex(const GeometryHelpers::Vertex& v)
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
        
        Eegeo::Rendering::Mesh* CreateUnlitBoxMesh(float width, float height, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool)
        {
            Eegeo::v3 halfDimensions(width/2, height, width/2);
            std::vector<GeometryHelpers::Vertex> boxVertices;
            std::vector<u16> triangleIndices;
            
            BuildBox(halfDimensions, boxVertices, triangleIndices);
            
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
        
        ExampleMeshRenderable* CreateExampleMeshRenderable(Eegeo::Rendering::Mesh& mesh, Eegeo::Rendering::Materials::IMaterial& material, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool, const Eegeo::dv3 ecefPosition)
        {
            // A VertexBinding provides association between the fields of our vertex struct (in this case PositionUvVertex), and
            // corresponding attributes in our shader (in this case TexturedUniformColoredShader, which expects "Position" and "UV" attributes)
            const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding =
            vertexBindingPool.GetVertexBinding(mesh.GetVertexLayout(), material.GetShader().GetVertexAttributes());
            
            // Create a WorldMeshRenderable, allowing the mesh to be inserted in render queue and drawn.
            const Eegeo::Rendering::LayerIds::Values renderLayer = Eegeo::Rendering::LayerIds::AfterWorld;
            const bool depthTest = true;
            const bool alphaBlend = true;
            const bool translateWithEnvironmentFlattening = true;
            const bool scaleWithEnvironmentFlattening = true;
            
            ExampleMeshRenderable* pUnlitBoxRenderable = new ExampleMeshRenderable(renderLayer,
                                                                                   ecefPosition,
                                                                                   material,
                                                                                   vertexBinding,
                                                                                   mesh,
                                                                                   Eegeo::Rendering::Colors::WHITE,
                                                                                   depthTest,
                                                                                   alphaBlend,
                                                                                   translateWithEnvironmentFlattening,
                                                                                   scaleWithEnvironmentFlattening);
            
            return pUnlitBoxRenderable;
        }
        
        void DeleteRenderable(ExampleMeshRenderable* renderable)
        {
            delete renderable;
        }
        
        Eegeo::m33 BuildBasisToEcef(double originLatitudeDegrees, double originLongitudeDegrees)
        {
            // create an orthogonal basis centred on originLocation, with positive y axis pointing up aligned with the Earth sphere normal
            Eegeo::Space::EcefTangentBasis basisFrame;
            Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
                                                                              Eegeo::Space::LatLong::FromDegrees(originLatitudeDegrees, originLongitudeDegrees).ToECEF(),
                                                                              0.0,
                                                                              basisFrame);
            Eegeo::m33 basisToEcef;
            basisFrame.GetBasisOrientationAsMatrix(basisToEcef);
            
            return basisToEcef;
        }
        
        Eegeo::m33 MakeEcefOrientation(float rotationRadiansYAxis, const Eegeo::m33& basisToEcef)
        {
            Eegeo::m33 localOrientation;
            localOrientation.RotateY(rotationRadiansYAxis);
            
            Eegeo::m33 ecefOrientation;
            Eegeo::m33::Mul(ecefOrientation, basisToEcef, localOrientation);
            return ecefOrientation;
        }
        
        float CalcFlatteningParam(float phase)
        {
            const float threshold = 0.8f;
            float clippedSine = 1.0f - ((std::max(std::sin(phase), threshold) - threshold) / (1.f - threshold));
            const float minFlatteningScale = 0.2f;
            float flatteningParam = Eegeo::Math::Lerp(minFlatteningScale, 1.f, clippedSine);
            return flatteningParam;
        }
        
        const float revsPerMinuteToRadiansPerSecond = Eegeo::Math::kPI*2.f/60.f;
        
    }
    

    MeshExample::MeshExample(Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                                       Eegeo::Modules::Core::RenderingModule& renderingModule,
                                       Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                                       Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                       Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                       const MeshExampleConfig& config)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_renderingModule(renderingModule)
    , m_textureFileLoader(textureFileLoader)
    , m_environmentFlatteningService(environmentFlatteningService)
    , m_webRequestFactory(webRequestFactory)
    , m_config(config)
    , m_webLoadCallback(this, &MeshExample::OnWebLoadCompleted)
    , m_pPositionUvVertexLayout(NULL)
    , m_pShader(NULL)
    , m_pMaterial(NULL)
    , m_pAsyncTextureMaterial(NULL)
    , m_pUnlitBoxMesh(NULL)
    , m_basisToEcef(BuildBasisToEcef(config.originLatLong.first, config.originLatLong.second))
    , m_phaseA(0.f)
    , m_phaseB(0.f)
    , m_environmentFlatteningPhase(0.f)
    , m_timer(0.f)
    , m_madeTextureRequest(false)
    {
        const int minDimension = 3;
        const int maxDimension = 10;
        
        Eegeo_ASSERT(m_config.meshRows >= minDimension && m_config.meshRows <= maxDimension);
        Eegeo_ASSERT(m_config.meshColumns >= minDimension && m_config.meshColumns <= maxDimension);
        
        m_textureInfo.textureId = 0;
        m_textureInfo.width = 0;
        m_textureInfo.height = 0;
        m_asyncTextureInfo.textureId = 0;
        m_asyncTextureInfo.width = 0;
        m_asyncTextureInfo.height = 0;
        
        m_pPositionUvVertexLayout = CreatePositionUvVertexLayout();
        
        Eegeo::Rendering::RenderableFilters& platformRenderableFilters = m_renderingModule.GetRenderableFilters();
        
        platformRenderableFilters.AddRenderableFilter(*this);
    }
    
    MeshExample::~MeshExample()
    {
        Eegeo::Rendering::RenderableFilters& platformRenderableFilters = m_renderingModule.GetRenderableFilters();
        
        platformRenderableFilters.RemoveRenderableFilter(*this);
        
        delete m_pPositionUvVertexLayout;
        delete m_pMaterial;
        delete m_pAsyncTextureMaterial;
        delete m_pShader;
        delete m_pUnlitBoxMesh;
        
        std::for_each(m_renderables.begin(), m_renderables.end(), DeleteRenderable);
        m_renderables.clear();
        
        if (m_textureInfo.textureId != 0)
        {
            Eegeo_GL(glDeleteTextures(1, &m_textureInfo.textureId));
        }

        if (m_asyncTextureInfo.textureId != 0)
        {
            Eegeo_GL(glDeleteTextures(1, &m_asyncTextureInfo.textureId));
        }
    }
    
    void MeshExample::Start()
    {
        const bool generateMipmaps = true;
        bool success = m_textureFileLoader.LoadTexture(m_textureInfo, m_config.textureFilename, generateMipmaps);
        Eegeo_ASSERT(success, "failed to load texture");
        if (!success)
            return;
        
        
        m_pShader = Eegeo::Rendering::Shaders::TexturedUniformColoredShader::Create(m_renderingModule.GetShaderIdGenerator().GetNextId());
        

        m_pMaterial = new (ExampleMeshUnlitTexturedMaterial)(
                                                             m_renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                             "MeshExampleMat",
                                                             *m_pShader,
                                                             m_textureInfo.textureId
                                                             );
        
        m_pUnlitBoxMesh = CreateUnlitBoxMesh(m_config.boxWidth, m_config.boxHeight, *m_pPositionUvVertexLayout, m_renderingModule.GetGlBufferPool());

        
        const int westToEastRows = m_config.meshRows;
        const int southToNorthColumns = m_config.meshColumns;
        m_renderables.reserve(westToEastRows*southToNorthColumns);
        
        Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool = m_renderingModule.GetVertexBindingPool();
        
        for (int i = 0; i < westToEastRows; ++i)
        {
            for (int j = 0; j < southToNorthColumns; ++j)
            {
                const Eegeo::Space::LatLongAltitude& lla = Eegeo::Space::LatLongAltitude::FromDegrees(
                                                                                                      m_config.originLatLong.first + i*m_config.spacing,
                                                                                                      m_config.originLatLong.second + j*m_config.spacing,
                                                                                                      m_config.altitude);
                const Eegeo::dv3& positionEcef = Eegeo::Space::ConvertLatLongAltitudeToEcef(lla);
                ExampleMeshRenderable* pRenderable = CreateExampleMeshRenderable(*m_pUnlitBoxMesh, *m_pMaterial, vertexBindingPool, positionEcef);
                
                pRenderable->SetOrientationEcef(m_basisToEcef);
            
                m_renderables.push_back(pRenderable);
            }
        }
        
        ExampleMeshRenderable& middleRenderable = *m_renderables[(southToNorthColumns/2)*westToEastRows + westToEastRows/2];
        middleRenderable.SetAlphaBlend(false);
        middleRenderable.SetEnvironmentFlattenScale(false);
        
        ExampleMeshRenderable& northWestRenderable = *m_renderables[(westToEastRows - 1)*southToNorthColumns];
        northWestRenderable.SetDepthTest(false);
        
        ExampleMeshRenderable& southEastRenderable = *m_renderables[southToNorthColumns - 1];
        southEastRenderable.SetColor(Eegeo::Rendering::Colors::MAGENTA);
        southEastRenderable.SetEnvironmentFlattenTranslate(false);
    }
    
    void MeshExample::Update(float dt)
    {
        m_environmentFlatteningPhase += dt*revsPerMinuteToRadiansPerSecond*m_config.environmentFlatteningCyclesPerMinute;
        m_environmentFlatteningPhase = std::fmod(m_environmentFlatteningPhase, Eegeo::Math::kPI*2);
        
        m_phaseA += dt*revsPerMinuteToRadiansPerSecond*m_config.revsPerMinuteA;
        m_phaseA = std::fmod(m_phaseA, Eegeo::Math::kPI*2);
        
        m_phaseB += dt*revsPerMinuteToRadiansPerSecond*m_config.revsPerMinuteB;
        m_phaseB = std::fmod(m_phaseB, Eegeo::Math::kPI*2);
        
        float flatteningParam = CalcFlatteningParam(m_environmentFlatteningPhase);
        m_environmentFlatteningService.SetCurrentScale(flatteningParam);

        ExampleMeshRenderable& southWestRenderable = *m_renderables.front();
        southWestRenderable.SetOrientationEcef(MakeEcefOrientation(m_phaseA, m_basisToEcef));
        
        ExampleMeshRenderable& northEastRenderable = *m_renderables.back();
        northEastRenderable.SetOrientationEcef(MakeEcefOrientation(m_phaseB, m_basisToEcef));
        
        if (!m_madeTextureRequest)
        {
            m_timer += dt;
            if (m_timer > m_config.secondsDelayBeforeTextureWebRequest)
            {
                Eegeo::Web::IWebLoadRequest* webLoadRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, m_config.asyncTextureUrl, m_webLoadCallback).Build();
                webLoadRequest->Load();
                m_madeTextureRequest = true;
            }
        }
    }
    
    
    void MeshExample::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
    {
        const float environmentFlatteningScale = m_environmentFlatteningService.GetCurrentScale();
        const Eegeo::Camera::RenderCamera& renderCamera = renderContext.GetRenderCamera();
        
        const Eegeo::m44& viewProjection = renderCamera.GetViewProjectionMatrix();
        const Eegeo::dv3& ecefCameraPosition = renderCamera.GetEcefLocation();
        
        for (ExampleMeshRenderableVector::const_iterator iter = m_renderables.begin(); iter != m_renderables.end(); ++iter)
        {
            ExampleMeshRenderable& renderable = **iter;
            
            const Eegeo::m44& mvp = renderable.CalcModelViewProjection(ecefCameraPosition, viewProjection, environmentFlatteningScale);
            renderable.SetModelViewProjection(mvp);
            
            renderQueue.EnqueueRenderable(renderable);
        }
    }
    
    void MeshExample::OnWebLoadCompleted(Eegeo::Web::IWebResponse& webResponse)
    {
        if (!webResponse.IsSucceeded())
        {
            Eegeo_TTY("Failed to fetch texture %s", webResponse.GetUrl().c_str());
            return;
        }
        
        const bool generateMipmaps = true;
        std::string filenameExtension = webResponse.GetUrl().substr(webResponse.GetUrl().find_last_of("."));
        
        bool success = m_textureFileLoader.LoadFromBuffer(m_asyncTextureInfo, filenameExtension, webResponse.GetBodyData().data(), webResponse.GetBodyData().size(), generateMipmaps);
        if (!success)
        {
            Eegeo_TTY("Failed to load texture %s", webResponse.GetUrl().c_str());
            return;
        }
    
        Eegeo_ASSERT(m_pAsyncTextureMaterial == NULL);
        m_pAsyncTextureMaterial = new (ExampleMeshUnlitTexturedMaterial)(
                                                             m_renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                             "MeshExampleAsyncMat",
                                                             *m_pShader,
                                                             m_asyncTextureInfo.textureId
                                                             );
        
        ExampleMeshRenderable& southWestRenderable = *m_renderables.front();
        southWestRenderable.SetMaterial(m_pAsyncTextureMaterial, m_renderingModule.GetVertexBindingPool());

    }

}
