// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RemoveMapLayerExample.h"
#include "PackedRenderableFilter.h"
#include "RenderableFilters.h"

namespace Examples
{
    const float TimeBetweenLayerSwitchesInSeconds = 5.f;
    
    RemoveMapLayerExample::RemoveMapLayerExample(Eegeo::Rendering::Filters::PackedRenderableFilter& buildingsFilter,
                                                 Eegeo::Rendering::Filters::PackedRenderableFilter& shadowFilter,
                                                 Eegeo::Rendering::Filters::PackedRenderableFilter& terrainFilter,
                                                 Eegeo::Rendering::Filters::PackedRenderableFilter& roadFilter,
                                                 Eegeo::Rendering::RenderableFilters& renderableFilters,
                                                 Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                 Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
	: GlobeCameraExampleBase(pCameraController, cameraTouchController)
	, m_renderableFilters(renderableFilters)
    , m_timer(0.f)
    , m_currentIndexToRemove(0)
    {
        TLayerFilterSet buildingsAndShadowsSet;
        buildingsAndShadowsSet.insert(&buildingsFilter);
        buildingsAndShadowsSet.insert(&shadowFilter);
        
        TLayerFilterSet allButTerrain;
        allButTerrain.insert(&buildingsFilter);
        allButTerrain.insert(&shadowFilter);
        allButTerrain.insert(&roadFilter);
        
        TLayerFilterSet terrainSet;
        terrainSet.insert(&terrainFilter);
        
        TLayerFilterSet roadSet;
        roadSet.insert(&roadFilter);
        
        m_layerRenderableFilterSets.push_back(buildingsAndShadowsSet);
        m_layerRenderableFilterSets.push_back(allButTerrain);
        m_layerRenderableFilterSets.push_back(terrainSet);
        m_layerRenderableFilterSets.push_back(roadSet);
    }

    void RemoveMapLayerExample::Start()
    {
        RemoveAllFiltersInSetAtCurrentIndex();
    }

    void RemoveMapLayerExample::Suspend()
    {
        AddAllFiltersInSetAtCurrentIndex();
    }

    void RemoveMapLayerExample::Update(float dt)
    {
        m_timer += dt;
        
        if (m_timer > TimeBetweenLayerSwitchesInSeconds)
        {
            SwitchToNextLayerSet();
            m_timer = 0.f;
        }
    }

    void RemoveMapLayerExample::Draw()
    {
    }
    
    void RemoveMapLayerExample::SwitchToNextLayerSet()
    {
        AddAllFiltersInSetAtCurrentIndex();
        
        m_currentIndexToRemove = (m_currentIndexToRemove + 1) % m_layerRenderableFilterSets.size();
        
        RemoveAllFiltersInSetAtCurrentIndex();
    }
    
    void RemoveMapLayerExample::RemoveAllFiltersInSetAtCurrentIndex()
    {
        TLayerFilterSet activeSet = m_layerRenderableFilterSets.at(m_currentIndexToRemove);
        
        for (TLayerFilterSet::iterator it = activeSet.begin(); it != activeSet.end(); ++it)
        {
            m_renderableFilters.RemoveRenderableFilter(**it);
        }
    }
    
    void RemoveMapLayerExample::AddAllFiltersInSetAtCurrentIndex()
    {
        TLayerFilterSet activeSet = m_layerRenderableFilterSets.at(m_currentIndexToRemove);
        
        for (TLayerFilterSet::iterator it = activeSet.begin(); it != activeSet.end(); ++it)
        {
            m_renderableFilters.AddRenderableFilter(**it);
        }
    }
}