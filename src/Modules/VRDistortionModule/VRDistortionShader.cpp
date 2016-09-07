// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "VRDistortionShader.h"
#include "ShaderCompiler.h"
#include "RenderContext.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            std::string VertexShader()
            {
                return
                "attribute vec2 Position;\n"
                "attribute mediump vec2 UV;\n"
                "varying mediump vec2 DestinationUV;\n"
                "void main(void) { \n"
                "DestinationUV = UV;\n"
                "vec2 pos = Position;\n"
                "gl_Position = vec4(pos, 0.0, 1.0);\n"
                "}";
            }
            
            std::string FragmentShader()
            {
                return
                "precision mediump float;\n"
                "varying mediump vec2 DestinationUV;\n"
                "uniform sampler2D diffuseTex; \n"
                "uniform float fadeMultiplier; \n"
                "void main(void) { \n"
                "highp vec4 colour = texture2D(diffuseTex, DestinationUV.xy); \n"
                "gl_FragColor = colour * fadeMultiplier; \n"
                "}";
            }
            
            VRDistortionShader* VRDistortionShader::Create(const Eegeo::Rendering::TShaderId shaderId)
            {
                return Eegeo_NEW(VRDistortionShader)(shaderId, VertexShader(), FragmentShader());
            }
            
            VRDistortionShader::VRDistortionShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexCode, const std::string& fragmentCode)
            : Shader(shaderId)
            {
                CompileProgram(vertexCode, fragmentCode);
                m_diffuseTextureSamplerUniformLocation = GetUniformLocation("diffuseTex");
                m_fadeMultiplierUniform = GetUniformLocation("fadeMultiplier");
            }
            
            GLuint VRDistortionShader::GetDiffuseSamplerId() const
            {
                return 0;
            }
            
            void VRDistortionShader::SetMVP(const m44& mvp) const{}
            
            void VRDistortionShader::Use(Eegeo::Rendering::GLState& glState) const
            {
                UseProgram(glState);
                SetUniformTextureSampler(glState, GetDiffuseSamplerId(), m_diffuseTextureSamplerUniformLocation);
            }

            void VRDistortionShader::SetFadeMultiplier(float fadeMultiplier)
            {
                SetUniformFloat(fadeMultiplier, m_fadeMultiplierUniform);
            }
        }
    }
}
