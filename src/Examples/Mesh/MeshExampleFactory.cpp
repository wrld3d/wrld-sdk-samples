// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MeshExampleFactory.h"
#include "MeshExample.h"
#include "CoreModule.h"
#include "RenderingModule.h"
#include "DefaultCameraControllerFactory.h"


namespace Examples
{
    MeshExampleFactory::MeshExampleFactory(Eegeo::EegeoWorld& world,
                                           DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
    : m_world(world)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
    {
        
    }
    
    IExample* MeshExampleFactory::CreateExample() const
    {
        Eegeo::Modules::Core::RenderingModule& renderingModule = m_world.GetRenderingModule();
        const Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = m_world.GetPlatformAbstractionModule();
        Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
        
        MeshExampleConfig config;
        config.textureFilename = "mesh_example/quadrants.png";
        config.asyncTextureUrl = "http://cdn1.eegeo.com/mobile-sdk-harness-data/eegeo-tile.png";
        config.originLatLong = std::make_pair(37.785, -122.404);
        config.spacing = 0.002f;
        config.altitude = 150.f;
        config.meshRows = 5;
        config.meshColumns = 3;
        config.boxWidth = 75.f;
        config.boxHeight = 50.f;
        config.revsPerMinuteA = 29.f;
        config.revsPerMinuteB = -17.f;
        config.environmentFlatteningCyclesPerMinute = 4.f;
        config.secondsDelayBeforeTextureWebRequest = 5.f;
        
        return new Examples::MeshExample(m_defaultCameraControllerFactory.Create(),
                                         m_globeCameraTouchController,
                                         renderingModule,
                                         platformAbstractionModule.GetTextureFileLoader(),
                                         mapModule.GetEnvironmentFlatteningService(),
                                         platformAbstractionModule.GetWebLoadRequestFactory(),
                                         config);

    }
    
    std::string MeshExampleFactory::ExampleName() const
    {
        return Examples::MeshExample::GetName();
    }
}
