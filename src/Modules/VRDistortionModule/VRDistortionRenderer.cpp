// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "RenderContext.h"
#include "RenderQueue.h"
#include "VRDistortionRenderable.h"
#include "VRDistortionRenderer.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            VRDistortionRenderer::VRDistortionRenderer(VRDistortionRenderable& renderable)
            : m_renderable(renderable)
            {    
            }
            
            void VRDistortionRenderer::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext,
                                                          Eegeo::Rendering::RenderQueue& renderQueue)
            {
                renderQueue.EnqueueRenderable(m_renderable);
            }
        }
    }
}
