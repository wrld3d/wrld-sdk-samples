// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppRunner.h"
#include "Graphics.h"
#include "App.h"

AppRunner::AppRunner
(
 const std::string& apiKey,
 ViewController& viewController
)
	: m_viewController(viewController)
    , m_apiKey(apiKey)
	, m_pAppHost(NULL)
{
	ReleaseDisplay();
	bool displayBound = TryBindDisplay();
	Eegeo_ASSERT(displayBound);
	CreateAppHost();
}

AppRunner::~AppRunner()
{
	m_displayService.ReleaseDisplay();

	if(m_pAppHost != NULL)
	{
		Eegeo_DELETE(m_pAppHost);
	}
}

void AppRunner::CreateAppHost()
{
	if(m_pAppHost == NULL && m_displayService.IsDisplayAvailable())
	{
        const Eegeo::Rendering::ScreenProperties& screenProperties =
            Eegeo::Rendering::ScreenProperties::Make(
                                                 m_displayService.GetDisplayWidth(),
                                                 m_displayService.GetDisplayHeight(),
                                                 m_displayService.GetPixelScale(),
                                                 m_displayService.GetDisplayDpi());
        
		m_pAppHost = Eegeo_NEW(AppHost)
        (
         m_apiKey,
         m_viewController,
         screenProperties
        );
	}
}

void AppRunner::Pause()
{
	if(m_pAppHost != NULL)
	{
		m_pAppHost->OnPause();
	}
}

void AppRunner::Resume()
{
	if(m_pAppHost != NULL)
	{
		m_pAppHost->OnResume();
	}
}

void AppRunner::ReleaseDisplay()
{
	if(m_displayService.IsDisplayAvailable())
	{
		m_displayService.ReleaseDisplay();
	}
}

bool AppRunner::TryBindDisplay()
{
	if(m_displayService.TryBindDisplay((GLKView&)*[&m_viewController view]))
	{
		if(m_pAppHost != NULL)
		{
			m_pAppHost->SetViewportOffset(0, 0);
		}

		return true;
	}

	return false;
}

void AppRunner::Update(float deltaSeconds)
{
	if(m_pAppHost != NULL && m_displayService.IsDisplayAvailable())
	{
		m_pAppHost->Update(deltaSeconds);

		Eegeo::Helpers::GLHelpers::ClearBuffers();

		m_pAppHost->Draw(deltaSeconds);
	}
}

void AppRunner::NotifyViewLayoutChanged()
{
    if (m_displayService.IsDisplayAvailable())
    {
        m_displayService.UpdateDisplayDimensions();
        
        const Eegeo::Rendering::ScreenProperties& screenProperties =
            Eegeo::Rendering::ScreenProperties::Make(
                                                     m_displayService.GetDisplayWidth(),
                                                     m_displayService.GetDisplayHeight(),
                                                     m_displayService.GetPixelScale(),
                                                     m_displayService.GetDisplayDpi());
        
        m_pAppHost->NotifyScreenPropertiesChanged(screenProperties);
    }
}

bool AppRunner::ShouldAutoRotateToInterfaceOrientation(UIInterfaceOrientation interfaceOrientation)
{
    // if return true , OS intersects interfaceOrientation with supported orientations for app (specified in info.plist), only
    // rotates if mode is allowed 
    return true;
}
