// Copyright eeGeo Ltd 2015, All Rights Reserved

#include "BuildingHighlightExample.h"
#include "PolyChartController.h"
#include "VectorMath.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "GlobeCameraController.h"

namespace Examples
{
    BuildingHighlightExample::BuildingHighlightExample(
                             Eegeo::Data::PolyChart::PolyChartController& polyChartController,
                             Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_polyChartController(polyChartController)
    , m_pBuildingPolyChart(NULL)
    {
        Eegeo::Space::EcefTangentBasis cameraInterestBasis;
        
        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
                                                                          Eegeo::Space::LatLong::FromDegrees(37.791235, -122.397075).ToECEF(),
                                                                          16.472872f,
                                                                          cameraInterestBasis);
        
        pCameraController->SetView(cameraInterestBasis, 700.0f);
    }
    
    void BuildingHighlightExample::Start()
    {
        CreateBuildingHighlight();
        m_polyChartController.Add(*m_pBuildingPolyChart);
    }
    
    void BuildingHighlightExample::Suspend()
    {
        m_polyChartController.Remove(*m_pBuildingPolyChart);
        delete m_pBuildingPolyChart;
        m_pBuildingPolyChart = NULL;
    }
    
    void BuildingHighlightExample::Update(float dt)
    {
    }
    
    void BuildingHighlightExample::Draw()
    {
    }
    
    void BuildingHighlightExample::Event_TouchPan(const AppInterface::PanData& data)
    {
        GlobeCameraExampleBase::Event_TouchPan(data);
    }
    
    void BuildingHighlightExample::Event_TouchDown(const AppInterface::TouchData& data)
    {
        GlobeCameraExampleBase::Event_TouchDown(data);
    }
    
    void BuildingHighlightExample::Event_TouchUp(const AppInterface::TouchData& data)
    {
        GlobeCameraExampleBase::Event_TouchUp(data);
    }
    
    void BuildingHighlightExample::CreateBuildingHighlight()
    {
        // This outline in Lat,Lon WGS84 comes from our geographic data. This will be exposed via a RESTful service in the future.
        // It is intended to be used against the LOD0 building
        std::vector<Eegeo::Space::LatLongAltitude> exteriorVerticesOfBuilding;
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790248930231456, -122.39715697172056, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790406318966596, -122.39696715913533, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790426447532369, -122.39699050549667, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790449982417776, -122.39695737757371, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790463778248125, -122.39697611884986, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790488598743835, -122.39694763702083, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.79075207458763, -122.39726918475478, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.79072927631988, -122.39730537326002, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790748652430331, -122.39732259286829, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790729237734993, -122.39735069004134, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790746346135862, -122.39736508870129, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790562930671271, -122.39759440954549, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790545457143253, -122.39757910523338, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790531738522844, -122.39759307274154, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790504163313706, -122.39755876989155, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790485553317332, -122.39758561105425, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790462419311012, -122.39755615588045, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790441462522992, -122.39758233463405, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790403177964279, -122.39753358123281, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790246094927767, -122.39732508482012, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790279331695771, -122.39728563168448, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790261913395334, -122.39726351259077, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790279915088455, -122.39724110577325, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790255373888265, -122.39720087265381, 0.0));
        exteriorVerticesOfBuilding.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.790270344946528, -122.39718507776054, 0.0));
        
        // Building is 182m high - from our geographic data
        m_pBuildingPolyChart = Eegeo::Data::PolyChart::PolyChartModel::PolyChartBuilder(
                                                                                                             "sf_building_example",
                                                                                                             exteriorVerticesOfBuilding,
                                                                                        Eegeo::v4(1.f, 0.f, 0.f, 0.5f))
                            .AltitudeOffset(3.9675f) // Height of terrain at centroid of building footprint, from TerrainHeightProvider query
                            .AddChartStack(60.6666f, Eegeo::v4(1.f, 0.f, 0.f, 0.5f))
                            .AddChartStack(60.6666f, Eegeo::v4(1.f, 1.f, 0.f, 0.5f))
                            .AddChartStack(60.6666f, Eegeo::v4(1.f, 0.f, 0.f, 0.5f))
                            .Build();
    }
}
