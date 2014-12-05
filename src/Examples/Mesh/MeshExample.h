// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IExample.h"
#include "IRenderableFilter.h"
#include "MeshExampleConfig.h"
#include "RenderTexture.h"
#include "Rendering.h"
#include "RenderToTextureExampleIncludes.h"
#include "Modules.h"
#include "Helpers.h"
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"


#include <vector>

namespace Examples
{
    class ExampleMeshRenderable;
    class ExampleMeshUnlitTexturedMaterial;
    

    
    class MeshExample : public IExample, Eegeo::Rendering::IRenderableFilter
    {
    public:
        typedef std::vector<ExampleMeshRenderable*> ExampleMeshRenderableVector;
        
        MeshExample(Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
                         Eegeo::Modules::Core::RenderingModule& renderingModule,
                         Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                         Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                         Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                         const MeshExampleConfig& config);
        
        virtual ~MeshExample();
        
        static std::string GetName()
        {
            return "MeshExample";
        }
        
        std::string Name() const
        {
            return GetName();
        }
        
        void Start();
        void Update(float dt);

        void Draw() {}
        void Suspend() {}
        const Eegeo::Camera::RenderCamera& GetRenderCamera() const;
        
        // IRenderableFilter interface
        void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
        
    private:
        void OnWebLoadCompleted(Eegeo::Web::IWebLoadRequest& webLoadRequest);
    
        Eegeo::Camera::GlobeCamera::GlobeCameraController& m_cameraController;
        Eegeo::Modules::Core::RenderingModule& m_renderingModule;
        Eegeo::Helpers::ITextureFileLoader& m_textureFileLoader;
        Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
        Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
        MeshExampleConfig m_config;
        
        Eegeo::Web::TWebLoadRequestCompletionCallback<MeshExample> m_webLoadCallback;
        
        GlobeCameraStateRestorer m_globeCameraStateRestorer;
        
        Eegeo::Helpers::GLHelpers::TextureInfo m_textureInfo;
        Eegeo::Helpers::GLHelpers::TextureInfo m_asyncTextureInfo;
        
        Eegeo::Rendering::VertexLayouts::VertexLayout* m_pPositionUvVertexLayout;
        Eegeo::Rendering::Shaders::TexturedUniformColoredShader* m_pShader;
        ExampleMeshUnlitTexturedMaterial* m_pMaterial;
        ExampleMeshUnlitTexturedMaterial* m_pAsyncTextureMaterial;
        Eegeo::Rendering::Mesh* m_pUnlitBoxMesh;
        ExampleMeshRenderableVector m_renderables;
        Eegeo::m33 m_basisToEcef;
        
        float m_phaseA;
        float m_phaseB;
        float m_environmentFlatteningPhase;
        float m_timer;
        bool m_madeTextureRequest;
    };
}
