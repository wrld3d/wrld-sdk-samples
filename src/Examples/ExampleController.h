// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ExampleController__
#define __ExampleApp__ExampleController__

#include "IExample.h"
#include "IExampleFactory.h"
#include "Types.h"
#include "EegeoWorld.h"
#include "UIActionHandler.h"
#include "IExampleControllerView.h"
#include "Camera.h"
#include "ScreenPropertiesProvider.h"
#include "DefaultCameraControllerFactory.h"

#include <vector>
#include <string>

namespace Examples
{
class ExampleController : private Eegeo::NonCopyable
{
	IExample* m_pCurrentExample;
	int m_currentExampleFactoryIndex;
	Eegeo::EegeoWorld& m_world;
	std::vector<IExampleFactory*> m_factories;
	bool m_uiVisible;
    DefaultCameraControllerFactory& m_defaultCameraControllerFactory;

	IExampleControllerView& m_view;
	UIActionHandler<ExampleController> m_nextExampleHandler;
	UIActionHandler<ExampleController> m_previousExampleHandler;
	UIActionHandler<ExampleController> m_selectedExampleChangedHandler;

	void DestroyCurrentExample();

	void RefreshExample();

public:
	ExampleController(Eegeo::EegeoWorld& world,
	                  IExampleControllerView& view,
                      DefaultCameraControllerFactory& defaultCameraControllerFactory);

	~ExampleController();

	std::vector<std::string> GetExampleNames() const;

	void UpdateSelectedExample();

	void ActivatePrevious();

	void ActivateNext();

	void EarlyUpdate(float dt);

	void Update(float dt);
    
	void PreWorldDraw();
    
	void Draw();

	void RegisterExample(IExampleFactory* pFactory);
    
    const Eegeo::Camera::RenderCamera& GetCurrentActiveCamera() const;
    
    Eegeo::dv3 GetCurrentInterestPoint() const;
    
    void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);

	template <typename TExampleFactory>
	void RegisterExample()
	{
		m_factories.push_back(Eegeo_NEW((TExampleFactory)(m_world)));
	}

	template <typename TExampleFactory>
	void RegisterCameraExample()
	{
		m_factories.push_back(Eegeo_NEW((TExampleFactory)(m_world, m_defaultCameraControllerFactory)));
	}
    
    template <typename TExampleFactory>
    void RegisterCameraScreenPropertiesProviderExample(const ScreenPropertiesProvider& screenPropertiesProvider)
    {
        m_factories.push_back(Eegeo_NEW((TExampleFactory)(m_world, m_defaultCameraControllerFactory, screenPropertiesProvider)));
    }

	bool Event_TouchRotate(const AppInterface::RotateData& data);
	bool Event_TouchRotate_Start(const AppInterface::RotateData& data);
	bool Event_TouchRotate_End(const AppInterface::RotateData& data);

	bool Event_TouchPinch(const AppInterface::PinchData& data);
	bool Event_TouchPinch_Start(const AppInterface::PinchData& data);
	bool Event_TouchPinch_End(const AppInterface::PinchData& data);

	bool Event_TouchPan(const AppInterface::PanData& data);
	bool Event_TouchPan_Start(const AppInterface::PanData& data);
	bool Event_TouchPan_End(const AppInterface::PanData& data);

	bool Event_TouchTap(const AppInterface::TapData& data);
	bool Event_TouchDoubleTap(const AppInterface::TapData& data);

	bool Event_TouchDown(const AppInterface::TouchData& data);
	bool Event_TouchMove(const AppInterface::TouchData& data);
	bool Event_TouchUp(const AppInterface::TouchData& data);
};
}

#endif /* defined(__ExampleApp__ExampleController__) */
