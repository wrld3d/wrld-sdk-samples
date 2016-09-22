// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "VRDistortionRenderable.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            void VRDistortionRenderable::Render(Eegeo::Rendering::GLState& glState) const
            {
                m_material->SetStatePerRenderable(this, glState);
                m_pMesh->BindVertexBuffers(GetVertexBinding(), glState);
                const u32 indexCount = m_pMesh->GetNumOfIndices();

                Eegeo_ASSERT(indexCount != 0);
                Eegeo_GL(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, (void*)(0)));
                m_pMesh->UnbindVertexBuffers(glState);
                
            }

            void VRDistortionRenderable::SetFadeModifier(float fadeModifier)
            {
                m_fadeModifier = fadeModifier;
            }

            float VRDistortionRenderable::GetFadeModifier() const
            {
                return m_fadeModifier;
            }
        }
    }
}
