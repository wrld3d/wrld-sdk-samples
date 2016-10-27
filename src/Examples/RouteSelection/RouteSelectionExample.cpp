// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "RouteSelectionExample.h"
#include "RouteBuilder.h"
#include "VectorMath.h"
#include "RouteStyle.h"
#include "CameraHelpers.h"
#include "GlobeCameraController.h"
#include "EcefTangentBasis.h"
#include "TerrainRayPicker.h"
#include "RouteSelectionHelper.h"


using namespace Eegeo;
using namespace Eegeo::Routes;

namespace Examples
{
RouteSelectionExample::RouteSelectionExample(Eegeo::Routes::RouteService& routeService,
                                             Eegeo::Routes::RouteRepository& routeRepository,
                                             Eegeo::EegeoWorld& world,
                                             Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                             const Eegeo::Collision::ICollisionBvhProvider& collisionMeshResourceProvider,
                                             Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
	, m_routeService(routeService)
    , m_routeRepository(routeRepository)
	, m_world(world)
	, m_createdRoutes(false)
    , m_selectedRoute(-1)
    , m_indexBeforeSelectedSegment(-1)
    , m_displayedRouteToSourceRouteMap()
{
	Eegeo::Space::EcefTangentBasis cameraInterestBasis;

	Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
	    Eegeo::Space::LatLong::FromDegrees(37.793348, -122.399035).ToECEF(),
	    354.824249f,
	    cameraInterestBasis);

	pCameraController->SetView(cameraInterestBasis, 1374.298706f);
    m_pRayPicker = new Eegeo::Resources::Terrain::Collision::TerrainRayPicker(terrainHeightProvider, collisionMeshResourceProvider);

    //An arbitrarily selected altitude for the route visualisation.
    const float altitudeMeters = 3.f;
    std::vector<Eegeo::Space::LatLongAltitude> route1Pts =
    {
        Space::LatLongAltitude::FromDegrees(37.788567128006434, -122.40233566664128, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.789290007482009, -122.40145482447454, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.790119971492516, -122.40047234667318, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.790682199880564, -122.3996931401411,  altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.791030243881721, -122.39925271905773, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.791753099261179, -122.39827024125637, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.792475947568853, -122.39738939908965, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.79335941923005 , -122.39630528565367, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.794082251822473, -122.39552607912158, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.794751534954337, -122.3946791154997,  altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.795420812023117, -122.39393378751247, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.796063312304966, -122.39464523695486, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.796812888904768, -122.39525505076259, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.797375066363401, -122.39579710748055, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.798017549648918, -122.39644079983316, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.79857971793993 , -122.39701673509603, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.799141881952686, -122.39749103472427, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.799837888612402, -122.39813472707688, altitudeMeters)
    };
    
    std::vector<Eegeo::Space::LatLongAltitude> route2Pts =
    {
        Space::LatLongAltitude::FromDegrees(37.788567128006434, -122.40233566664128, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.789290007482009, -122.40145482447454, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.790119971492516, -122.40047234667318, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.790682199880564, -122.3996931401411,  altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.792101138218008, -122.39982865432059, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.793252332318616, -122.40009968267958, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.794162566118423, -122.40023519685907, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.79512633085983 , -122.40043846812831, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.796009770828235, -122.40057398230782, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.796812888904768, -122.40074337503219, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.797749848959029, -122.40091276775655, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.798660027346543, -122.40108216048094, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.798767106419547, -122.39989641141034, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.798900955042512, -122.39871066233974, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.799141881952686, -122.39749103472427, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.799837888612402, -122.39813472707688, altitudeMeters)
    };
    
    std::vector<Eegeo::Space::LatLongAltitude> route3Pts =
    {
        Space::LatLongAltitude::FromDegrees(37.788567128006434, -122.40233566664128, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.787576503906507, -122.40352141571185, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.788941955283917, -122.40372468698109, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.789879015159492, -122.40389407970548, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.790869608392583, -122.40413122951961, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.791753099261179, -122.40419898660936, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.792716895433223, -122.40443613642348, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.793627135829595, -122.40470716478245, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.794483822429157, -122.40487655750685, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.795474353926693, -122.40501207168633, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.796223936502336, -122.40521534295557, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.797053822625188, -122.40538473567995, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.797990779623589, -122.40552024985945, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.798124629653245, -122.40470716478245, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.798231709502339, -122.40386020116061, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.798392328984953, -122.40297935899387, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.7984726385953  , -122.40220015246176, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.798660027346543, -122.40108216048094, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.798767106419547, -122.39989641141034, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.798900955042512, -122.39871066233974, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.799141881952686, -122.39749103472427, altitudeMeters),
        Space::LatLongAltitude::FromDegrees(37.799837888612402, -122.39813472707688, altitudeMeters)
    };
    

    m_sourceRoutePts = { route1Pts, route2Pts, route3Pts };
    const Eegeo::v4 routeRed(1, 0, 0, 0.5);
    const Eegeo::v4 routeGreen(0, 1, 0, 0.5f);
    const Eegeo::v4 routeBlue(0, 0, 1, 0.5f);
    m_routeColors = { routeRed, routeGreen, routeBlue };
}

void RouteSelectionExample::CreateRoutes()
{
    const float halfWidth = 5.f;
    const float routeSpeedMetersPerSecond = 40.f;
    Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone);
    
