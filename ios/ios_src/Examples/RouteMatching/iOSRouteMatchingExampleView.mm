// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "iOSRouteMatchingExampleView.h"
#include "UIHelpers.h"
#include "iOSUIHelpers.h"


@implementation IRouteMatchingExampleBinding

Examples::iOSRouteMatchingExampleView* m_pRouteMatchingExample;
UIView* m_pRouteMatchingExampleView;
UIButton* m_pToggleMatchingButton;


-(instancetype) initWith:(Examples::iOSRouteMatchingExampleView*)pExample :(UIView*)pView
{
    if (self = [super init])
    {
        m_pRouteMatchingExample = pExample;
        m_pRouteMatchingExampleView = pView;

        m_pToggleMatchingButton = [UIButton buttonWithType:BUTTON_TYPE];
        m_pToggleMatchingButton.frame = CGRectZero;
        
        
        if (!IS_IPAD)
        {
            m_pToggleMatchingButton.titleLabel.font = [UIFont systemFontOfSize:10];
        }
        
        [m_pToggleMatchingButton setTitle:@"Toggle Match!" forState:UIControlStateNormal];
        [m_pToggleMatchingButton setBackgroundColor:[UIColor colorWithRed:0.0/255.0f green:0.0/255.0f blue:128.0f/255.0f alpha:0.6f]];
        [m_pToggleMatchingButton addTarget:self action:@selector(toggleMatching) forControlEvents:UIControlEventTouchDown];
        [m_pRouteMatchingExampleView addSubview:m_pToggleMatchingButton];
        
        [self layoutViews];
    }
    return self;
}

- (void)dealloc
{
    if (m_pToggleMatchingButton != nil)
    {
        [m_pToggleMatchingButton removeFromSuperview];
        m_pToggleMatchingButton = nil;
    }
    
    [super dealloc];
}

-(void) toggleMatching
{
	m_pRouteMatchingExample->ToggleMatching();
}

-(void) layoutViews
{
    // Grab the window frame and adjust it for orientation
    UIView *rootView = [[[UIApplication sharedApplication] keyWindow]
                        rootViewController].view;
    
    CGRect originalFrame = [[UIScreen mainScreen] bounds];
    CGRect adjustedFrame = [rootView convertRect:originalFrame fromView:nil];
    
    const float margin = 20.f;
    const float buttonWidth = 200.f;
    const float buttonHeight = 50.f;
    
    m_pToggleMatchingButton.frame = CGRectMake(margin, adjustedFrame.size.height - margin - buttonHeight, buttonWidth, buttonHeight);
}
@end

namespace Examples
{
    iOSRouteMatchingExampleView::iOSRouteMatchingExampleView(UIView* pView)
    {
        m_pBinding = [[IRouteMatchingExampleBinding alloc] initWith:this :pView];
    }

    iOSRouteMatchingExampleView::~iOSRouteMatchingExampleView()
    {
        [m_pBinding release];
        m_pBinding = nil;
    }

    void iOSRouteMatchingExampleView::AddMatchingToggledHandler(IUIActionHandler& handler)
    {
        m_matchingToggledHandlers.push_back(&handler);
    }

    void iOSRouteMatchingExampleView::RemoveMatchingToggledHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_matchingToggledHandlers, &handler);
    }

    void iOSRouteMatchingExampleView::ToggleMatching()
    {
        InvokeAllHandlers(m_matchingToggledHandlers);
    }
    
    void iOSRouteMatchingExampleView::NotifyNeedsLayout()
    {
        [m_pBinding layoutViews];
    }
}
