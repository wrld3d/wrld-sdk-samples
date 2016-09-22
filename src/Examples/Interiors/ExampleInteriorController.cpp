// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ExampleInteriorController.h"
#include "InteriorsCameraController.h"
#include "InteriorSelectionModel.h"
#include "InteriorId.h"
#include "InteriorMarkerModelRepository.h"
#include "InteriorMarkerModel.h"
#include "CameraHelpers.h"
#include "VectorMath.h"
#include "EcefTangentBasis.h"
#include "GlobeCameraController.h"
#include "CameraFrustumStreamingVolume.h"
#include "EarthConstants.h"
#include "InteriorsModel.h"
#include "LatLongAltitude.h"
#include "InteriorInteractionModel.h"
#include "InteriorTransitionModel.h"

namespace Eegeo
{
    namespace Interiors
    {
        namespace
        {
            const float InitialDistance = 400.0f;
        }
        
        ExampleInteriorController::ExampleInteriorController(Resources::Interiors::InteriorSelectionModel& selectionModel,
                                                             const Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                             Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                                             Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                                             Resources::Interiors::InteriorsCameraController& cameraController,
                                                             Streaming::CameraFrustumStreamingVolume& streamingVolume)
        : m_selectionModel(selectionModel)
        , m_interiorInteractionModel(interiorInteractionModel)
        , m_interiorTransitionModel(interiorTransitionModel)
        , m_markerRepository(markerRepository)
        , m_cameraController(cameraController)
        , m_streamingVolume(streamingVolume)
        , m_interiorFocusOrigin(0, 0, 0)
        , m_selectionChangedCallback(this, &ExampleInteriorController::HandleInteriorSelectionChanged)
        , m_transitionParam(0.0f)
        {
            m_selectionModel.RegisterSelectionChangedCallback(m_selectionChangedCallback);
        }
        
        ExampleInteriorController::~ExampleInteriorController()
        {
            m_selectionModel.UnregisterSelectionChangedCallback(m_selectionChangedCallback);
        }
        
        void ExampleInteriorController::HandleInteriorSelectionChanged(const Resources::Interiors::InteriorId& interiorId)
        {
            if (m_selectionModel.IsInteriorSelected())
            {
                const Resources::Interiors::InteriorId& interiorId = m_selectionModel.GetSelectedInteriorId();
                if(m_markerRepository.Contains(interiorId))
                {
                    const Resources::Interiors::Markers::InteriorMarkerModel& marker = m_markerRepository.Get(interiorId);
                    m_interiorFocusOrigin = marker.GetMarkerLatLongAltitude();
                    
                    m_cameraController.SetInterestLocation(m_interiorFocusOrigin.ToECEF());
                    m_cameraController.SetDistanceToInterest(InitialDistance);
                }
            }
            
            bool forceToHighestLod = m_selectionModel.IsInteriorSelected();
            m_streamingVolume.SetForceMaximumRefinement(forceToHighestLod);
        }
        
        void ExampleInteriorController::Update(float dt)
        {
            const bool shouldDisplay = m_selectionModel.IsInteriorSelected() && m_interiorInteractionModel.HasInteriorModel();
            const float transitionTarget = shouldDisplay ? 1.f : 0.f;
            
            float delta = 0.f;
            if (m_transitionParam < transitionTarget)
            {
                delta = dt;
            }
            else if (m_transitionParam > transitionTarget)
            {
                delta = -dt;
            }

            m_transitionParam += delta;
            m_transitionParam = Math::Clamp01(m_transitionParam);
            
            m_interiorTransitionModel.SetVisibilityParam(m_transitionParam);
            
            if (m_selectionModel.IsInteriorSelected() && !m_interiorInteractionModel.HasInteriorModel())
            {
                m_cameraController.SetInterestLocation(m_interiorFocusOrigin.ToECEF());
                m_cameraController.SetDistanceToInterest(InitialDistance);
            }
        }
    }
}
