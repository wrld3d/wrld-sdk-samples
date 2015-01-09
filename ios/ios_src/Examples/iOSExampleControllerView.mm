// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "iOSExampleControllerView.h"
#include "UIHelpers.h"
#include "iOSUIHelpers.h"
#include "App.h"


@interface AvailableExamplesView : UIScrollView

@end

@implementation IExampleControllerViewBinding

Examples::iOSExampleControllerView* m_pInstance;
UIView* m_pView;
UIScrollView* m_pScroller;
std::vector<std::string> m_exampleNames;
UIControl* m_pSelectionScreen;

UIButton* m_pNextButton;
UIButton* m_pPreviousButton;
UIButton* m_pSelectNewExampleButton;

float m_exampleSelectorWidth;

const float topMargin = 20.f;
const float bottomMargin = 30.f;
const float buttonHeight = 30.f;

-(void) setExampleNames:(const std::vector<std::string>&)exampleNames
{
	m_exampleNames = exampleNames;
}


-(instancetype) initWith:(Examples::iOSExampleControllerView*)pInstance :(UIView*)pView :(float)exampleSelectorWidth
{
    if (self = [super init])
    {
        m_pInstance = pInstance;
        m_pView = pView;
        m_pSelectionScreen = nil;
        m_exampleSelectorWidth = exampleSelectorWidth;
        
        if ((UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad))
        {
            m_pPreviousButton = [UIButton buttonWithType:BUTTON_TYPE];
            [m_pPreviousButton retain];
            m_pPreviousButton.frame = CGRectZero;
            [m_pPreviousButton setBackgroundColor:[UIColor colorWithRed:0.0/255.0f green:0.0/255.0f blue:128.0f/255.0f alpha:0.6f]];
            [m_pPreviousButton setTitle:@"Previous" forState:UIControlStateNormal];
            [m_pPreviousButton addTarget:self action:@selector(activatePrevious) forControlEvents:UIControlEventTouchDown];
            
            m_pNextButton = [UIButton buttonWithType:BUTTON_TYPE];
            [m_pNextButton retain];
            m_pNextButton.frame = CGRectZero;
            [m_pNextButton setBackgroundColor:[UIColor colorWithRed:0.0/255.0f green:0.0/255.0f blue:128.0f/255.0f alpha:0.6f]];
            [m_pNextButton setTitle:@"Next" forState:UIControlStateNormal];
            [m_pNextButton addTarget:self action:@selector(activateNext) forControlEvents:UIControlEventTouchDown];
        }
        
        m_pSelectNewExampleButton = [UIButton buttonWithType:BUTTON_TYPE];
        [m_pSelectNewExampleButton retain];
        m_pSelectNewExampleButton.frame = CGRectZero;
        
        [m_pSelectNewExampleButton setBackgroundColor:[UIColor colorWithRed:0.0/255.0f green:0.0/255.0f blue:128.0f/255.0f alpha:0.6f]];
        [m_pSelectNewExampleButton setTitle:@"" forState:UIControlStateNormal];
        [m_pSelectNewExampleButton addTarget:self action:@selector(openExampleSelectionMenu) forControlEvents:UIControlEventTouchDown];
        
        [self layoutViews];
    }
    return self;
}

- (void)dealloc
{
    if (m_pNextButton != nil)
    {
        [m_pNextButton removeFromSuperview];
        m_pNextButton = nil;
    }
    
    if (m_pPreviousButton != nil)
    {
        [m_pPreviousButton removeFromSuperview];
        m_pPreviousButton = nil;
    }
    
    [m_pSelectNewExampleButton removeFromSuperview];
    m_pSelectNewExampleButton = nil;
    
    [super dealloc];
}

-(void) show
{
    if (m_pPreviousButton != nil)
    {
        [m_pView addSubview:m_pPreviousButton];
    }
    
    if (m_pNextButton != nil)
    {
        [m_pView addSubview:m_pNextButton];
    }
    
    [m_pView addSubview:m_pSelectNewExampleButton];
}

-(void) activateNext
{
	m_pInstance->ActivateNext();
}

-(void) activatePrevious
{
	m_pInstance->ActivatePrevious();
}

-(void)selectionHandler:(UIButton*)sender
{
	std::string name = sender.titleLabel.text.UTF8String;
	m_pInstance->SetCurrentExampleName(name);

    [self removeSelectionViews];
}

-(void) handleDismissSelectionScreen
{
    [self removeSelectionViews];
}

-(void) removeSelectionViews
{
    if (m_pScroller != nil)
    {
        [m_pScroller removeFromSuperview];
        [m_pScroller release];
        m_pScroller = nil;
    }
    
    if(m_pSelectionScreen != nil)
    {
        [m_pSelectionScreen removeFromSuperview];
        [m_pSelectionScreen release];
        m_pSelectionScreen = nil;
    }
}



-(void) layoutViews
{
    UIView *rootView = [[[UIApplication sharedApplication] keyWindow]
                        rootViewController].view;
    CGRect originalFrame = [[UIScreen mainScreen] bounds];
    CGRect screenRect = [rootView convertRect:originalFrame fromView:nil];
    

    if (m_pSelectionScreen != nil)
    {
        [self layoutSelectionScreen:screenRect.size];
    }

    [self layoutSelectionButtons:screenRect.size];
    
    [m_pView layoutIfNeeded];
}

