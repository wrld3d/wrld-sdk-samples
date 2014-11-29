// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__NavigationGraphExample__
#define __ExampleApp__NavigationGraphExample__

#include "IExample.h"

#include "NavigationGraphRepository.h"
#include "NavigationGraphAddedCallback.h"
#include "NavigationGraphRemovalCallback.h"
#include "NavigationGraph.h"
#include "DebugRendering.h"
#include "GLState.h"

namespace Examples
{
class NavigationGraphExample : public IExample
{
private:
	typedef std::map<const Eegeo::Resources::Roads::Navigation::NavigationGraph*, Eegeo::DebugRendering::DebugRenderable*> MapType;

	struct Added : public Eegeo::Resources::Roads::Navigation::INavigationGraphAddedCallback
	{
		NavigationGraphExample& m_example;
		Added(NavigationGraphExample& example):m_example(example) {}
		void operator()(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph)
		{
			m_example.HandleAddedGraph(navGraph);
		}
	};

	struct Removed : public Eegeo::Resources::Roads::Navigation::INavigationGraphRemovalCallback
	{
		NavigationGraphExample& m_example;
		Removed(NavigationGraphExample& example):m_example(example) {}
		void operator()(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph)
		{
			m_example.HandleRemovedGraph(navGraph);
		}
	};


	void HandleAddedGraph(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph);
	void HandleRemovedGraph(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph);

    Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pCameraController;
	Eegeo::Resources::Roads::Navigation::NavigationGraphRepository& m_navigationGraphRepository;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

	Added m_addedHandler;
	Removed m_removedHandler;
	MapType m_navGraphsToVisualisers;

public:
	NavigationGraphExample(Eegeo::Resources::Roads::Navigation::NavigationGraphRepository& navigationGraphRepository,
	                       Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController);

	static std::string GetName()
	{
		return "NavigationGraphExample";
	}
	std::string Name() const
	{
		return GetName();
	}
    
	void Start();
	void Update(float dt) {}
	void Draw();
	void Suspend();
    const Eegeo::Camera::RenderCamera& GetRenderCamera() const;
    Eegeo::dv3 GetInterestPoint() const;
};
}


#endif /* defined(__ExampleApp__NavigationGraphExample__) */
