// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RoutingServiceExample.h"
#include "RouteBuilder.h"
#include "VectorMath.h"
#include "RouteStyle.h"
#include "CameraHelpers.h"
#include "GlobeCameraController.h"
#include "EcefTangentBasis.h"
#include "RoutingRequestBuilder.h"
#include "JsonRouteParser.h"
#include "InteriorSelectionModel.h"
#include "InteriorTransitionModel.h"
#include "InteriorsModel.h"
#include "InteriorInteractionModel.h"
#include "IRoutingServiceExampleViewFactory.h"

namespace Examples
{
RoutingServiceExample::RoutingServiceExample(Eegeo::Routes::RouteService& routeService,
                                             const Eegeo::Routes::Webservice::RoutingRequestBuilder& requestBuilder,
                                             Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                             Eegeo::EegeoWorld& world,
                                             Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                                             IRoutingServiceExampleViewFactory& routingServiceViewFactory)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_requestBuilder(requestBuilder)
    , m_webRequestFactory(webRequestFactory)
	, m_routeService(routeService)
	, m_world(world)
    , m_routeReceivedCallback(this, &RoutingServiceExample::RouteReceivedCallback)
    , m_enteredInterior(false)
    , m_routingServiceViewFactory(routingServiceViewFactory)
    , m_moveUpHandler(this, &RoutingServiceExample::MoveUp)
    , m_moveDownHandler(this, &RoutingServiceExample::MoveDown)
    , m_getRouteHandler(this, &RoutingServiceExample::GetRoute)
    , m_toggleExpandedHandler(this, &RoutingServiceExample::ToggleExpand)
{
	Eegeo::Space::EcefTangentBasis cameraInterestBasis;

	Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
	    Eegeo::Space::LatLong::FromDegrees(56.4600889,-2.9782014).ToECEF(),
        0.0f,
	    cameraInterestBasis);

	pCameraController->SetView(cameraInterestBasis, 400.0f);

    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
    m_pInteriorSelectionModel = &interiorsPresentationModule.GetInteriorSelectionModel();
    m_pInteriorInteractionModel = &interiorsPresentationModule.GetInteriorInteractionModel();

    m_routeThicknessPolicy.SetScaleFactor(0.25f);
}
    
void RoutingServiceExample::EnterInterior(const Eegeo::Resources::Interiors::InteriorId& interiorId)
{
    m_pInteriorSelectionModel->SelectInteriorId(interiorId);
    m_enteredInterior = true;
}
    
void RoutingServiceExample::ExitInterior()
{
    m_pInteriorSelectionModel->ClearSelection();
    m_enteredInterior = false;
}

void RoutingServiceExample::RouteReceivedCallback(Eegeo::Web::IWebResponse& webResponse)
{
    const std::vector<Byte> *responseData = webResponse.TransferResourceDataOwnership();
    size_t responseSize = responseData->size();
    std::string responseString(reinterpret_cast<const char*>(responseData->data()), responseSize);
    Eegeo_DELETE responseData;
    
    Eegeo::Routes::Webservice::JsonRouteParser resultParser(m_world.GetWorkPool());
    Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone, Eegeo::Rendering::LayerIds::InteriorEntities, true);
    // this will asynchronously parse the result and add the resulting route to m_routeService
    resultParser.CreateRouteFromJSON(responseString, m_routeService, routeStyle);
}
    
void RoutingServiceExample::GetRoute()
{
    // destroy any existing routes
    m_routeService.DestroyAllRoutes();
    
    // Query the service for a route
    Eegeo::Space::LatLongAltitude start = Eegeo::Space::LatLongAltitude::FromDegrees(56.4602302, -2.9785768, 0);
    int startLevel = 0;
    Eegeo::Space::LatLongAltitude end = Eegeo::Space::LatLongAltitude::FromDegrees(56.4600344, -2.9783117, 0);
    int endLevel = 2;
    
    std::string apiCall = m_requestBuilder.CreateRouteRequestWithLevels(start, startLevel, end, endLevel);
    Eegeo::Web::IWebLoadRequest* webRequest = m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, apiCall, m_routeReceivedCallback)
        .SetShouldCacheAggressively(false)
        .Build();
    webRequest->Load();
}

void RoutingServiceExample::Update(float dt)
{
	//Defer creating the routes until the loading state is over.
	if(m_world.Initialising())
	{
		return;
	}
    
    if (!m_enteredInterior)
    {
        Eegeo::Resources::Interiors::InteriorId interiorId("westport_house");
        EnterInterior(interiorId);
        CreateAndBindUI();
    }
    
    // Update the altitude based scaler with the current camera's altitude.
    float altitude = GetGlobeCameraController().GetRenderCamera().GetAltitude();
    m_routeThicknessPolicy.SetAltitude(altitude);
}

void RoutingServiceExample::Suspend()
{
	//Destroy all of the routes...
    ExitInterior();
    m_routeService.DestroyAllRoutes();
    delete m_pRoutingServiceView;
}
    
void RoutingServiceExample::CreateAndBindUI()
{
    m_pRoutingServiceView = m_routingServiceViewFactory.CreateRoutingServiceExampleView();
    
    m_pRoutingServiceView->AddGetRouteHandler(m_getRouteHandler);
    m_pRoutingServiceView->AddMoveUpHandler(m_moveUpHandler);
    m_pRoutingServiceView->AddMoveDownHandler(m_moveDownHandler);
    m_pRoutingServiceView->AddToggleExpandedHandler(m_toggleExpandedHandler);
}
    
void RoutingServiceExample::ToggleExpand()
{
    m_pInteriorInteractionModel->ToggleExpanded();
}

void RoutingServiceExample::MoveUp()
{
    const Eegeo::Resources::Interiors::InteriorsModel* model = m_pInteriorInteractionModel->GetInteriorModel();
    
    if (model)
    {
        int floorCount = model->GetFloorCount();
        int currentFloor = m_pInteriorInteractionModel->GetSelectedFloorIndex();
        m_pInteriorInteractionModel->SetSelectedFloorIndex(std::min(currentFloor + 1, floorCount - 1));
    }
}
    
void RoutingServiceExample::MoveDown()
{
    const Eegeo::Resources::Interiors::InteriorsModel* model = m_pInteriorInteractionModel->GetInteriorModel();
    
    if (model)
    {
        int currentFloor = m_pInteriorInteractionModel->GetSelectedFloorIndex();
        m_pInteriorInteractionModel->SetSelectedFloorIndex(std::max(currentFloor - 1, 0));
    }
}
}
