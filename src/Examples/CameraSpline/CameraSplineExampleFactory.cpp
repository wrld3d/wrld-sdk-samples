// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CameraSplineExampleFactory.h"
#include "CameraSplineExample.h"
#include "EegeoWorld.h"
#include "GlobeCameraController.h"
#include "ResourceCeilingProvider.h"

#include "MapModule.h"

namespace Examples
{

CameraSplineExampleFactory::CameraSplineExampleFactory(Eegeo::EegeoWorld& world,
                                                       const IScreenPropertiesProvider& screenPropertiesProvider)
: m_world(world)
, m_screenPropertiesProvider(screenPropertiesProvider)
{
    
}

IExample* CameraSplineExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    
    const Eegeo::Rendering::ScreenProperties& initialScreenProperties = m_screenPropertiesProvider.GetScreenProperties();
    
	return new Examples::CameraSplineExample(m_world,
                                             mapModule.GetResourceCeilingProvider(),
                                             initialScreenProperties);
}

std::string CameraSplineExampleFactory::ExampleName() const
{
	return Examples::CameraSplineExample::GetName();
}
}
