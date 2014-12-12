// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RenderToTextureExample__
#define __ExampleApp__RenderToTextureExample__

#include "GlobeCameraExampleBase.h"
#include "RenderTexture.h"
#include "Rendering.h"
#include "RenderToTextureExampleIncludes.h"
#include "ScreenProperties.h"

namespace Examples
{
    class RenderToTextureExample : public GlobeCameraExampleBase
    {
    private:
        Eegeo::Rendering::VertexLayouts::VertexLayoutPool& m_vertexLayoutPool;
        Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_vertexBindingPool;
        Eegeo::Rendering::Shaders::ShaderIdGenerator& m_shaderIdGenerator;
        Eegeo::Rendering::Materials::MaterialIdGenerator& m_materialIdGenerator;
        Eegeo::Rendering::RenderableFilters& m_renderableFilters;
        Eegeo::Rendering::GlBufferPool& m_glBufferPool;
        
        PostProcessVignetteShader* m_pVignetteShader;
        PostProcessVignetteMaterial* m_pVignetteMaterial;
        PostProcessVignetteRenderable* m_pRenderable;
        PostProcessVignetteRenderer* m_pVignetteRenderer;
        Eegeo::Rendering::RenderTexture* m_pRenderTexture;
        
        
        
        static const float SecondsBetweenEffectUpdates;
        float m_secondsSinceLastEffectUpate;

        Eegeo::Rendering::ScreenProperties m_screenProperties;
        
        void UpdateEffect();
        
        void HandleScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
        
    public:
        RenderToTextureExample(Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                               Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                               const Eegeo::Rendering::ScreenProperties& screenProperties,
                               Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
                               Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                               Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
                               Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                               Eegeo::Rendering::RenderableFilters& renderableFilters,
                               Eegeo::Rendering::GlBufferPool& m_glBufferPool);
        
        static std::string GetName()
        {
            return "RenderToTextureExample";
        }
        
        std::string Name() const
        {
            return GetName();
        }
        
        void Start();
        void EarlyUpdate(float dt);
        void Update(float dt);
        void PreWorldDraw();
        void Draw() {}
        void Suspend();
        
        void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
    };
}

#endif /* defined(__ExampleApp__RenderToTextureExample__) */
