// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ExampleMeshUnlitTexturedMaterial.h"
#include "TexturedUniformColoredShader.h"
#include "TextureMinifyType.h"
#include "GLHelpers.h"
#include "RenderableBase.h"
#include "ExampleMeshRenderable.h"

namespace Examples
{
    ExampleMeshUnlitTexturedMaterial::ExampleMeshUnlitTexturedMaterial(
                                                                       const Eegeo::Rendering::TMaterialId materialId,
                                                                       const std::string& debugName,
                                                                       Eegeo::Rendering::Shaders::TexturedUniformColoredShader& shader,
                                                                       Eegeo::Rendering::TTextureId textureId)
    : m_id(materialId)
    , m_debugName(debugName)
    , m_shader(shader)
    , m_textureId(textureId)
    {
        
    }
    
    const Eegeo::Rendering::Shader& ExampleMeshUnlitTexturedMaterial::GetShader() const
    {
        return m_shader;
    }
    
    void ExampleMeshUnlitTexturedMaterial::SetState(Eegeo::Rendering::GLState& glState) const
    {
        m_shader.Use(glState);

        glState.DepthFunc(GL_LEQUAL);
        glState.CullFace.Enable();
        glState.FrontFace(GL_CW);
        glState.CullFaceMode(GL_BACK);
        glState.StencilTest.Disable();

        glState.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glState.BlendEquation(GL_FUNC_ADD);
        glState.ColorMask(true, true, true, true);

        
        bool repeatTexture = false;
        Eegeo::Rendering::TextureMinifyType textureMinifyType = Eegeo::Rendering::TextureMinify_LinearMipmap_Linear;
        Eegeo::Helpers::GLHelpers::BindTexture2D(glState, m_shader.GetDiffuseSamplerId(), m_textureId, textureMinifyType, repeatTexture);
    }
    
    void ExampleMeshUnlitTexturedMaterial::SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const
    {
        const ExampleMeshRenderable& exampleMeshRenderable = *static_cast<const ExampleMeshRenderable*>(renderableBase);
        m_shader.SetMVP(exampleMeshRenderable.GetModelViewProjection());
        
        if (exampleMeshRenderable.IsDepthTest())
        {
            glState.DepthTest.Enable();
        }
        else
        {
            glState.DepthTest.Disable();
        }
        
        if (exampleMeshRenderable.IsAlphaBlend())
        {
            glState.Blend.Enable();
            glState.DepthMask(GL_FALSE);
        }
        else
        {
            glState.Blend.Disable();
            glState.DepthMask(GL_TRUE);
        }
        
        m_shader.SetColor(exampleMeshRenderable.GetColor());
    }

}