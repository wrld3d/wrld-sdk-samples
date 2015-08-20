// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "BuildingSelectionExample.h"
#include "CollisionVisualizationModule.h"
#include "BuildingFootprintsModule.h"
#include "EnvironmentRayCaster.h"
#include "BuildingSelectionController.h"
#include "CollisionBvh.h"
#include "CameraHelpers.h"
#include "GlobeCameraController.h"
#include "CollisionGroup.h"

namespace Examples
{
    BuildingSelectionExample::BuildingSelectionExample(
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                                                       Eegeo::Modules::CollisionVisualizationModule& collisionVisualizationModule,
                                                       Eegeo::Modules::BuildingFootprintsModule& buildingFootprintsModule,
                                                       Eegeo::Collision::EnvironmentRayCaster* pRayCaster)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_collisionVisualizationModule(collisionVisualizationModule)
    , m_buildingFootprintsModule(buildingFootprintsModule)
    , m_pRayCaster(pRayCaster)
    , m_buildingSelectionController(m_buildingFootprintsModule.GetBuildingSelectionController())
    {
    }
    
    BuildingSelectionExample::~BuildingSelectionExample()
    {
        delete m_pRayCaster;
    }
    
    void BuildingSelectionExample::Update(float dt)
    {
        m_collisionVisualizationModule.Update(dt);
        m_buildingFootprintsModule.Update(dt);
    }
    
    void BuildingSelectionExample::PreWorldDraw()
    {
        const Eegeo::Camera::RenderCamera& renderCamera = GetGlobeCameraController().GetRenderCamera();
        m_collisionVisualizationModule.Draw(renderCamera);
        m_buildingFootprintsModule.Draw(renderCamera);
    }
    
    
    void BuildingSelectionExample::Event_TouchTap(const AppInterface::TapData& data)
    {
        const Eegeo::Camera::RenderCamera& renderCamera = GetGlobeCameraController().GetRenderCamera();
        
        float screenPixelX = data.point.GetX();
        float screenPixelY = data.point.GetY();
        
        Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
        Eegeo::dv3 rayDirection;
        Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
        
        PerformRayPick(rayOrigin, rayDirection);
    }
    
    void BuildingSelectionExample::PerformRayPick(const Eegeo::dv3& rayOrigin, const Eegeo::dv3& rayDirection)
    {
        const Eegeo::Collision::RayCasterResult& pickResult = m_pRayCaster->CastRay(rayOrigin, rayDirection, Eegeo::Collision::CollisionGroup::Buildings);
        
        if (pickResult.intersects)
        {
            m_buildingSelectionController.PerformOperation(pickResult, Eegeo::BuildingFootprints::BuildingSelectionController::CycleFlashing);
        }
    }
}