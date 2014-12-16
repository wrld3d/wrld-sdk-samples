// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ReadHeadingExample.h"
#include "EegeoWorld.h"
#include "ILocationService.h"
#include "DebugRenderer.h"
#include "CoordinateConversion.h"
#include "LatLongAltitude.h"
#include "Logger.h"
#include "Colors.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"

namespace Examples
{
	ReadHeadingExample::ReadHeadingExample(Eegeo::EegeoWorld& eegeoWorld,
                                           Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                           Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                                           Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                           Eegeo::Location::ILocationService& locationService)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_world(eegeoWorld)
	, m_debugRenderer(debugRenderer)
    , m_locationService(locationService)
    {
    }
    
    void ReadHeadingExample::Update(float dt)
    {
    	double degrees;
    	if(m_locationService.GetHeadingDegrees(degrees))
    	{
    		EXAMPLE_LOG("Heading: %f\n", degrees);
            
            Eegeo::dv3 ecefCenter = ConvertLatLongAltitudeToEcef(Eegeo::Space::LatLongAltitude::FromDegrees(37.78469,-122.40143, 200));
            Eegeo::Space::EcefTangentBasis tangentBasis;
            Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(ecefCenter, static_cast<float>(degrees), tangentBasis);
            const float axesSize = 150.0f;
            m_debugRenderer.DrawAxes(ecefCenter, tangentBasis.GetRight()*axesSize, tangentBasis.GetUp()*axesSize, tangentBasis.GetForward()*axesSize);
    	}
    	else
    	{
    		EXAMPLE_LOG("Unable to read heading from device.\n");
    	}
    }

}
