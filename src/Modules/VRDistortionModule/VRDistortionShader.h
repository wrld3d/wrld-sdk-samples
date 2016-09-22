// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Shader.h"
#include "Rendering.h"
#include "Graphics.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            class VRDistortionShader : public Eegeo::Rendering::Shader
            {
            public:
                static VRDistortionShader* Create(const Eegeo::Rendering::TShaderId shaderId);
                void Use(Eegeo::Rendering::GLState& glState) const;
                GLuint GetDiffuseSamplerId() const;
                void SetMVP(const m44& mvp) const;
                void SetFadeMultiplier(float fadeMultiplier);

            private:
                VRDistortionShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexCode, const std::string& fragmentCode);
                GLuint m_diffuseTextureSamplerUniformLocation;
                GLuint m_fadeMultiplierUniform;
            };
            
        }
    }
}

