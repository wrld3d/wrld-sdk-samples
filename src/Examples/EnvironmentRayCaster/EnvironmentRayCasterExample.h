// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "GlobeCameraExampleBase.h"
#include "Rendering.h"
#include "Terrain.h"
#include "Camera.h"
#include "DebugRendering.h"
#include "Collision.h"

namespace Examples
{
    /*!
     *  Demonstrates use of class EnvironmentRayCaster, to perform raycast collision detection
     *  against environment resource meshes
     *  When the touch screen is tapped, a ray is constructed that passes through the camera origin and
     *  a screen pixel.
     *  We use EnvironmentRayCaster to perform ray cast collision, drawing a marker at the first 
     *  intersection point.
     *  The color of the marker sphere indicates the type of resource collided with:
     *      brown: terrain
     *      blue: buildings
     *      green: trees / forrest
     *      red: roads
     *      black: rail
     *      white: no collision found
     *  A white line shows the surface normal of the environment mesh at the point of intersection
     */
    class EnvironmentRayCasterExample : public GlobeCameraExampleBase
    {

    public:
        EnvironmentRayCasterExample(
                          Eegeo::Collision::ICollisionBvhProvider& collisionBvhProvider,
                          Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                          Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                          Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);
        
        virtual ~EnvironmentRayCasterExample();
        
        static std::string GetName()
        {
            return "EnvironmentRayCasterExample";
        }
        std::string Name() const
        {
            return GetName();
        }
        
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();

        void Event_TouchTap(const AppInterface::TapData& data);
        
    private:
        
    
        Eegeo::Collision::EnvironmentRayCaster* m_pRayCaster;
        Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
        Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
        
        
        Eegeo::dv3 m_spherePosition;
        Eegeo::v4 m_sphereColour;
        Eegeo::v3 m_surfaceNormal;
        
        bool m_drawMarker;
        
        float m_environmentFlatteningPhase;
    };
}