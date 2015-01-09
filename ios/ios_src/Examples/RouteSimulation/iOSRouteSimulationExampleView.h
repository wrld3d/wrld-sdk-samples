// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__iOSRouteSimulationExampleView__
#define __ExampleApp__iOSRouteSimulationExampleView__

#include "Types.h"
#include "IRouteSimulationExampleView.h"
#import <UIKit/UIKit.h>
#include <vector>

namespace Examples
{
class iOSRouteSimulationExampleView;
}

@interface IRouteSimulationExampleBinding : NSObject

-(instancetype) initWith:(Examples::iOSRouteSimulationExampleView*)pExample :(UIView*)pView;
-(void) toggleFollowCamera;
-(void) toggleFollowMode:(bool)followEnabled;
-(void) changeFollowDirection;
-(void) increaseSpeedFollowed;
-(void) decreaseSpeedFollowed;
-(void) rotateToFollow;
-(void) toggleSideOfRoadToDriveOn;
-(void) layoutViews;

@end

namespace Examples
{
class iOSRouteSimulationExampleView : public IRouteSimulationExampleView, private Eegeo::NonCopyable
{
	std::vector<IUIActionHandler*> m_followCameraToggledHandlers;
	std::vector<IUIActionHandler*> m_directionChangedHandlers;
	std::vector<IUIActionHandler*> m_increaseSpeedHandlers;
	std::vector<IUIActionHandler*> m_decreaseSpeedHandlers;
	std::vector<IUIActionHandler*> m_rotateToFollowToggledHandlers;
	std::vector<IUIActionHandler*> m_roadSideChangedHandlers;

	
	IRouteSimulationExampleBinding* m_pBinding;


public:

	iOSRouteSimulationExampleView(UIView* pView);

	~iOSRouteSimulationExampleView();

	void AddFollowCameraToggledHandler(IUIActionHandler& handler);

	void RemoveFollowCameraToggledHandler(IUIActionHandler& handler);

	void ToggleFollowCamera();

	void AddFollowCameraDirectionChangedHandler(IUIActionHandler& handler);

	void RemoveFollowCameraDirectionChangedHandler(IUIActionHandler& handler);

	void ToggleCameraDirection();

	void AddIncreaseSpeedHandler(IUIActionHandler& handler);

	void RemoveIncreaseSpeedHandler(IUIActionHandler& handler);

	void IncreaseSpeed();

	void AddDecreaseSpeedHandler(IUIActionHandler& handler);

	void RemoveDecreaseSpeedHandler(IUIActionHandler& handler);

	void DecreaseSpeed();

	void AddRotateToFollowToggledHandler(IUIActionHandler& handler);

	void RemoveRotateToFollowToggledHandler(IUIActionHandler& handler);

	void ToggleRotateToFollow();

	void AddSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler);

	void RemoveSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler);

	void ChangeSideOfRoad();
    
    void NotifyNeedsLayout();

private:

	void ToggleFollowMode(bool followEnabled);
};
}


#endif /* defined(__ExampleApp__iOSRouteSimulationExampleView__) */
