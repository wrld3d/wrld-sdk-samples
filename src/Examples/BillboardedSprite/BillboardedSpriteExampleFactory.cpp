// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "BillboardedSpriteExampleFactory.h"
#include "BillboardedSpriteExample.h"
#include "DefaultCameraControllerFactory.h"
#include "Modules.h"
#include "Rendering.h"
#include "IPlatformAbstractionModule.h"

namespace Examples
{

    BillboardedSpriteExampleFactory::BillboardedSpriteExampleFactory(Eegeo::EegeoWorld& world,
                                                                     DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                                     Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
    : m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    {

    }

    IExample* BillboardedSpriteExampleFactory::CreateExample() const
    {
        Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
        Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = m_world.GetPlatformAbstractionModule();
        return new Examples::BillboardedSpriteExample(m_defaultCameraControllerFactory.Create(),
                                                      m_globeCameraTouchController,
                                                      renderingModule,
                                                      platformAbstractionModule.GetTextureFileLoader(),
                                                      platformAbstractionModule.GetWebLoadRequestFactory());
    }

    std::string BillboardedSpriteExampleFactory::ExampleName() const
    {
        return Examples::BillboardedSpriteExample::GetName();
    }

}

