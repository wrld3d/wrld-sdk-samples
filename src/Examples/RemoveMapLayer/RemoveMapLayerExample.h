// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RemoveMapLayerExample__
#define __ExampleApp__RemoveMapLayerExample__

#include "GlobeCameraExampleBase.h"

#include <vector>
#include <set>

namespace Examples
{
    typedef std::set<Eegeo::Rendering::IRenderableFilter*> TLayerFilterSet;
    
    class RemoveMapLayerExample : public GlobeCameraExampleBase
    {
    private:
        Eegeo::Rendering::RenderableFilters& m_renderableFilters;
        std::vector<TLayerFilterSet> m_layerRenderableFilterSets;
        
        float m_timer;
        u16 m_currentIndexToRemove;
        
        void SwitchToNextLayerSet();
        void RemoveAllFiltersInSetAtCurrentIndex();
        void AddAllFiltersInSetAtCurrentIndex();
        
    public:
        RemoveMapLayerExample(Eegeo::Rendering::Filters::PackedRenderableFilter& buildingsFilter,
                              Eegeo::Rendering::Filters::PackedRenderableFilter& shadowFilter,
                              Eegeo::Rendering::Filters::PackedRenderableFilter& terrainFilter,
                              Eegeo::Rendering::Filters::PackedRenderableFilter& roadFilter,
                              Eegeo::Rendering::RenderableFilters& renderableFilters,
                              Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                              Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);


        static std::string GetName()
        {
            return "RemoveMapLayerExample";
        }
        std::string Name() const
        {
            return GetName();
        }

        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();
    };
}

#endif /* defined(__ExampleApp__RemoveMapLayerExample__) */
