// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ExampleInteriorModule.h"
#include "InteriorsModelModule.h"
#include "InteriorsPresentationModule.h"
#include "InteriorsStreamingModule.h"
#include "InteriorsConfiguration.h"
#include "IPlatformAbstractionModule.h"
#include "ExampleInteriorController.h"
#include "InteriorsCameraController.h"
#include "CubeFaceFileNames.h"
#include "ScreenProperties.h"
#include "MapModule.h"
#include "GlobeCameraTouchControllerConfiguration.h"
#include "GlobeCameraControllerConfiguration.h"
#include "InteriorsCameraControllerFactory.h"
#include "InteriorsCameraController.h"
#include "GlobeCameraController.h"
#include "GlobeCameraTouchController.h"
#include "ExampleInteriorController.h"

namespace Eegeo
{
    namespace Interiors
    {
        ExampleInteriorModule::ExampleInteriorModule(Modules::Map::Layers::InteriorsModelModule& interiorsModelModule,
                                                   Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule,
                                                   Resources::Interiors::InteriorsCameraControllerFactory& cameraControllerFactory,
                                                   Streaming::CameraFrustumStreamingVolume& streamingVolume,
                                                   const Rendering::ScreenProperties& screenProperties)
        {
            m_pGlobeCameraTouchController = cameraControllerFactory.CreateTouchController();
            m_pGlobeCameraController = cameraControllerFactory.CreateInteriorGlobeCameraController(*m_pGlobeCameraTouchController);
            
            m_pInteriorCameraController = cameraControllerFactory.CreateInteriorsCameraController(*m_pGlobeCameraTouchController, *m_pGlobeCameraController);
            m_pInteriorCameraController->UpdateScreenProperties(screenProperties);
            
            m_pExampleInteriorController = Eegeo_NEW(ExampleInteriorController)(
                                                                        interiorsPresentationModule.GetInteriorSelectionModel(),
                                                                        interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                        interiorsPresentationModule.GetInteriorTransitionModel(),
                                                                        interiorsModelModule.GetInteriorMarkerModelRepository(),
                                                                        *m_pInteriorCameraController,
                                                                        streamingVolume);
        }
        
        ExampleInteriorModule::~ExampleInteriorModule()
        {
            Eegeo_DELETE m_pInteriorCameraController;
            Eegeo_DELETE m_pGlobeCameraController;
            Eegeo_DELETE m_pGlobeCameraTouchController;
            Eegeo_DELETE m_pExampleInteriorController;
        }
        
        void ExampleInteriorModule::Update(float dt)
        {
            m_pInteriorCameraController->Update(dt);
            m_pExampleInteriorController->Update(dt);
        }
        
        void ExampleInteriorModule::UpdateScreenProperties(const Rendering::ScreenProperties& screenProperties)
        {
            m_pInteriorCameraController->UpdateScreenProperties(screenProperties);
        }

        Resources::Interiors::InteriorsCameraController& ExampleInteriorModule::GetInteriorCameraController() const
        {
            return *m_pInteriorCameraController;
        }
        
        ITouchController& ExampleInteriorModule::GetInteriorCameraTouchController() const
        {
            return *m_pGlobeCameraTouchController;
        }
    }
}
