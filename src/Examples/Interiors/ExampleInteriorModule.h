// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "Modules.h"
#include "Interiors.h"
#include "GlobeCamera.h"
#include "Streaming.h"
#include "EegeoRootDeclarations.h"
#include "InteriorsCameraControllerFactory.h"

namespace Eegeo
{
    namespace Interiors
    {
        class ExampleInteriorController;
        
        class ExampleInteriorModule
        {
        public:
            
            ExampleInteriorModule(Modules::Map::Layers::InteriorsModelModule& interiorsModelModule,
                                  Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule,
                                  Resources::Interiors::InteriorsCameraControllerFactory& cameraControllerFactory,
                                  Streaming::CameraFrustumStreamingVolume& streamingVolume,
                                  const Rendering::ScreenProperties& screenProperties);
            ~ExampleInteriorModule();
            
            Resources::Interiors::InteriorsCameraController& GetInteriorCameraController() const;
            ITouchController& GetInteriorCameraTouchController() const;
            
            void Update(float dt);
            void UpdateScreenProperties(const Rendering::ScreenProperties& screenProperties);
            
        private:
            
            Resources::Interiors::InteriorsCameraController* m_pInteriorCameraController;
            Camera::GlobeCamera::GlobeCameraTouchController* m_pGlobeCameraTouchController;
            Camera::GlobeCamera::GlobeCameraController* m_pGlobeCameraController;
            ExampleInteriorController* m_pExampleInteriorController;
            
        };
    }
}
