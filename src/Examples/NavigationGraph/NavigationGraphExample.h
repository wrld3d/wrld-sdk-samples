// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__NavigationGraphExample__
#define __ExampleApp__NavigationGraphExample__

#include "GlobeCameraExampleBase.h"

#include "NavigationGraphRepository.h"
#include "NavigationGraphAddedCallback.h"
#include "NavigationGraphRemovalCallback.h"
#include "NavigationGraph.h"
#include "DebugRendering.h"
#include "GLState.h"

namespace Examples
{
class NavigationGraphExample : public GlobeCameraExampleBase
{
private:
	typedef std::map<const Eegeo::Resources::Roads::Navigation::NavigationGraph*, Eegeo::DebugRendering::DebugRenderable*> MapType;

	struct Added : public Eegeo::Resources::Roads::Navigation::INavigationGraphAddedCallback
	{
		Added(NavigationGraphExample& example):m_example(example) {}
		void operator()(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph)
		{
			m_example.HandleAddedGraph(navGraph);
		}
    private:
        NavigationGraphExample& m_example;
	};

	struct Removed : public Eegeo::Resources::Roads::Navigation::INavigationGraphRemovalCallback
	{
		Removed(NavigationGraphExample& example):m_example(example) {}
		void operator()(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph)
		{
			m_example.HandleRemovedGraph(navGraph);
		}
    private:
        NavigationGraphExample& m_example;
	};


	void HandleAddedGraph(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph);
	void HandleRemovedGraph(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph);

    
	Eegeo::Resources::Roads::Navigation::NavigationGraphRepository& m_navigationGraphRepository;

	Added m_addedHandler;
	Removed m_removedHandler;
	MapType m_navGraphsToVisualisers;

public:
	NavigationGraphExample(Eegeo::Resources::Roads::Navigation::NavigationGraphRepository& navigationGraphRepository,
	                       Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

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
    
    
};
}


#endif /* defined(__ExampleApp__NavigationGraphExample__) */
