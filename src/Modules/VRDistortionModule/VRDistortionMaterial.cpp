// Copyright eeGeo Ltd (2012-2016), All Rights Reserved


#include "VRDistortionMaterial.h"
#include "GLHelpers.h"
#include "Rendering.h"
#include "VectorMath.h"
#include "VRDistortionShader.h"
#include "VRDistortionRenderable.h"

#include "Logger.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            
            VRDistortionMaterial::VRDistortionMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                                       const std::string& name,
                                                       VRDistortionShader& shader,
                                                       Eegeo::Rendering::RenderTexture& renderTexture,
                                                       Eegeo::Rendering::ScreenProperties& screenProperties)
            : m_id(materialId)
            , m_name(name)
            , m_shader(shader)
            , m_renderTexture(renderTexture)
            , m_screenProperties(screenProperties)
            , m_isRenderingEnded(false)
            {  
            }
            
            const Eegeo::Rendering::Shader& VRDistortionMaterial::GetShader() const
            {
                return m_shader;
            }
            
            void VRDistortionMaterial::SetState(Eegeo::Rendering::GLState& glState) const
            {
                m_isRenderingEnded = true;
                
                glViewport(0, 0, m_screenProperties.GetScreenWidth(), m_screenProperties.GetScreenHeight());
                
                m_shader.Use(glState);
                m_renderTexture.EndRendering();
                
                const bool repeat = false;
                Eegeo::Helpers::GLHelpers::BindTexture2D(glState,
                                                         m_shader.GetDiffuseSamplerId(),
                                                         m_renderTexture.TextureId(),
                                                         Eegeo::Rendering::TextureMinify_Nearest,
                                                         repeat);
            }
            
            void VRDistortionMaterial::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
            {
                m_screenProperties = screenProperties;
            }
            
            void VRDistortionMaterial::SetStatePerRenderable(const Rendering::RenderableBase* pRenderableBase, Rendering::GLState& glState) const
            {
                const VRDistortionRenderable* pRenderable = static_cast<const VRDistortionRenderable*>(pRenderableBase);

                m_shader.SetFadeMultiplier(pRenderable->GetFadeModifier());
            }
        }
    }
}
