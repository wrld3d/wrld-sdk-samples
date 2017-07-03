// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "iOSRoutingServiceExampleView.h"
#include "UIHelpers.h"
#include "iOSUIHelpers.h"

@implementation IRoutingServiceExampleBinding

static Examples::iOSRoutingServiceExampleView* m_pExample;

static UIView* m_pRoutingServiceExampleView;
static UIButton* m_pToggleExpandButton;
static UIButton* m_pMoveUpButton;
static UIButton* m_pMoveDownButton;
static UIButton* m_pGetRouteButton;

static UIButton* CreateMenuButton(NSString * title)
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

-(instancetype) initWith:(Examples::iOSRoutingServiceExampleView*)pExample :(UIView*)pView
{
    if (self = [super init])
    {
        m_pExample = pExample;
        m_pRoutingServiceExampleView = pView;
       
        m_pToggleExpandButton = CreateMenuButton(@"Toggle Expanded");
        [m_pToggleExpandButton addTarget:self action:@selector(toggleExpanded) forControlEvents:UIControlEventTouchDown];
        [m_pRoutingServiceExampleView addSubview:m_pToggleExpandButton];
        
        m_pMoveUpButton = CreateMenuButton(@"Move Up!");
        [m_pMoveUpButton addTarget:self action:@selector(moveUp) forControlEvents:UIControlEventTouchDown];
        [m_pRoutingServiceExampleView addSubview:m_pMoveUpButton];
        
        m_pMoveDownButton = CreateMenuButton(@"Move Down!");
        [m_pMoveDownButton addTarget:self action:@selector(moveDown) forControlEvents:UIControlEventTouchDown];
        [m_pRoutingServiceExampleView addSubview:m_pMoveDownButton];
       
        m_pGetRouteButton = CreateMenuButton(@"Get Route!");
        [m_pGetRouteButton addTarget:self action:@selector(getRoute) forControlEvents:UIControlEventTouchDown];
        [m_pRoutingServiceExampleView addSubview:m_pGetRouteButton];
        
        [self layoutViews];
    }
    return self;
}

- (void)dealloc
{
    if (m_pToggleExpandButton != nil)
    {
        [m_pToggleExpandButton removeFromSuperview];
        m_pToggleExpandButton = nil;
    }
    
    if (m_pMoveUpButton != nil)
    {
        [m_pMoveUpButton removeFromSuperview];
        m_pMoveUpButton = nil;
    }
    
    if (m_pMoveDownButton != nil)
    {
        [m_pMoveDownButton removeFromSuperview];
        m_pMoveDownButton = nil;
    }
    
    if (m_pGetRouteButton != nil)
    {
        [m_pGetRouteButton removeFromSuperview];
        m_pGetRouteButton = nil;
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
    
    m_pGetRouteButton.frame = CGRectMake(margin, buttonY, buttonWidth, buttonHeight);
    buttonY -= buttonGridHeight;
    
    m_pMoveDownButton.frame = CGRectMake(margin, buttonY, buttonWidth, buttonHeight);
    buttonY -= buttonGridHeight;
    
    m_pMoveUpButton.frame = CGRectMake(margin, buttonY, buttonWidth, buttonHeight);
    buttonY -= buttonGridHeight;
    
    m_pToggleExpandButton.frame = CGRectMake(margin, buttonY, buttonWidth, buttonHeight);
    buttonY -= buttonGridHeight;
}

-(void) toggleExpanded
{
    m_pExample->ToggleExpanded();
}

-(void) moveUp
{
    m_pExample->MoveUp();
}

-(void) moveDown
{
	m_pExample->MoveDown();
}

-(void) getRoute
{
	m_pExample->GetRoute();
}

@end

namespace Examples
{
    iOSRoutingServiceExampleView::iOSRoutingServiceExampleView(UIView* pView)
    {
        m_pBinding = [[IRoutingServiceExampleBinding alloc] initWith:this :pView];
    }

    iOSRoutingServiceExampleView::~iOSRoutingServiceExampleView()
    {
        [m_pBinding release];
        m_pBinding = nil;
    }

    void iOSRoutingServiceExampleView::AddToggleExpandedHandler(IUIActionHandler& handler)
    {
        m_toggleExpandedHandlers.push_back(&handler);
    }
    
    void iOSRoutingServiceExampleView::RemoveToggleExpandedHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_toggleExpandedHandlers, &handler);
    }
    
    void iOSRoutingServiceExampleView::ToggleExpanded()
    {
        InvokeAllHandlers(m_toggleExpandedHandlers);
    }
    
    void iOSRoutingServiceExampleView::AddMoveUpHandler(IUIActionHandler& handler)
    {
        m_moveUpHandlers.push_back(&handler);
    }

    void iOSRoutingServiceExampleView::RemoveMoveUpHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_moveUpHandlers, &handler);
    }

    void iOSRoutingServiceExampleView::MoveUp()
    {
        InvokeAllHandlers(m_moveUpHandlers);
    }

    void iOSRoutingServiceExampleView::AddMoveDownHandler(IUIActionHandler& handler)
    {
        m_moveDownHandlers.push_back(&handler);
    }

    void iOSRoutingServiceExampleView::RemoveMoveDownHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_moveDownHandlers, &handler);
    }

    void iOSRoutingServiceExampleView::MoveDown()
    {
        InvokeAllHandlers(m_moveDownHandlers);
    }

    void iOSRoutingServiceExampleView::AddGetRouteHandler(IUIActionHandler& handler)
    {
        m_getRouteHandlers.push_back(&handler);
    }

    void iOSRoutingServiceExampleView::RemoveGetRouteHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_getRouteHandlers, &handler);
    }

    void iOSRoutingServiceExampleView::GetRoute()
    {
        InvokeAllHandlers(m_getRouteHandlers);
    }

    void iOSRoutingServiceExampleView::NotifyNeedsLayout()
    {
        [m_pBinding layoutViews];
    }
}
