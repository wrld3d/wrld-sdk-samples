// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RenderToTextureExampleFactory__
#define __ExampleApp__RenderToTextureExampleFactory__

#include "IExampleFactory.h"
#include "GlobeCameraExampleBase.h"
#include "EegeoWorld.h"
#include "ScreenPropertiesProvider.h"

namespace Examples
{
class RenderToTextureExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
    DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;
    
    const IScreenPropertiesProvider& m_screenPropertiesProvider;
    
public:
	RenderToTextureExampleFactory(Eegeo::EegeoWorld& world,
                                  DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                  Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController,
                                  const IScreenPropertiesProvider& screenPropertiesProvider);
    
	std::string ExampleName() const;
    
	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__RenderToTextureExampleFactory__) */
