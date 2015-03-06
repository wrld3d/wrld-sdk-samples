// Copyright eeGeo Ltd 2015, All Rights Reserved

#include "StencilAreaExample.h"
#include "StencilAreaController.h"
#include "StencilAreaPaletteModel.h"
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
        
        const Eegeo::v4 GreenParty(0.f, 1.f, 0.f, 0.5f);
    }
    
    StencilAreaExample::StencilAreaExample(
                                       Eegeo::Data::StencilArea::StencilAreaController& StencilAreaController,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_StencilAreaController(StencilAreaController)
    , m_pDundeeEastPalette(NULL)
    , m_pDundeeWestPalette(NULL)
    , m_pDundeeEastWard(NULL)
    , m_pDundeeWestWard(NULL)
    , m_pCirclePalette(NULL)
    , m_pCircleArea(NULL)
    {
        Eegeo::Space::EcefTangentBasis cameraInterestBasis;
        
        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
                                                                          Eegeo::Space::LatLong::FromDegrees(56.459956, -2.978128).ToECEF(),
                                                                          16.472872f,
                                                                          cameraInterestBasis);
        
        pCameraController->SetView(cameraInterestBasis, 1900.0f);
    }
    
    void StencilAreaExample::Start()
    {
        CreateDundeeEastData();
        CreateDundeeWestData();
        
        m_pCirclePalette = Eegeo::Data::StencilArea::StencilAreaPaletteModel::StencilAreaPaletteBuilder("circle_palette", GreenParty).Build();
        m_pCircleArea = Eegeo::Data::StencilArea::StencilAreaModel::StencilAreaBuilder("circle_area",
                                                                                       *m_pCirclePalette,
                                                                                       Eegeo::Space::LatLongAltitude::FromDegrees(56.459977, -2.978189,0),
                                                                                       80.f,
                                                                                       Eegeo::Rendering::StencilMapLayerMask::TransportAndTerrain,
                                                                                       150.f)
                                                                                    .Build();
        
        m_StencilAreaController.Add(*m_pDundeeEastWard);
        m_StencilAreaController.Add(*m_pDundeeWestWard);
        m_StencilAreaController.Add(*m_pCircleArea);
    }
    
    void StencilAreaExample::Suspend()
    {
        m_StencilAreaController.Remove(*m_pCircleArea);
        m_StencilAreaController.Remove(*m_pDundeeWestWard);
        m_StencilAreaController.Remove(*m_pDundeeEastWard);
        delete m_pDundeeWestPalette;
        delete m_pDundeeWestWard;
        delete m_pDundeeEastPalette;
        delete m_pDundeeEastWard;
        delete m_pCirclePalette;
        delete m_pCircleArea;
        m_pDundeeWestPalette = NULL;
        m_pDundeeWestWard = NULL;
        m_pDundeeEastPalette = NULL;
        m_pDundeeEastWard = NULL;
        m_pCirclePalette = NULL;
        m_pCircleArea = NULL;
    }
    
    void StencilAreaExample::Update(float dt)
    {
    }
    
    void StencilAreaExample::Draw()
    {
    }
    
    void StencilAreaExample::Event_TouchPan(const AppInterface::PanData& data)
    {
        GlobeCameraExampleBase::Event_TouchPan(data);
    }
    
    void StencilAreaExample::Event_TouchDown(const AppInterface::TouchData& data)
    {
        GlobeCameraExampleBase::Event_TouchDown(data);
    }
    
    void StencilAreaExample::Event_TouchUp(const AppInterface::TouchData& data)
    {
        GlobeCameraExampleBase::Event_TouchUp(data);
    }
    
    void StencilAreaExample::CreateDundeeEastData()
    {
        std::vector<Eegeo::Space::LatLongAltitude> dundeeEast;
        Examples::Data::DundeeEast(dundeeEast);
        
        m_pDundeeEastPalette = Eegeo::Data::StencilArea::StencilAreaPaletteModel::StencilAreaPaletteBuilder("dundee_east_palette", ScottishNationalParty).Build();
        
        m_pDundeeEastWard = Eegeo::Data::StencilArea::StencilAreaModel::StencilAreaBuilder(
                                                                                     "dundee_east_ward",
                                                                                     *m_pDundeeEastPalette,
                                                                                     dundeeEast,
                                                                                     Eegeo::Rendering::StencilMapLayerMask::Terrain,
                                                                                     150.f)
                                .Build();
    }
    
    void StencilAreaExample::CreateDundeeWestData()
    {
        std::vector<Eegeo::Space::LatLongAltitude> dundeeWest;
        Examples::Data::DundeeWest(dundeeWest);
        
        m_pDundeeWestPalette = Eegeo::Data::StencilArea::StencilAreaPaletteModel::StencilAreaPaletteBuilder("dundee_west_palette", Labour).Build();
        
        m_pDundeeWestWard = Eegeo::Data::StencilArea::StencilAreaModel::StencilAreaBuilder(
                                                                                           "dundee_west_ward",
                                                                                           *m_pDundeeWestPalette,
                                                                                           dundeeWest,
                                                                                           Eegeo::Rendering::StencilMapLayerMask::Buildings,
                                                                                           150.f)
        .Build();
    }
}