-(void) layoutSelectionScreen:(CGSize) screenSize
{
    CGRect selectionRect = CGRectMake(0, 0, screenSize.width, screenSize.height);
    m_pSelectionScreen.frame = selectionRect;
    
    CGRect scrollerRect = CGRectMake((selectionRect.size.width - m_exampleSelectorWidth)/2, topMargin + buttonHeight, m_exampleSelectorWidth, selectionRect.size.height - topMargin - buttonHeight - bottomMargin);
    
    m_pScroller.frame = scrollerRect;
    m_pScroller.contentSize = CGSizeMake(scrollerRect.size.width, buttonHeight * m_exampleNames.size());
    
    int i = 0;
    for (UIView* subView in [m_pScroller subviews])
    {
        if ([subView isKindOfClass:[UIButton class]])
        {
            subView.frame = CGRectMake(0, (i * buttonHeight), m_pScroller.frame.size.width, buttonHeight);
            ++i;
        }

    }
    
    [m_pSelectionScreen layoutIfNeeded];
}

-(void) layoutSelectionButtons:(CGSize) screenSize
{
    m_pSelectNewExampleButton.frame = CGRectMake((screenSize.width - m_exampleSelectorWidth) / 2, topMargin, m_exampleSelectorWidth, buttonHeight);
    
    
    const float prevNextButtonWidth = 100.f;
    const float buttonMarginX = 10.f;
    
    if (m_pPreviousButton != nil)
    {
        m_pPreviousButton.frame = CGRectMake(buttonMarginX, topMargin, prevNextButtonWidth, buttonHeight);
    }
    
    if (m_pNextButton != nil)
    {
        m_pNextButton.frame = CGRectMake(screenSize.width - prevNextButtonWidth - buttonMarginX, topMargin, prevNextButtonWidth, buttonHeight);
    }
}

-(void) openExampleSelectionMenu
{
	m_pSelectionScreen = [[UIControl alloc] initWithFrame:CGRectZero];
	m_pSelectionScreen.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:0.3f];

	m_pScroller = [[UIScrollView alloc] initWithFrame:CGRectZero];
    
    m_pScroller.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:0.5];

	for (int i = 0; i < m_exampleNames.size(); ++ i)
	{
		NSString* label = [NSString stringWithUTF8String:m_exampleNames[i].c_str()];
		UIButton* b = [UIButton buttonWithType:BUTTON_TYPE];
		b.frame = CGRectZero;

		[b setTitle:label forState:UIControlStateNormal];
        [b addTarget:self action:@selector(selectionHandler:) forControlEvents:UIControlEventTouchUpInside];
		[m_pScroller addSubview:b];
	}

    
	[m_pSelectionScreen addSubview:m_pScroller];

	[m_pSelectionScreen addTarget:self action:@selector(handleDismissSelectionScreen) forControlEvents:UIControlEventTouchDragInside];
	[m_pSelectionScreen addTarget:self action:@selector(handleDismissSelectionScreen) forControlEvents:UIControlEventTouchUpInside];

	[m_pView addSubview:m_pSelectionScreen];
    
    [self layoutViews];
}

@end

namespace Examples
{
iOSExampleControllerView::iOSExampleControllerView(UIView* pView)
	: m_pView(pView)
{
    const float selectionMenuWidth = 500.f;
	m_pBinding = [[IExampleControllerViewBinding alloc] initWith:this :m_pView :selectionMenuWidth];
}

iOSExampleControllerView::~iOSExampleControllerView()
{
	[m_pBinding release];
	m_pBinding = nil;
}

void iOSExampleControllerView::PopulateExampleList(const std::vector<std::string>& exampleNames)
{
	[m_pBinding setExampleNames: exampleNames];
}

void iOSExampleControllerView::Show()
{
    [m_pBinding show];
}

void iOSExampleControllerView::SetCurrentExampleName(const std::string &name)
{
	NSString* s = [NSString stringWithUTF8String:name.c_str()];
	[m_pSelectNewExampleButton setTitle:s forState:UIControlStateNormal];

	m_selectedExample = name;
	UpdateSelectedExample();
}

void iOSExampleControllerView::AddSelectPreviousExampleHandler(IUIActionHandler& handler)
{
	m_previousHandlers.push_back(&handler);
}

void iOSExampleControllerView::RemoveSelectPreviousExampleHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_previousHandlers, &handler);
}

void iOSExampleControllerView::ActivatePrevious()
{
	InvokeAllHandlers(m_previousHandlers);
}

void iOSExampleControllerView::AddSelectNextExampleHandler(IUIActionHandler& handler)
{
	m_nextHandlers.push_back(&handler);
}

void iOSExampleControllerView::RemoveSelectNextExampleHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_nextHandlers, &handler);
}

void iOSExampleControllerView::ActivateNext()
{
	InvokeAllHandlers(m_nextHandlers);
}

void iOSExampleControllerView::AddExampleSelectedHandler(IUIActionHandler& handler)
{
	m_exampleUpdatedHandlers.push_back(&handler);
}

void iOSExampleControllerView::RemoveExampleSelectedHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_exampleUpdatedHandlers, &handler);
}

void iOSExampleControllerView::UpdateSelectedExample()
{
	InvokeAllHandlers(m_exampleUpdatedHandlers);
}

std::string iOSExampleControllerView::GetSelectedExample()
{
	return m_selectedExample;
}

void iOSExampleControllerView::NotifyNeedsLayout()
{
    [m_pBinding layoutViews];

    
}
}
