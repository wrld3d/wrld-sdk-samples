// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once


#include "IExampleFactory.h"
#include "GlobeCameraExampleBase.h"
#include "EegeoWorld.h"
#include "Modules.h"

namespace Examples
{
    class BuildingSelectionExampleFactory : public IExampleFactory
    {
    public:
        BuildingSelectionExampleFactory(Eegeo::EegeoWorld& world,
                                        DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                        Eegeo::Modules::CollisionVisualizationModule& collisionVisualizationModule,
                                        Eegeo::Modules::BuildingFootprintsModule& buildingFootprintsModule);
        
        std::string ExampleName() const;
        
        IExample* CreateExample() const;
        
    private:
    
        Eegeo::EegeoWorld& m_world;
        DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;
        Eegeo::Modules::CollisionVisualizationModule& m_collisionVisualizationModule;
        Eegeo::Modules::BuildingFootprintsModule& m_buildingFootprintsModule;
    };
}