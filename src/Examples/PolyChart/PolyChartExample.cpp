// Copyright eeGeo Ltd 2015, All Rights Reserved

#include "PolyChartExample.h"
#include "PolyChartController.h"
#include "VectorMath.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "GlobeCameraController.h"
#include "ExamplePolygons.h"

namespace Examples
{
    namespace
    {
        const Eegeo::v4 ScottishNationalParty(1.f, 204.f/255.f, 0.f, 0.5f);
        const Eegeo::v4 Labour(204.f/255.f, 0.f, 0.f, 0.5f);
        const Eegeo::v4 LiberalDemocrats(1.f, 153.f/255.f, 0.f, 0.5f);
        const Eegeo::v4 Conservative(51.f/255.f, 51.f/255.f, 153.f/255.f, 0.5f);
        const Eegeo::v4 Other(0.7f, 0.7f, 0.7f, 0.5f);
    
        const Eegeo::v4 ScottishNationalPartyNoAlpha(1.f, 204.f/255.f, 0.f, 1.f);
        const Eegeo::v4 LabourNoAlpha(204.f/255.f, 0.f, 0.f, 1.f);
        const Eegeo::v4 LiberalDemocratsNoAlpha(1.f, 153.f/255.f, 0.f, 2.f);
        const Eegeo::v4 ConservativeNoAlpha(51.f/255.f, 51.f/255.f, 153.f/255.f, 1.f);
        const Eegeo::v4 OtherNoAlpha(0.7f, 0.7f, 0.7f, 1.f);
    }
    
    PolyChartExample::PolyChartExample(
                                                       Eegeo::Data::PolyChart::PolyChartController& polyChartController,
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_polyChartController(polyChartController)
    , m_pDundeeEastCylinder(NULL)
    , m_pDundeeWestCylinder(NULL)
    , m_pDundeeEastWard(NULL)
    , m_pDundeeWestWard(NULL)
    {
        Eegeo::Space::EcefTangentBasis cameraInterestBasis;
        
        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
                                                                          Eegeo::Space::LatLong::FromDegrees(56.462870, -3.003617).ToECEF(),
                                                                          16.472872f,
                                                                          cameraInterestBasis);
        
        pCameraController->SetView(cameraInterestBasis, 1900.0f);
    }
    
    void PolyChartExample::Start()
    {
        CreateDundeeEastData();
        CreateDundeeWestData();
        m_polyChartController.Add(*m_pDundeeEastWard);
        m_polyChartController.Add(*m_pDundeeWestWard);
        m_polyChartController.Add(*m_pDundeeEastCylinder);
        m_polyChartController.Add(*m_pDundeeWestCylinder);
    }
    
    void PolyChartExample::Suspend()
    {
        m_polyChartController.Remove(*m_pDundeeWestCylinder);
        m_polyChartController.Remove(*m_pDundeeEastCylinder);
        m_polyChartController.Remove(*m_pDundeeWestWard);
        m_polyChartController.Remove(*m_pDundeeEastWard);
        delete m_pDundeeWestCylinder;
        delete m_pDundeeWestWard;
        delete m_pDundeeEastCylinder;
        delete m_pDundeeEastWard;
        m_pDundeeWestCylinder = NULL;
        m_pDundeeWestWard = NULL;
        m_pDundeeEastCylinder = NULL;
        m_pDundeeEastWard = NULL;
    }
    
    void PolyChartExample::Update(float dt)
    {
    }
    
    void PolyChartExample::Draw()
    {
    }
    
    void PolyChartExample::Event_TouchPan(const AppInterface::PanData& data)
    {
        GlobeCameraExampleBase::Event_TouchPan(data);
    }
    
    void PolyChartExample::Event_TouchDown(const AppInterface::TouchData& data)
    {
        GlobeCameraExampleBase::Event_TouchDown(data);
    }
    
    void PolyChartExample::Event_TouchUp(const AppInterface::TouchData& data)
    {
        GlobeCameraExampleBase::Event_TouchUp(data);
    }
    
    void PolyChartExample::CreateDundeeEastData()
    {
        std::vector<Eegeo::Space::LatLongAltitude> dundeeEast;
        Examples::Data::DundeeEast(dundeeEast);
        
        m_pDundeeEastWard = Eegeo::Data::PolyChart::PolyChartModel::PolyChartBuilder(
                                                                                     "dundee_east_ward",
                                                                                     dundeeEast,
                                                                                     ScottishNationalParty)
                            .Build();
        
        m_pDundeeEastCylinder = Eegeo::Data::PolyChart::PolyChartModel::PolyChartBuilder( "dundee_east_data", Eegeo::Space::LatLongAltitude::FromDegrees(56.473253, -2.936197, 0.0), 30.f, ScottishNationalPartyNoAlpha)
                            .AltitudeOffset(50.f)
                            .AddChartStack(3.f * 3.f, OtherNoAlpha)
                            .AddChartStack(10.6f * 3.f, LiberalDemocratsNoAlpha)
                            .AddChartStack(15.2f * 3.f, ConservativeNoAlpha)
                            .AddChartStack(33.3f * 3.f, LabourNoAlpha)
                            .AddChartStack(37.8f * 3.f, ScottishNationalPartyNoAlpha)
                            .Build();
    }
    
    void PolyChartExample::CreateDundeeWestData()
    {
        std::vector<Eegeo::Space::LatLongAltitude> dundeeWest;
        Data::DundeeWest(dundeeWest);
        
        m_pDundeeWestWard = Eegeo::Data::PolyChart::PolyChartModel::PolyChartBuilder(
                                                                                        "dundee_west_ward",
                                                                                        dundeeWest,
                                                                                        Labour)
                    .Build();
        
        m_pDundeeWestCylinder = Eegeo::Data::PolyChart::PolyChartModel::PolyChartBuilder( "dundee_west_data", Eegeo::Space::LatLongAltitude::FromDegrees(56.462514, -3.008166, 0.0), 30.f, LabourNoAlpha)
                    .AltitudeOffset(50.f)
                    .AddChartStack(2.f * 3.f, OtherNoAlpha)
                    .AddChartStack(9.3f * 3.f, ConservativeNoAlpha)
                    .AddChartStack(11.4f * 3.f, LiberalDemocratsNoAlpha)
                    .AddChartStack(28.9f * 3.f, ScottishNationalPartyNoAlpha)
                    .AddChartStack(48.5f * 3.f, LabourNoAlpha)
                    .Build();
    }
}
