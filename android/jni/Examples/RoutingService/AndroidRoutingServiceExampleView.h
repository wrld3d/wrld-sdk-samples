// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__AndroidRoutingServiceExampleView__
#define __ExampleApp__AndroidRoutingServiceExampleView__

#include "Types.h"
#include "IRoutingServiceExampleView.h"
#include "AndroidNativeState.h"
#include <vector>
#include <jni.h>

namespace Examples
{
class AndroidRoutingServiceExampleView : public IRoutingServiceExampleView, private Eegeo::NonCopyable
{
	std::vector<IUIActionHandler*> m_moveUpHandlers;
	std::vector<IUIActionHandler*> m_moveDownHandlers;
	std::vector<IUIActionHandler*> m_getRouteHandlers;

	AndroidNativeState& m_nativeState;
	jclass m_routingServiceExampleHudClass;
	jobject m_routingServiceExampleHud;

public:
	AndroidRoutingServiceExampleView(
	    AndroidNativeState& androidNativeState);

	~AndroidRoutingServiceExampleView();

	void AddMoveUpHandler(IUIActionHandler& handler);

	void RemoveMoveUpHandler(IUIActionHandler& handler);

	void MoveUp();

	void AddMoveDownHandler(IUIActionHandler& handler);

	void RemoveMoveDownHandler(IUIActionHandler& handler);

	void MoveDown();

	void AddGetRouteHandler(IUIActionHandler& handler);

	void RemoveGetRouteHandler(IUIActionHandler& handler);

	void GetRoute();

	void NotifyNeedsLayout() {;}
};
}

#endif /* defined(__ExampleApp__AndroidRoutingServiceExampleView__) */
