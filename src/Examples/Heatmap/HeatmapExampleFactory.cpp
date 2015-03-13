// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "HeatmapExampleFactory.h"
#include "HeatmapExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"
#include "DefaultCameraControllerFactory.h"
#include "HeatmapModule.h"
#include "DataModule.h"
#include "IPlatformAbstractionModule.h"

namespace Examples
{
    HeatmapExampleFactory::HeatmapExampleFactory(Eegeo::EegeoWorld& world,
                                                 DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                 Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
        : m_world(world)
        , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
        , m_globeCameraTouchController(globeCameraTouchController)
    {
    }
    
    IExample* HeatmapExampleFactory::CreateExample() const
    {
        Eegeo::Modules::IPlatformAbstractionModule& platformAbstractioModule = m_world.GetPlatformAbstractionModule();

        Eegeo::Modules::Data::HeatmapModule& heatmapModule = m_world.GetDataModule().GetHeatmapModule();
        
        return new Examples::HeatmapExample(
                                              heatmapModule.GetController(),
                                              m_defaultCameraControllerFactory.Create(),
                                              m_globeCameraTouchController,
                                              platformAbstractioModule.GetTextureFileLoader()
                                            );
    }
    
    std::string HeatmapExampleFactory::ExampleName() const
    {
        return Examples::HeatmapExample::GetName();
    }
}

