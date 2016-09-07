// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Rendering.h"
#include "RenderTexture.h"
#include "ScreenProperties.h"
#include "ICallback.h"
#include "VRDistortionIncludes.h"
#include "VRDistortionTransitionModel.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            class VRDistortionModule : public Eegeo::NonCopyable
            {
                
            private:
                Eegeo::Rendering::VertexLayouts::VertexLayoutPool& m_vertexLayoutPool;
                Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_vertexBindingPool;
                Eegeo::Rendering::Shaders::ShaderIdGenerator& m_shaderIdGenerator;
                Eegeo::Rendering::Materials::MaterialIdGenerator& m_materialIdGenerator;
                Eegeo::Rendering::RenderableFilters& m_renderableFilters;
                Eegeo::Rendering::GlBufferPool& m_glBufferPool;
                
                VRDistortionShader* m_pVRDistortionShader;
                VRDistortionMaterial* m_pVRDistortionMaterial;
                VRDistortionRenderable* m_pRenderable;
                VRDistortionRenderer* m_pVRDistortionRenderer;
                
                Eegeo::Rendering::RenderTexture* m_pRenderTexture;
                Eegeo::Rendering::VertexLayouts::VertexLayout* m_pPositionUvVertexLayout;
                Eegeo::Rendering::ScreenProperties m_screenProperties;
                
                VRCardboardDeviceProfile* m_pCardboardProfile;
                bool m_meshUpdateRequried;

                VRDistortionTransitionModel* m_pTransitionModel;
                Eegeo::Helpers::TCallback0<VRDistortionModule> m_visibilityParamChangedCallback;
                
                void HandleScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
                void UpdateMaterialFadeMultiplier();

            public:
                
                VRDistortionModule(const Eegeo::Rendering::ScreenProperties& screenProperties,
                                       Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
                                       Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                                       Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
                                       Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                                       Eegeo::Rendering::RenderableFilters& renderableFilters,
                                       Eegeo::Rendering::GlBufferPool& glBufferPool);
                virtual ~VRDistortionModule();
                void Initialize();
                void Suspend();
                
                void UpdateCardboardProfile(float cardboardProfile[]);
                VRCardboardDeviceProfile& GetCardboardProfile() { return *m_pCardboardProfile; }
                
                void BeginRendering();
                void RegisterRenderable();
                void UnRegisterRenderable();

                VRDistortionTransitionModel& GetTransionModel() const;
                
                void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
            };
        }
    }
}


