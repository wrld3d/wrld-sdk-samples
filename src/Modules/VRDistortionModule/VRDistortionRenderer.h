// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "IRenderableFilter.h"
#include "VRDistortionIncludes.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            class VRDistortionRenderer : Eegeo::NonCopyable, public Eegeo::Rendering::IRenderableFilter
            {
                
            public:
                VRDistortionRenderer(VRDistortionRenderable& renderable);
                void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
            private:
                VRDistortionRenderable& m_renderable;
                
            };
            
        }
    }
}


