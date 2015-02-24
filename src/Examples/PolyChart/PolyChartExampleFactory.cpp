// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PolyChartExampleFactory.h"
#include "PolyChartExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"
#include "DefaultCameraControllerFactory.h"
#include "PolyChartModule.h"
#include "DataModule.h"

namespace Examples
{
    
    PolyChartExampleFactory::PolyChartExampleFactory(Eegeo::EegeoWorld& world,
                                                                     DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                                     Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
    : m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    {
        
    }
    
    IExample* PolyChartExampleFactory::CreateExample() const
    {
        Eegeo::Modules::Data::PolyChartModule& polyChartModule = m_world.GetDataModule().GetPolyChartModule();
        
        return new Examples::PolyChartExample(
                                                      polyChartModule.GetController(),
                                                      m_defaultCameraControllerFactory.Create(),
                                                      m_globeCameraTouchController);
    }
    
    std::string PolyChartExampleFactory::ExampleName() const
    {
        return Examples::PolyChartExample::GetName();
    }
}

