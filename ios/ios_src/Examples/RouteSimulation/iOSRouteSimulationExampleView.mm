// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "iOSRouteSimulationExampleView.h"
#include "UIHelpers.h"
#include "iOSUIHelpers.h"

@implementation IRouteSimulationExampleBinding

Examples::iOSRouteSimulationExampleView* m_pExample;


UIView* m_pRouteSimulationExampleView;
UIButton* m_pToggleFollowButton;
UIButton* m_pIncreaseSpeedButton;
UIButton* m_pDecreaseSpeedButton;
UIButton* m_pRotateToFollowButton;
UIButton* m_pChangeDirectionButton;
UIButton* m_pToggleSideOfRoadToDriveOnButton;


UIButton* CreateMenuButton(NSString * title)
{
    UIButton* button = [UIButton buttonWithType:BUTTON_TYPE];
    button.frame = CGRectZero;
    [button setBackgroundColor:[UIColor colorWithRed:0.0/255.0f green:0.0/255.0f blue:128.0f/255.0f alpha:0.6f]];
    [button setTitle:title forState:UIControlStateNormal];
    
    if(!IS_IPAD) {
        button.titleLabel.font = [UIFont systemFontOfSize:10];
    }
    
    return button;
}

-(instancetype) initWith:(Examples::iOSRouteSimulationExampleView*)pExample :(UIView*)pView
{
    if (self = [super init])
    {
        m_pExample = pExample;
        m_pRouteSimulationExampleView = pView;
       
        m_pToggleFollowButton = CreateMenuButton(@"Toggle Follow!");
        [m_pToggleFollowButton addTarget:self action:@selector(toggleFollowCamera) forControlEvents:UIControlEventTouchDown];
        [m_pRouteSimulationExampleView addSubview:m_pToggleFollowButton];
        
        m_pIncreaseSpeedButton = CreateMenuButton(@"Increase Speed!");
        [m_pIncreaseSpeedButton addTarget:self action:@selector(increaseSpeedFollowed) forControlEvents:UIControlEventTouchDown];
        [m_pRouteSimulationExampleView addSubview:m_pIncreaseSpeedButton];
       
        m_pDecreaseSpeedButton = CreateMenuButton(@"Decrease Speed!");
        [m_pDecreaseSpeedButton addTarget:self action:@selector(decreaseSpeedFollowed) forControlEvents:UIControlEventTouchDown];
        [m_pRouteSimulationExampleView addSubview:m_pDecreaseSpeedButton];
        
        m_pChangeDirectionButton = CreateMenuButton(@"Change Direction!");
        [m_pChangeDirectionButton addTarget:self action:@selector(changeFollowDirection) forControlEvents:UIControlEventTouchDown];
        [m_pRouteSimulationExampleView addSubview:m_pChangeDirectionButton];
        
        m_pRotateToFollowButton = CreateMenuButton(@"Rotate to Follow!");
        [m_pRotateToFollowButton addTarget:self action:@selector(rotateToFollow) forControlEvents:UIControlEventTouchDown];
        [m_pRouteSimulationExampleView addSubview:m_pRotateToFollowButton];
        
        
        //this one goes beside toggle follow as we can do it any time
        m_pToggleSideOfRoadToDriveOnButton = [UIButton buttonWithType:BUTTON_TYPE];
        m_pToggleSideOfRoadToDriveOnButton.frame = CGRectZero;

        [m_pToggleSideOfRoadToDriveOnButton setBackgroundColor:[UIColor colorWithRed:0.0/255.0f green:0.0/255.0f blue:128.0f/255.0f alpha:0.6f]];
        [m_pToggleSideOfRoadToDriveOnButton setTitle:@"Toggle Road Side!" forState:UIControlStateNormal];
        [m_pToggleSideOfRoadToDriveOnButton addTarget:self action:@selector(toggleSideOfRoadToDriveOn) forControlEvents:UIControlEventTouchDown];
        [m_pRouteSimulationExampleView addSubview:m_pToggleSideOfRoadToDriveOnButton];
        
        if (!IS_IPAD) {
            m_pToggleSideOfRoadToDriveOnButton.titleLabel.font = [UIFont systemFontOfSize:10];
        }

        [self layoutViews];
    }
    return self;
}

