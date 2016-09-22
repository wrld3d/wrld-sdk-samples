// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "ICallback.h"
#include "Camera.h"
#include "GlobeCamera.h"
#include "LatLongAltitude.h"
#include "Streaming.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"

namespace Eegeo
{
    namespace Interiors
    {
        class ExampleInteriorController
        {
        public:
            
            ExampleInteriorController(Resources::Interiors::InteriorSelectionModel& selectionModel,
                                      const Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                      Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                      Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                      Resources::Interiors::InteriorsCameraController& cameraController,
                                      Streaming::CameraFrustumStreamingVolume& streamingVolume);
            ~ExampleInteriorController();
            
            void Update(float dt);
            
        private:
            void HandleInteriorSelectionChanged(const Resources::Interiors::InteriorId& interiorId);

            
            Resources::Interiors::InteriorSelectionModel& m_selectionModel;
            const Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
            Resources::Interiors::InteriorTransitionModel& m_interiorTransitionModel;
            Resources::Interiors::Markers::InteriorMarkerModelRepository& m_markerRepository;
            Resources::Interiors::InteriorsCameraController& m_cameraController;
            Streaming::CameraFrustumStreamingVolume& m_streamingVolume;
            
            Helpers::TCallback1<ExampleInteriorController, const Resources::Interiors::InteriorId> m_selectionChangedCallback;
            Space::LatLongAltitude m_interiorFocusOrigin;
            
            float m_transitionParam;
        };
    }
}
