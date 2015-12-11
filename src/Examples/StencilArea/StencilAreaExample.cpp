// Copyright eeGeo Ltd 2015, All Rights Reserved

#include "StencilAreaExample.h"
#include "StencilAreaController.h"
#include "StencilAreaPaletteModel.h"
#include "VectorMath.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "GlobeCameraController.h"


#include "GeoJSONDocument.h"
#include "GeoJSONObject.h"
#include "FeatureCollection.h"
#include "Feature.h"
#include "MultiPolygon.h"
#include "LinearRing.h"
#include "PolygonData.h"

#include "IWebLoadRequest.h"

#include "IAlertBoxFactory.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

namespace Examples
{
    namespace
    {
        typedef std::vector<std::vector<Eegeo::Space::LatLongAltitude> > TDistricts;

        const void ConvertToDistrict(const Eegeo::Data::GeoJSON::PolygonData& data, TDistricts& districts)
        {
            const Eegeo::Data::GeoJSON::LinearRing& ring = data.GetExteriorRing();
            std::vector<Eegeo::Space::LatLongAltitude> ringLLA;
            ringLLA.reserve(ring.GetRing().size());
            for (std::vector<Eegeo::dv2>::const_iterator it = ring.GetRing().begin(); it != ring.GetRing().end()-1; ++it)
            {
                const Eegeo::dv2& longLat = *it;
                ringLLA.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(longLat.GetY(), longLat.GetX(), 0.0));
            }
            districts.push_back(ringLLA);
        }
    }
    
    StencilAreaExample::StencilAreaExample(
                                       Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                       Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                       Eegeo::Data::StencilArea::StencilAreaController& StencilAreaController,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_controller(StencilAreaController)
    , m_webLoadRequestFactory(webRequestFactory)
    , m_nativeUIFactories(nativeUIFactories)
    , m_pAlertBoxDismissedHandler(NULL)
    , m_handler(this, &StencilAreaExample::HandleRequest)
    {
        Eegeo::Space::EcefTangentBasis cameraInterestBasis;
        
        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
                                                                          Eegeo::Space::LatLong::FromDegrees(37.793348, -122.399035).ToECEF(),
                                                                          354.824249f,
                                                                          cameraInterestBasis);
        
        pCameraController->SetView(cameraInterestBasis, 1900.0f);
    }
    
    void StencilAreaExample::Start()
    {
        m_palettes.push_back(Eegeo::Data::StencilArea::StencilAreaPaletteModel::StencilAreaPaletteBuilder("0", Eegeo::v4(0.f, 0.f/255.f, 255.f/255.f, 0.4f)).Build());
        m_palettes.push_back(Eegeo::Data::StencilArea::StencilAreaPaletteModel::StencilAreaPaletteBuilder("1", Eegeo::v4(0.f, 128.f/255.f, 255.f/255.f, 0.4f)).Build());
        m_palettes.push_back(Eegeo::Data::StencilArea::StencilAreaPaletteModel::StencilAreaPaletteBuilder("2", Eegeo::v4(0.f, 255.f/255.f, 128.f/255.f, 0.4f)).Build());
        m_palettes.push_back(Eegeo::Data::StencilArea::StencilAreaPaletteModel::StencilAreaPaletteBuilder("3", Eegeo::v4(0.f, 255.f/255.f, 0.f/255.f, 0.4f)).Build());
        m_palettes.push_back(Eegeo::Data::StencilArea::StencilAreaPaletteModel::StencilAreaPaletteBuilder("4", Eegeo::v4(128.f/255.f, 255.f/255.f, 0.f, 0.4f)).Build());
        m_palettes.push_back(Eegeo::Data::StencilArea::StencilAreaPaletteModel::StencilAreaPaletteBuilder("5", Eegeo::v4(255.f/255.f, 255.f/255.f, 0.f, 0.4f)).Build());
        m_palettes.push_back(Eegeo::Data::StencilArea::StencilAreaPaletteModel::StencilAreaPaletteBuilder("6", Eegeo::v4(255.f/255.f, 128.f/255.f, 0.f, 0.4f)).Build());
        m_palettes.push_back(Eegeo::Data::StencilArea::StencilAreaPaletteModel::StencilAreaPaletteBuilder("7", Eegeo::v4(255.f/255.f, 0.f/255.f, 0.f, 0.4f)).Build());

        // Asynchronously fetch san francisco district polygons in GeoJSON format
        const std::string geoJsonURL = "https://eegeo-static.s3.amazonaws.com/mobile-sdk-harness-data/san-francisco-districts.geojson.gz";
    
        Eegeo::Web::IWebLoadRequest* pRequest = m_webLoadRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, geoJsonURL, m_handler).Build();
        m_pendingWebRequestsContainer.InsertRequest(*pRequest);
        pRequest->Load();
    }
    
    void StencilAreaExample::HandleRequest(Eegeo::Web::IWebResponse& webResponse)
    {
        m_pendingWebRequestsContainer.RemoveRequest(webResponse);
        
        if (!webResponse.IsSucceeded())
        {
            Eegeo_ASSERT(m_pAlertBoxDismissedHandler == NULL, "AlertBoxDismissedHandler not NULL");
            
            m_pAlertBoxDismissedHandler = Eegeo_NEW(Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<StencilAreaExample>(this, &StencilAreaExample::HandleAlertBoxDismissed));
            
            m_nativeUIFactories.AlertBoxFactory().CreateSingleOptionAlertBox("Unabled to Retrieve Stencil Data",
                                                                             "Ensure network connection is enabled and retry the example",
                                                                             *m_pAlertBoxDismissedHandler);
            
            return;
        }
        
        size_t resultSize = webResponse.GetBodyData().size();
        std::string json( reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize );
        
        const std::string document(json);
        TDistricts districtOutlines;
        
        // Parse polygons in GeoJSON to vector of LatLongAltitudes
        Eegeo::Data::GeoJSON::GeoJSONDocument geoJsonDocument(document);
        const Eegeo::Data::GeoJSON::GeoJSONObject& obj = geoJsonDocument.Parse();
        const Eegeo::Data::GeoJSON::FeatureCollection& featureCollection = obj.AsFeatureCollection();
        for (int i = 0; i < featureCollection.GetNumFeatures(); ++i)
        {
            const Eegeo::Data::GeoJSON::Feature& feature = featureCollection.GetFeatureAt(i);
            const Eegeo::Data::GeoJSON::MultiPolygon& multiPolygon = feature.GetGeometry().AsMultiPolygon();
            
            for (int j = 0; j < multiPolygon.GetNumPolygons(); ++j)
            {
                const Eegeo::Data::GeoJSON::PolygonData& polygonData = multiPolygon.GetPolygonAt(j);
                ConvertToDistrict(polygonData, districtOutlines);
            }
        }
        
        // outlineAltitudeOffsets are terrain heights (from ITerrainHeightLookup) at outline centroids
        const float outlineAltitudeOffsets[] = {4.6849f, 43.7334f, 2.6585f, 90.3125f, 75.8662f, 102.4601f, 44.9174f, 66.8289f, 75.8662f, 114.1066f, 133.8441f, 133.8441f, 62.8317f, 114.9324f, 118.5516f, 95.9089f, 95.5290f, 74.7607f, 51.2341f, 75.5237f, 25.9373f, 73.1260f, 25.9373f, 150.2888f, 89.1085f, 51.5655f, 114.1066f, 100.2126f, 70.4457f, 97.8528f, 20.2937f, 60.0656f, 85.6781f, 104.2594f, 99.6410f, 116.9411f, 214.2081f, 96.4998f, 210.9473f, 253.4782f, 153.0558f, 83.6688f, 96.4998f, 201.9720f, 131.3402f, 179.9836f, 253.4782f, 71.6693f, 103.3735f, 97.8528f, 182.9989f, 198.2886f, 198.2886f, 210.7315f, 214.2081f, 68.3862f, 180.9597f, 95.9089f, 114.9324f, 89.3736f, 46.2380f, 46.2380f, 9.2913f, 38.6931f, 66.5644f, 68.5033f, 59.7500f, 87.9804f, 87.3458f, 180.5154f, 31.2882f, 85.6422f, 29.3151f, 86.2003f, 84.5633f, 24.2386f, 68.4895f, 67.2186f, 65.6160f, 93.8255f, 65.5967f, 93.8255f, 49.4197f, 102.0758f, 48.5513f, 32.5650f, 32.5650f, 18.5832f, 15.9373f, 65.6160f, 145.7743f, 153.0558f, 24.2386f, 83.5538f, 21.3396f, 102.0758f, 84.0589f, 45.1286f, 18.5832f, 60.8095f, 65.5967f, 78.1820f, 64.3211f, 84.5633f, 87.0487f, 27.0241f, 38.6449f, 9.0000f, 87.9804f, 68.0252f, 78.8772f, 86.1506f, 10.5388f, 50.2124f, 63.0208f, 24.9978f, 68.6975f, 34.0320f, 81.3867f, 73.4589f, 99.1616f, 74.4662f, 29.0826f, 67.2422f, 24.4150f, 37.3627f, 74.5852f, 51.0264f, 7.7920f, 58.2490f, 57.2189f, 65.7713f, 86.5244f, 3.9804f, 28.7383f, 38.1068f, 57.2189f, 50.3965f, 74.5852f, 31.1714f, 3.9804f, 6.0546f, 99.1616f, 18.1432f, 104.0983f, 17.7228f, 16.0400f, 63.0100f, 13.3495f, 21.9093f, 16.0400f, 38.7216f, 86.5244f, 68.5033f, 54.6419f, 67.0218f, 24.3175f, 15.2920f, 50.4095f, 10.6337f, 51.0376f};
        
        const float heightOfStencilAreaInM = 250.f;
        
        // Create stencil area extrusions for each district polygon, assigning to a random color palette.
        int districtCount = 0;
        for (TDistricts::iterator it = districtOutlines.begin(); it != districtOutlines.end(); ++it)
        {
            int randomPalette = int((rand() % m_palettes.size()));
            const Eegeo::Data::StencilArea::StencilAreaPaletteModel& paletteModel = *(m_palettes[randomPalette]);
            const std::vector<Eegeo::Space::LatLongAltitude>& outline = *it;
            Eegeo::Data::StencilArea::StencilAreaModel* pModel = Eegeo::Data::StencilArea::StencilAreaModel::StencilAreaBuilder("stencil_area",
                                                                                                                                paletteModel,
                                                                                                                                outline,
                                                                                                                                Eegeo::Rendering::StencilMapLayerMask::Buildings,
                                                                                                                                outlineAltitudeOffsets[districtCount]+heightOfStencilAreaInM)
            .Build();
            m_outlines.push_back(pModel);
            m_controller.Add(*pModel);
            ++districtCount;
        }
    }
    
    void StencilAreaExample::Suspend()
    {
        for (TOutlines::iterator it = m_outlines.begin(); it != m_outlines.end(); ++it)
        {
            m_controller.Remove(**it);
            delete *it;
        }
        m_outlines.clear();
        for(TPalettes::iterator it = m_palettes.begin(); it != m_palettes.end(); ++it)
        {
            delete *it;
        }
        m_palettes.clear();
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
    
    void StencilAreaExample::HandleAlertBoxDismissed()
    {
        if (m_pAlertBoxDismissedHandler != NULL)
        {
            Eegeo_DELETE m_pAlertBoxDismissedHandler;
            m_pAlertBoxDismissedHandler = NULL;
        }
        
        return;
    }
}