- (void)dealloc
{
    if (m_pToggleFollowButton != nil)
    {
        [m_pToggleFollowButton removeFromSuperview];
        m_pToggleFollowButton = nil;
    }
    
    if (m_pIncreaseSpeedButton != nil)
    {
        [m_pIncreaseSpeedButton removeFromSuperview];
        m_pIncreaseSpeedButton = nil;
    }
    
    if (m_pDecreaseSpeedButton != nil)
    {
        [m_pDecreaseSpeedButton removeFromSuperview];
        m_pDecreaseSpeedButton = nil;
    }
    
    if (m_pRotateToFollowButton != nil)
    {
        [m_pRotateToFollowButton removeFromSuperview];
        m_pRotateToFollowButton = nil;
    }
    
    if (m_pChangeDirectionButton != nil)
    {
        [m_pChangeDirectionButton removeFromSuperview];
        m_pChangeDirectionButton = nil;
    }
    
    if (m_pToggleSideOfRoadToDriveOnButton != nil)
    {
        [m_pToggleSideOfRoadToDriveOnButton removeFromSuperview];
        m_pToggleSideOfRoadToDriveOnButton = nil;
    }
    
    [super dealloc];
}

-(void) layoutViews
{
    // Grab the window frame and adjust it for orientation
    UIView *rootView = [[[UIApplication sharedApplication] keyWindow]
                        rootViewController].view;
    CGRect originalFrame = [[UIScreen mainScreen] bounds];
    CGRect adjustedFrame = [rootView convertRect:originalFrame fromView:nil];

    
    const float buttonHeight = 30.f;
    const float buttonGridHeight = 40.f;
    const float buttonWidth = 200.f;
    const float margin = 20.f;
    
    float buttonY = static_cast<float>(adjustedFrame.size.height) - margin - buttonHeight;
    
    m_pToggleSideOfRoadToDriveOnButton.frame = CGRectMake(margin, buttonY, buttonWidth, buttonHeight);
    buttonY -= buttonGridHeight;
    
    m_pChangeDirectionButton.frame = CGRectMake(margin, buttonY, buttonWidth, buttonHeight);
    buttonY -= buttonGridHeight;
    
    m_pRotateToFollowButton.frame = CGRectMake(margin, buttonY, buttonWidth, buttonHeight);
    buttonY -= buttonGridHeight;
    
    m_pDecreaseSpeedButton.frame = CGRectMake(margin, buttonY, buttonWidth, buttonHeight);
    buttonY -= buttonGridHeight;
    
    m_pIncreaseSpeedButton.frame = CGRectMake(margin, buttonY, buttonWidth, buttonHeight);
    buttonY -= buttonGridHeight;
    
    m_pToggleFollowButton.frame = CGRectMake(margin, buttonY, buttonWidth, buttonHeight);
    buttonY -= buttonGridHeight;
}

-(void) toggleFollowCamera
{
	m_pExample->ToggleFollowCamera();

	[m_pChangeDirectionButton setHidden: ![m_pChangeDirectionButton isHidden]];
	[m_pIncreaseSpeedButton setHidden: ![m_pIncreaseSpeedButton isHidden]];
	[m_pDecreaseSpeedButton setHidden: ![m_pDecreaseSpeedButton isHidden]];
	[m_pRotateToFollowButton setHidden: ![m_pRotateToFollowButton isHidden]];
}

-(void) toggleFollowMode:(bool) followEnabled
{
    [m_pChangeDirectionButton setHidden: !followEnabled];
    [m_pIncreaseSpeedButton setHidden: !followEnabled];
    [m_pDecreaseSpeedButton setHidden: !followEnabled];
    [m_pRotateToFollowButton setHidden: !followEnabled];
}

-(void) changeFollowDirection
{
	m_pExample->ToggleCameraDirection();
}

