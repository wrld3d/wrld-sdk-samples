// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EnvironmentRayCasterExample.h"
#include "EnvironmentRayCaster.h"
#include "CameraHelpers.h"
#include "DebugRenderer.h"
#include "GlobeCameraController.h"
#include "EnvironmentFlatteningService.h"

namespace Examples
{
    namespace
    {
        Eegeo::v4 ColorFromCollisionGroup(Eegeo::Collision::CollisionGroup::Type collisionGroup)
        {
            switch (collisionGroup)
            {
                case Eegeo::Collision::CollisionGroup::Buildings:
                    return Eegeo::v4(0.f, 0.f, 1.f, 1.f);
                case Eegeo::Collision::CollisionGroup::Terrain:
                    return Eegeo::v4(139.f/255.f, 69.f/255.f, 19.f/255.f, 1.f);
                case Eegeo::Collision::CollisionGroup::Trees:
                    return Eegeo::v4(0.f, 1.f, 0.f, 1.f);
                case Eegeo::Collision::CollisionGroup::Roads:
                    return Eegeo::v4(1.f, 0.f, 0.f, 1.f);
                case Eegeo::Collision::CollisionGroup::Rail:
                    return Eegeo::v4(0.f, 0.f, 0.f, 1.f);
                default:
                    break;
            }
            return Eegeo::v4(1.f, 1.f, 1.f, 1.f);
        }
    }

    
    EnvironmentRayCasterExample::EnvironmentRayCasterExample(
                                                             Eegeo::Collision::ICollisionBvhProvider& collisionBvhProvider,
                                                             Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                         Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                         Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                         Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_environmentFlatteningService(environmentFlatteningService)
    , m_debugRenderer(debugRenderer)
    , m_pRayCaster(NULL)
    , m_sphereColour(Eegeo::v4::Zero())
    , m_surfaceNormal(Eegeo::v3::Zero())
    , m_spherePosition(Eegeo::dv3::Zero())
    , m_drawMarker(false)
    {
        m_pRayCaster = new Eegeo::Collision::EnvironmentRayCaster(collisionBvhProvider, environmentFlatteningService);
    }
    
    EnvironmentRayCasterExample::~EnvironmentRayCasterExample()
    {
        m_environmentFlatteningService.SetIsFlattened(false);
        delete m_pRayCaster;
    }
    
    void EnvironmentRayCasterExample::Start()
    {
    }
    
    void EnvironmentRayCasterExample::Suspend()
    {
        
        
    }
    
    void EnvironmentRayCasterExample::Update(float dt)
    {
        const float environmentFlatteningPeriod = 10.f;
        const float environmentFlatteningFrequency = 1.f / environmentFlatteningPeriod;
        
        m_environmentFlatteningPhase += dt*environmentFlatteningFrequency;
        m_environmentFlatteningPhase = std::fmod(m_environmentFlatteningPhase, 1.f);
        
        const float ratio = 0.5f;
        
        bool shouldBeFlattened = m_environmentFlatteningPhase > ratio;
        
        if (m_environmentFlatteningService.IsFlattened() != shouldBeFlattened)
        {
            m_environmentFlatteningService.ToggleFlattened();
            m_drawMarker = false;
        }
    }
    
    void EnvironmentRayCasterExample::Draw()
    {
        if (!m_drawMarker)
            return;
        
        const Eegeo::Camera::RenderCamera& renderCamera = GetGlobeCameraController().GetRenderCamera();
        
        const float altitudeScale = 1.f + 200.f*Eegeo::Math::Clamp01(renderCamera.GetAltitude() / 20000.f);
        
        m_debugRenderer.SetDepthTestEnabled(true);
        m_debugRenderer.DrawSphere(m_spherePosition, 1.f*altitudeScale, m_sphereColour);
        const float normalLength = 4.f*altitudeScale;
        m_debugRenderer.DrawLine(m_spherePosition, m_spherePosition + m_surfaceNormal*normalLength, Eegeo::v4(1.f, 1.f, 1.f, 1.f));
        
        m_debugRenderer.SetDepthTestEnabled(false);
    }
    
    
    void EnvironmentRayCasterExample::Event_TouchTap(const AppInterface::TapData& data)
    {
        const Eegeo::Camera::RenderCamera& renderCamera = GetGlobeCameraController().GetRenderCamera();
        
        float screenPixelX = data.point.GetX();
        float screenPixelY = data.point.GetY();
        
        
        Eegeo::dv3 rayDirection;
        Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
        
        const Eegeo::dv3& rayOrigin = renderCamera.GetEcefLocation();
        const Eegeo::Collision::RayCasterResult& pickResult = m_pRayCaster->CastRay(rayOrigin, rayDirection);
        m_sphereColour = ColorFromCollisionGroup(pickResult.collisionGroup);

        if (pickResult.intersects)
        {
            m_spherePosition = pickResult.intersectionPointEcef;
            m_surfaceNormal = pickResult.triangleNormal;
        }

        m_drawMarker = true;
        
        GlobeCameraExampleBase::Event_TouchTap(data);
    }
    
}