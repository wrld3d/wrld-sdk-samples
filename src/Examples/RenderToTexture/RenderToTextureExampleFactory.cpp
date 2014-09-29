// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RenderToTextureExampleFactory.h"
#include "RenderToTextureExample.h"

#include "RenderingModule.h"

namespace Examples
{
    RenderToTextureExampleFactory::RenderToTextureExampleFactory(Eegeo::EegeoWorld& world,
                                                                 Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
    : m_world(world)
    , m_globeCameraController(globeCameraController)
    {
        
    }
    
    IExample* RenderToTextureExampleFactory::CreateExample() const
    {
        Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
        
        return new Examples::RenderToTextureExample(m_globeCameraController,
                                                    m_world.GetScreenProperties(),
                                                    renderingModule.GetVertexLayoutPool(),
                                                    renderingModule.GetVertexBindingPool(),
                                                    renderingModule.GetShaderIdGenerator(),
                                                    renderingModule.GetMaterialIdGenerator(),
                                                    renderingModule.GetRenderableFilters(),
                                                    renderingModule.GetGlBufferPool());
    }
    
    std::string RenderToTextureExampleFactory::ExampleName() const
    {
        return Examples::RenderToTextureExample::GetName();
    }
}
