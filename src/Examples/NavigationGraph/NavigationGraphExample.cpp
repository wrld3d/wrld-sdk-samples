// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "NavigationGraphExample.h"
#include "NavigationGraphRoad.h"
#include "CameraHelpers.h"
#include "DebugRenderable.h"
#include "RenderCamera.h"
#include "GLState.h"
#include "GlobeCameraController.h"

#include <limits>

using namespace Eegeo::Rendering;
using namespace Eegeo::DebugRendering;
using namespace Eegeo::Resources::Roads::Navigation;

namespace
{
DebugRenderable* CreateVisualisation(const Eegeo::v3& roadColor,
                                     const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph);
}

namespace Examples
{
NavigationGraphExample::NavigationGraphExample(NavigationGraphRepository& navigationGraphRepository,
        Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
	, m_navigationGraphRepository(navigationGraphRepository)
	,m_addedHandler(*this)
	,m_removedHandler(*this)
{
}

void NavigationGraphExample::Start()
{
	srand(static_cast<unsigned>(time(0))); //for colors
	m_navigationGraphRepository.RegisterAddedCallback(&m_addedHandler);
	m_navigationGraphRepository.RegisterRemovalCallback(&m_removedHandler);
}

void NavigationGraphExample::Suspend()
{
	m_navigationGraphRepository.UnregisterAddedCallback(&m_addedHandler);
	m_navigationGraphRepository.UnregisterRemovalCallback(&m_removedHandler);
    
    
    
}

void NavigationGraphExample::Draw()
{
    Eegeo::Rendering::GLState glState;
    glState.InvalidateAll();
    
	for(MapType::const_iterator it = m_navGraphsToVisualisers.begin(); it != m_navGraphsToVisualisers.end(); ++ it)
	{
		const NavigationGraph &navGraph = *it->first;
		DebugRenderable &renderable = *it->second;

		Eegeo::dv3 ecefPosition = navGraph.GetCellInfo().GetFaceCentreECEF() + Eegeo::dv3::FromSingle(navGraph.GetUpECEF() * 2.0f);
        
        Eegeo::Camera::RenderCamera renderCamera(GetGlobeCameraController().GetRenderCamera());
		Eegeo::v3 m_cameraRelativePosition = Eegeo::Camera::CameraHelpers::CameraRelativePoint(ecefPosition, renderCamera.GetEcefLocation());
		renderable.Draw(m_cameraRelativePosition, renderCamera, glState);
	}
}

void NavigationGraphExample::HandleAddedGraph(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph)
{
	Eegeo::v3 roadColor((rand()%256)/256.0f, (rand()%256)/256.0f, (rand()%256)/256.0f);
	m_navGraphsToVisualisers[&navGraph] = CreateVisualisation(roadColor, navGraph);
}

void NavigationGraphExample::HandleRemovedGraph(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph)
{
	delete m_navGraphsToVisualisers[&navGraph];
	m_navGraphsToVisualisers.erase(m_navGraphsToVisualisers.find(&navGraph));
}

}

namespace
{
DebugRenderable* CreateVisualisation(const Eegeo::v3& roadColor,
                                     const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph)
{
	DebugRenderable* renderable = new DebugRenderable(NULL);

	const NavigationGraph::TRoadsVector& roads = navGraph.GetRoads();

	const Eegeo::v3& roadColorStart = roadColor;
	const Eegeo::v3& roadColorEnd = roadColor;

	std::vector<Eegeo::v3> verts;
	std::vector<Eegeo::v3> colors;
	std::vector<Eegeo::v2> uvs;
	std::vector<u16> indices;

	const Eegeo::v3& up = navGraph.GetUpECEF();

	for (NavigationGraph::TRoadsVector::const_iterator iter = roads.begin(); iter != roads.end(); ++iter)
	{
		const NavigationGraphRoad& road = **iter;

		const std::vector<Eegeo::v3>& roadVerts = road.GetVertices();
		const float halfWidth = road.GetHalfWidth();

		const float paramScale = 1.f / (roadVerts.size() - 1);

		for (int i = 1; i < roadVerts.size(); ++i)
		{
			Eegeo::v3 v0 = roadVerts[i-1];
			Eegeo::v3 v1 = roadVerts[i];
			Eegeo::v3 segmentColorStart = Eegeo::v3::Lerp(roadColorStart, roadColorEnd, (i-1)*paramScale);
			Eegeo::v3 segmentColorEnd = Eegeo::v3::Lerp(roadColorStart, roadColorEnd, i*paramScale);

            Eegeo_ASSERT(verts.size() + 3 <= std::numeric_limits<u16>::max());
			const u16 indexBase = static_cast<u16>(verts.size());
			Eegeo::v3 dir = (v1 - v0).Norm();
			Eegeo::v3 right = Eegeo::v3::Cross(up, dir).Norm();

			verts.push_back(v0 + right*halfWidth);
			verts.push_back(v0 - right*halfWidth);
			verts.push_back(v1 + right*halfWidth);
			verts.push_back(v1 - right*halfWidth);

			colors.push_back(segmentColorStart);
			colors.push_back(segmentColorStart);
			colors.push_back(segmentColorEnd);
			colors.push_back(segmentColorEnd);

			uvs.push_back(Eegeo::v2(0.f, 0.f));
			uvs.push_back(Eegeo::v2(0.f, 1.f));
			uvs.push_back(Eegeo::v2(1.f, 0.f));
			uvs.push_back(Eegeo::v2(1.f, 0.f));
			uvs.push_back(Eegeo::v2(0.f, 1.f));
			uvs.push_back(Eegeo::v2(1.f, 1.f));

			indices.push_back(indexBase + 0);
			indices.push_back(indexBase + 1);
			indices.push_back(indexBase + 2);
			indices.push_back(indexBase + 2);
			indices.push_back(indexBase + 1);
			indices.push_back(indexBase + 3);
		}
	}

    Eegeo::Rendering::GLState glState;
    glState.SetDefaultState();
    
	renderable->Build(verts, colors, indices, uvs, glState);
	return renderable;
}
}
