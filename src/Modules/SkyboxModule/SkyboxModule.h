// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ColorShader.h"
#include "ColorMaterial.h"
#include "Rendering.h"
#include "IRenderableFilter.h"
#include "Modules.h"
#include "MeshRenderable.h"

namespace Eegeo
{
    namespace Skybox
    {
        class SkyboxModule : public Eegeo::Rendering::IRenderableFilter
        {
        private:
            Eegeo::Modules::Core::RenderingModule& m_renderingModule;
            Eegeo::Rendering::Shaders::ColorShader* m_pShader;
            Eegeo::Rendering::Materials::ColorMaterial* m_pMaterial;
            Eegeo::Rendering::GlBufferPool& m_glBufferPool;
            Eegeo::Rendering::VertexLayouts::VertexLayoutPool& m_vertexLayoutPool;
            Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_vertexBindingPool;
            Eegeo::Rendering::Renderables::MeshRenderable* m_pRenderable;
            Eegeo::Rendering::RenderableFilters& m_renderableFilters;
            Eegeo::v4 m_backgroundColor;
            bool m_isShowing;
            
        public:
            SkyboxModule(Eegeo::Modules::Core::RenderingModule& renderingModule,
                         Eegeo::Rendering::GlBufferPool& glBufferPool,
                         Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                         Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
                         Eegeo::Rendering::RenderableFilters& renderableFilters);
            virtual ~SkyboxModule();
            void Start();
            void Stop();
            void Update(float dt);
            void Draw();
            void Suspend();
            void UpdateSkyColor(const Eegeo::v3 color);
            bool IsShowing();
            
            // IRenderableFilter interface
            void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
        };

    }
}


