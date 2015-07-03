// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ViewController.h"
#include "AppLocationDelegate.h"

const std::string ApiKey = "OBTAIN API_KEY FROM https://www.eegeo.com/developers/ AND INSERT IT HERE";

using namespace Eegeo::iOS;

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver: self
                                             selector: @selector(onPause)
                                                 name: @"handlePause"
                                               object: nil];
    
    [[NSNotificationCenter defaultCenter] addObserver: self
                                             selector: @selector(onResume)
                                                 name: @"handleResume"
                                               object: nil];
    
	m_previousTimestamp = CFAbsoluteTimeGetCurrent();
	self.preferredFramesPerSecond = 60;
    
    m_pAppRunner = new AppRunner(ApiKey, *self);
    
    if ([self respondsToSelector:@selector(setNeedsStatusBarAppearanceUpdate)]) {
        // iOS 7>=
        [self performSelector:@selector(setNeedsStatusBarAppearanceUpdate)];
    }
}

- (BOOL)prefersStatusBarHidden
{
    return NO;
}

- (void)onPause
{
    m_pAppRunner->Pause();
    
    GLKView* glkView = static_cast<GLKView*>(self.view);
    glkView.context = nil;
}

- (void)onResume
{
    GLKView* glkView = static_cast<GLKView*>(self.view);
    glkView.context = [EAGLContext currentContext];
    
    m_pAppRunner->Resume();
}
    

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
	CFTimeInterval timeNow = CFAbsoluteTimeGetCurrent();
	CFTimeInterval frameDuration = timeNow - m_previousTimestamp;
    m_pAppRunner->Update(static_cast<float>(frameDuration));
    
	const GLenum discards[]  = {GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT};
	Eegeo_GL(glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 2, discards));
    
    m_previousTimestamp = timeNow;
}

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
	return YES;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
	return YES;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (m_pAppRunner == NULL)
        ? true
        : m_pAppRunner->ShouldAutoRotateToInterfaceOrientation(interfaceOrientation);
}

- (BOOL)shouldAutorotate
{
    UIInterfaceOrientation interfaceOrientation = [[UIApplication sharedApplication] statusBarOrientation];
    
    return (m_pAppRunner == NULL)
        ? true
        : m_pAppRunner->ShouldAutoRotateToInterfaceOrientation(interfaceOrientation);
}

- (void)viewWillLayoutSubviews
{
    if (m_pAppRunner != NULL)
    {
        m_pAppRunner->NotifyViewLayoutChanged();
    }
}

@end
