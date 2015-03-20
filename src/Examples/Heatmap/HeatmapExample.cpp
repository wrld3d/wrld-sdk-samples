// Copyright eeGeo Ltd 2015, All Rights Reserved

#include "HeatmapExample.h"
#include "HeatmapController.h"
#include "HeatmapModel.h"
#include "VectorMath.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "GlobeCameraController.h"
#include "LatLongAltitude.h"
#include "StencilMapLayerMask.h"

namespace Examples
{
    HeatmapExample::HeatmapExample(
                                       Eegeo::Data::Heatmaps::HeatmapController& heatmapController,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                                       Eegeo::Helpers::ITextureFileLoader& textureLoader
                                   )
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_heatmapController(heatmapController)
    , m_textureLoader(textureLoader)
    , m_pSfCrimeHeatmap(NULL)
    {
        Eegeo::Space::EcefTangentBasis cameraInterestBasis;
        
        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
                                                                          Eegeo::Space::LatLong::FromDegrees(37.793348, -122.399035).ToECEF(),
                                                                          354.824249f,
                                                                          cameraInterestBasis);
        
        pCameraController->SetView(cameraInterestBasis, 1900.0f);
    }
    
    void HeatmapExample::Start()
    {
        bool heatmapResult = m_textureLoader.LoadTexture(m_heatmapTexture, "heatmap_example/sf-heatmap.png", true);
        Eegeo_ASSERT(heatmapResult, "Unable to load heatmap_example/sf-heatmap.png");
        
        bool gradientResult = m_textureLoader.LoadTexture(m_gradientTexture, "heatmap_example/gradient.png", true);
        Eegeo_ASSERT(gradientResult, "Unable to load heatmap_example/gradient.png");
        
        m_pSfCrimeHeatmap = Eegeo::Data::Heatmaps::HeatmapModel::HeatmapBuilder(
                                                                         "example_heatmap",
                                                                         m_heatmapTexture.textureId,
                                                                         m_gradientTexture.textureId,
                                                                         Eegeo::Space::LatLong::FromDegrees(37.8137250395396194, -122.5163426427749869),
                                                                         Eegeo::Space::LatLong::FromDegrees(37.7018266572250056,-122.3670702007672872)
                                                                         )
                                                                    .Alpha(0.5)
                                                                    .MaxValue(24)
                                                                    .Layer(Eegeo::Rendering::StencilMapLayerMask::Buildings)
                                                                    .Build();
        
        m_heatmapController.Add(*m_pSfCrimeHeatmap);
    }
    
    void HeatmapExample::Suspend()
    {
        m_heatmapController.Remove(*m_pSfCrimeHeatmap);
        delete m_pSfCrimeHeatmap;
        m_pSfCrimeHeatmap = NULL;
        
        if (m_heatmapTexture.textureId != 0)
        {
            Eegeo_GL(glDeleteTextures(1, &m_heatmapTexture.textureId));
        }
        
        if (m_gradientTexture.textureId != 0)
        {
            Eegeo_GL(glDeleteTextures(1, &m_gradientTexture.textureId));
        }
    }
    
    void HeatmapExample::Update(float dt)
    {
    }
    
    void HeatmapExample::Draw()
    {
    }
    
    void HeatmapExample::Event_TouchPan(const AppInterface::PanData& data)
    {
        GlobeCameraExampleBase::Event_TouchPan(data);
    }
    
    void HeatmapExample::Event_TouchDown(const AppInterface::TouchData& data)
    {
        GlobeCameraExampleBase::Event_TouchDown(data);
    }
    
    void HeatmapExample::Event_TouchUp(const AppInterface::TouchData& data)
    {
        GlobeCameraExampleBase::Event_TouchUp(data);
    }
}
