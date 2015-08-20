// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "GlobeCameraExampleBase.h"
#include "Modules.h"
#include "Collision.h"
#include "CollisionVisualization.h"
#include "BuildingFootprints.h"

namespace Examples
{
    class BuildingSelectionExample : public GlobeCameraExampleBase
    {
    public:
        BuildingSelectionExample(Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                 Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                                 Eegeo::Modules::CollisionVisualizationModule& collisionVisualizationModule,
                                 Eegeo::Modules::BuildingFootprintsModule& buildingFootprintsModule,
                                 Eegeo::Collision::EnvironmentRayCaster* pRayCaster);
        
        virtual ~BuildingSelectionExample();
        
        static std::string GetName() { return "BuildingSelectionExample"; }
        std::string Name() const { return GetName(); }
        
        void Start() {;}
        void Update(float dt);
        void PreWorldDraw();
        void Draw() {;}
        void Suspend() {;}

        void Event_TouchTap(const AppInterface::TapData& data);
    private:
        void PerformRayPick(const Eegeo::dv3& rayOrigin, const Eegeo::dv3& rayDirection);
    
        Eegeo::Modules::CollisionVisualizationModule& m_collisionVisualizationModule;
        Eegeo::Modules::BuildingFootprintsModule& m_buildingFootprintsModule;
        Eegeo::Collision::EnvironmentRayCaster* m_pRayCaster;
        Eegeo::BuildingFootprints::BuildingSelectionController& m_buildingSelectionController;
    };
}


