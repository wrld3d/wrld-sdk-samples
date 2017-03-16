// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "GlobeCameraExampleBase.h"
#include "Modules.h"
#include "Rendering.h"
#include "ITextureFileLoader.h"
#include "GLHelpers.h"
#include "IRenderableFilter.h"
#include "Bounds.h"

#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"

namespace Examples
{
    class BillboardedSpriteExample : public GlobeCameraExampleBase, public Eegeo::Rendering::IRenderableFilter
    {
    private:
        Eegeo::Modules::Core::RenderingModule& m_renderingModule;
        Eegeo::Helpers::ITextureFileLoader& m_textureFileLoader;
        
        Eegeo::Rendering::Renderables::BatchedSpriteRenderable* m_pBatchedSpriteRenderable;
        Eegeo::Rendering::Shaders::BatchedSpriteShader* m_pBatchedSpriteShader;
        Eegeo::Rendering::Materials::BatchedSpriteMaterial* m_pBatchedSpriteMaterial;
        Eegeo::Rendering::Materials::BatchedSpriteMaterial* m_pAsyncBatchedSpriteMaterial;
        
        Eegeo::Helpers::GLHelpers::TextureInfo m_textureInfo;
        Eegeo::Helpers::GLHelpers::TextureInfo m_asyncTextureInfo;
    
        Eegeo::dv3 m_spriteEcefPosition;
        Eegeo::v2 m_spriteDimensions;
        Eegeo::Geometry::Bounds2D m_spriteUvBounds;
        Eegeo::v4 m_spriteColor;
        
        bool m_hasMadeWebRequest;
        float m_webRequestDelayTimer;
        Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
        Eegeo::Web::TWebLoadRequestCompletionCallback<BillboardedSpriteExample> m_webLoadCallback;
        
        void OnWebLoadCompleted(Eegeo::Web::IWebResponse& webResponse);
        
    public:
        BillboardedSpriteExample(Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                             Eegeo::Modules::Core::RenderingModule& renderingModule,
                             Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                             Eegeo::Web::IWebLoadRequestFactory& webRequestFactory);
        
        ~BillboardedSpriteExample();

        static std::string GetName()
        {
            return "BillboardedSpriteExample";
        }
        std::string Name() const
        {
            return GetName();
        }

        void Start();
        void Update(float dt);
        void Draw() {}
        void Suspend() {}
        
        void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
    };
}


