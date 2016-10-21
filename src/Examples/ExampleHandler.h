// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IExample.h"
#include "CameraState.h"
#include "EegeoWorld.h"

namespace Examples
{
    class ExampleHandler : public IExample
    {
    public:
        virtual ~ExampleHandler() {}
        virtual void AfterCameraUpdate() { }
        virtual void SetVRCameraState(const float headTransform[]){}
        virtual void UpdateCardboardProfile(const float cardboardProfile[]){}

        virtual void UpdateWorld(float dt, Eegeo::EegeoWorld& world, Eegeo::Camera::CameraState cameraState, Examples::ScreenPropertiesProvider& screenPropertyProvider, Eegeo::Streaming::IStreamingVolume& streamingVolume)
        {
        	Eegeo::EegeoUpdateParameters updateParameters(dt,
        		    									  cameraState.LocationEcef(),
														  cameraState.InterestPointEcef(),
														  cameraState.ViewMatrix(),
														  cameraState.ProjectionMatrix(),
														  streamingVolume,
														  screenPropertyProvider.GetScreenProperties());
        	world.Update(updateParameters);
        }

        virtual void DrawWorld(Eegeo::EegeoWorld& world, Eegeo::Camera::CameraState cameraState, Examples::ScreenPropertiesProvider& screenPropertyProvider)
        {
        	Eegeo::EegeoDrawParameters drawParameters(cameraState.LocationEcef(),
        	        							      cameraState.InterestPointEcef(),
        											  cameraState.ViewMatrix(),
        											  cameraState.ProjectionMatrix(),
													  screenPropertyProvider.GetScreenProperties());

        	world.Draw(drawParameters);
        }
    };

}
