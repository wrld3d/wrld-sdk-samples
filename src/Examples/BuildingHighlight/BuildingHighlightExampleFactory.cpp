// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "BuildingHighlightExampleFactory.h"
#include "BuildingHighlightExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"
#include "DefaultCameraControllerFactory.h"
#include "PolyChartModule.h"
#include "DataModule.h"

namespace Examples
{
    
    BuildingHighlightExampleFactory::BuildingHighlightExampleFactory(Eegeo::EegeoWorld& world,
                                                           DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
    : m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    {
        
    }
    
    IExample* BuildingHighlightExampleFactory::CreateExample() const
    {
        Eegeo::Modules::Data::PolyChartModule& polyChartModule = m_world.GetDataModule().GetPolyChartModule();
        
        return new Examples::BuildingHighlightExample(
                                                 polyChartModule.GetController(),
                                                 m_defaultCameraControllerFactory.Create(),
                                                 m_globeCameraTouchController);
    }
    
    std::string BuildingHighlightExampleFactory::ExampleName() const
    {
        return Examples::BuildingHighlightExample::GetName();
    }
}

