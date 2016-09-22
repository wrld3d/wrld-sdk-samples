// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Rendering.h"
#include "MeshRenderable.h"
#include "VectorMathDecl.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            class VRDistortionRenderable : public Eegeo::Rendering::Renderables::MeshRenderable
            {
            public:
                VRDistortionRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                       Eegeo::Rendering::Materials::IMaterial* pMaterial,
                                       const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                       Eegeo::Rendering::Mesh* pMesh)
                : MeshRenderable(layerId, Eegeo::dv3(), pMaterial, pMesh, vertexBinding)
                {}
                
                virtual void Render(Eegeo::Rendering::GLState& glState) const;

                void SetFadeModifier(float fadeModifier);
                float GetFadeModifier() const;

            private:
                float m_fadeModifier;
            };
        }
    }
}

#pragma once
