// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RenderToTextureExampleFactory.h"
#include "RenderToTextureExample.h"
#include "DefaultCameraControllerFactory.h"
#include "RenderingModule.h"

namespace Examples
{
    RenderToTextureExampleFactory::RenderToTextureExampleFactory(Eegeo::EegeoWorld& world,
                                                                 DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                                 Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                                                 const IScreenPropertiesProvider& screenPropertiesProvider)
    : m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    , m_screenPropertiesProvider(screenPropertiesProvider)
    {
        
    }
    
    IExample* RenderToTextureExampleFactory::CreateExample() const
    {
        Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
        
        return new Examples::RenderToTextureExample(m_defaultCameraControllerFactory.Create(),
                                                    m_globeCameraTouchController,
                                                    m_screenPropertiesProvider.GetScreenProperties(),
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
