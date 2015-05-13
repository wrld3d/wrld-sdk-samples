// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "StencilAreaExampleFactory.h"
#include "StencilAreaExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"
#include "DefaultCameraControllerFactory.h"
#include "StencilAreaModule.h"
#include "DataModule.h"

namespace Examples
{
    
    StencilAreaExampleFactory::StencilAreaExampleFactory(Eegeo::EegeoWorld& world,
                                                     DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                     Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
    : m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    {
        
    }
    
    IExample* StencilAreaExampleFactory::CreateExample() const
    {
        Eegeo::Modules::Data::StencilAreaModule& StencilAreaModule = m_world.GetDataModule().GetStencilAreaModule();
        
        return new Examples::StencilAreaExample(
                                              m_world.GetPlatformAbstractionModule().GetWebLoadRequestFactory(),
                                              m_world.GetNativeUIFactories(),
                                              StencilAreaModule.GetController(),
                                              m_defaultCameraControllerFactory.Create(),
                                              m_globeCameraTouchController);
    }
    
    std::string StencilAreaExampleFactory::ExampleName() const
    {
        return Examples::StencilAreaExample::GetName();
    }
}

