// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__Pick3DObjectExample__
#define __ExampleApp__Pick3DObjectExample__

#include <iostream>

#include "GlobeCameraExampleBase.h"
#include "RenderContext.h"
#include "SphereMesh.h"
#include "LatLongAltitude.h"
#include "VectorMath.h"

namespace Examples
{
class Pick3DObjectExample : public GlobeCameraExampleBase
{
private:
	struct Ray
	{
		Eegeo::dv3 origin;
		Eegeo::v3 direction;
	};

	bool m_movingObject;
	Eegeo::DebugRendering::SphereMesh* m_pObject;
	Eegeo::dv3 m_objectLocationEcef;
    Eegeo::v4 m_objectColor;
    
    Eegeo::Space::LatLongAltitude m_interestLocation;
    Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;

    

public:
	Pick3DObjectExample(
                        Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                        Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	static std::string GetName()
	{
		return "Pick3DObjectExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt);
	void Draw();
	void Suspend();
    
    

	void Event_TouchPan				(const AppInterface::PanData& data);
	void Event_TouchDown            (const AppInterface::TouchData& data);
	void Event_TouchUp              (const AppInterface::TouchData& data);

private:
	void CreateSphereAtLocation(const Eegeo::dv3& location, const Eegeo::v3& colour);
	bool IsScreenPointInsideModel(const Eegeo::v2& screenPoint);
	void CreateWorldSpaceRayFromScreen(const Eegeo::v2& screenPoint, Ray& ray);
};
}

#endif /* defined(__ExampleApp__Pick3DObjectExample__) */