-(void) increaseSpeedFollowed
{
	m_pExample->IncreaseSpeed();
}

-(void) decreaseSpeedFollowed
{
	m_pExample->DecreaseSpeed();
}

-(void) rotateToFollow
{
	m_pExample->ToggleRotateToFollow();
}

-(void) toggleSideOfRoadToDriveOn
{
	m_pExample->ChangeSideOfRoad();
}

@end

namespace Examples
{
    iOSRouteSimulationExampleView::iOSRouteSimulationExampleView(UIView* pView)
    {
        m_pBinding = [[IRouteSimulationExampleBinding alloc] initWith:this :pView];

        ToggleFollowMode(false);
    }

    iOSRouteSimulationExampleView::~iOSRouteSimulationExampleView()
    {
        [m_pBinding release];
        m_pBinding = nil;
    }

    void iOSRouteSimulationExampleView::ToggleFollowMode(bool followEnabled)
    {
        [m_pBinding toggleFollowMode:followEnabled];
    }

    void iOSRouteSimulationExampleView::AddFollowCameraToggledHandler(IUIActionHandler& handler)
    {
        m_followCameraToggledHandlers.push_back(&handler);
    }

    void iOSRouteSimulationExampleView::RemoveFollowCameraToggledHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_followCameraToggledHandlers, &handler);
    }

    void iOSRouteSimulationExampleView::ToggleFollowCamera()
    {
        InvokeAllHandlers(m_followCameraToggledHandlers);
    }

    void iOSRouteSimulationExampleView::AddFollowCameraDirectionChangedHandler(IUIActionHandler& handler)
    {
        m_directionChangedHandlers.push_back(&handler);
    }

    void iOSRouteSimulationExampleView::RemoveFollowCameraDirectionChangedHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_directionChangedHandlers, &handler);
    }

    void iOSRouteSimulationExampleView::ToggleCameraDirection()
    {
        InvokeAllHandlers(m_directionChangedHandlers);
    }

    void iOSRouteSimulationExampleView::AddIncreaseSpeedHandler(IUIActionHandler& handler)
    {
        m_increaseSpeedHandlers.push_back(&handler);
    }

    void iOSRouteSimulationExampleView::RemoveIncreaseSpeedHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_increaseSpeedHandlers, &handler);
    }

    void iOSRouteSimulationExampleView::IncreaseSpeed()
    {
        InvokeAllHandlers(m_increaseSpeedHandlers);
    }

    void iOSRouteSimulationExampleView::AddDecreaseSpeedHandler(IUIActionHandler& handler)
    {
        m_decreaseSpeedHandlers.push_back(&handler);
    }

    void iOSRouteSimulationExampleView::RemoveDecreaseSpeedHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_decreaseSpeedHandlers, &handler);
    }

    void iOSRouteSimulationExampleView::DecreaseSpeed()
    {
        InvokeAllHandlers(m_decreaseSpeedHandlers);
    }

    void iOSRouteSimulationExampleView::AddRotateToFollowToggledHandler(IUIActionHandler& handler)
    {
        m_rotateToFollowToggledHandlers.push_back(&handler);
    }

    void iOSRouteSimulationExampleView::RemoveRotateToFollowToggledHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_rotateToFollowToggledHandlers, &handler);
    }

    void iOSRouteSimulationExampleView::ToggleRotateToFollow()
    {
        InvokeAllHandlers(m_rotateToFollowToggledHandlers);
    }

    void iOSRouteSimulationExampleView::AddSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler)
    {
        m_roadSideChangedHandlers.push_back(&handler);
    }

    void iOSRouteSimulationExampleView::RemoveSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_roadSideChangedHandlers, &handler);
    }

    void iOSRouteSimulationExampleView::ChangeSideOfRoad()
    {
        InvokeAllHandlers(m_roadSideChangedHandlers);
    }

    void iOSRouteSimulationExampleView::NotifyNeedsLayout()
    {
        [m_pBinding layoutViews];
    }
    
}