    RouteBuilder builder;
    
    // Draw unselected routes
    for (size_t i=0; i<m_sourceRoutePts.size(); i++)
    {
        if (m_selectedRoute == i)
        {
            continue;
        }

        builder.Start(m_routeColors[i], halfWidth, routeSpeedMetersPerSecond, Routes::Road);
        for (size_t j = 0; j < m_sourceRoutePts[i].size(); j++)
        {
            builder.AddPoint(m_sourceRoutePts[i][j]);
        }
        std::vector<RouteVertex> points = builder.FinishRoute();
        Route* route = m_routeService.CreateRoute(points, routeStyle, false);
        m_routes.push_back(route);
        m_displayedRouteToSourceRouteMap.push_back(i);
    }
    
    if (m_selectedRoute != -1)
    {
        // Add selected route with solid color
        Eegeo::v4 selectedSegmentColor(1, 1, 1, 1.0f);
        Eegeo::v4 baseColor = m_routeColors[m_selectedRoute];
        baseColor.SetW(1.0);

        Eegeo::v4 startColor = baseColor;
        if (m_indexBeforeSelectedSegment == 0)
        {
            startColor = selectedSegmentColor;
        }
        builder.Start(startColor, halfWidth, routeSpeedMetersPerSecond, Routes::Road);
        for (size_t j = 0; j < m_sourceRoutePts[m_selectedRoute].size(); j++)
        {
            builder.AddPoint(m_sourceRoutePts[m_selectedRoute][j]);
            // change the color for the selected segment
            if (m_indexBeforeSelectedSegment == j)
            {
                builder.ChangeColor(selectedSegmentColor);
            }
            else if (m_indexBeforeSelectedSegment + 1 == j)
            {
                builder.ChangeColor(baseColor);
            }
        }
        std::vector<RouteVertex> points = builder.FinishRoute();
        Route* route = m_routeService.CreateRoute(points, routeStyle, false);
        m_routes.push_back(route);
        m_displayedRouteToSourceRouteMap.push_back(m_selectedRoute);
    }
}

void RouteSelectionExample::Update(float dt)
{
	//Defer creating the routes until the loading state is over.
	if(m_world.Initialising())
	{
		return;
	}

	if(!m_createdRoutes)
	{
        CreateRoutes();
		m_createdRoutes = true;
	}
}
    
void RouteSelectionExample::Event_TouchTap(const AppInterface::TapData& data)
{
    Eegeo::Camera::RenderCamera renderCamera(GetGlobeCameraController().GetRenderCamera());
        
    float screenPixelX = data.point.GetX();
    float screenPixelY = data.point.GetY();
        
    Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
    Eegeo::dv3 rayDirection;
    Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
        
    Eegeo::dv3 ecefIntersectionPoint;
    double intersectionParam;
    bool rayPick = m_pRayPicker->TryGetRayIntersection(rayOrigin, rayDirection, ecefIntersectionPoint, intersectionParam);
    if(rayPick)
    {
        std::vector<const Routes::Route*> routes = m_routeRepository.GetRoutes();

        RouteSelectionHelper::RouteHitTestResult result = RouteSelectionHelper::GetRouteClosestToPoint(routes, ecefIntersectionPoint);
        if (result.routeIndex != -1)
        {
            m_selectedRoute = m_displayedRouteToSourceRouteMap[result.routeIndex];
            m_indexBeforeSelectedSegment = result.pointIndexBeforeClosestPoint;
            
            DestroyRoutes();
            CreateRoutes();
        }
    }
        
    GlobeCameraExampleBase::Event_TouchTap(data);
}
    
void RouteSelectionExample::DestroyRoutes()
{
	for(std::vector<Route*>::iterator i = m_routes.begin(); i != m_routes.end(); ++ i)
	{
		m_routeService.DestroyRoute(*i);
	}

	m_routes.clear();
    m_displayedRouteToSourceRouteMap.clear();
}

void RouteSelectionExample::Suspend()
{
    DestroyRoutes();
}
}
