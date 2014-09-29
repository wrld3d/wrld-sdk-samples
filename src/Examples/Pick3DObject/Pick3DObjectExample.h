// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__Pick3DObjectExample__
#define __ExampleApp__Pick3DObjectExample__

#include <iostream>

#include "IExample.h"
#include "RenderContext.h"
#include "SphereMesh.h"
#include "LatLongAltitude.h"
#include "VectorMath.h"

namespace Examples
{
class Pick3DObjectExample : public IExample
{
private:
	struct Ray
	{
		Eegeo::dv3 m_origin;
		Eegeo::v3 m_direction;
	};

	bool m_movingObject;
	Eegeo::DebugRendering::SphereMesh* m_pObject;
	Eegeo::dv3 m_objectLocationEcef;
    Eegeo::v4 m_objectColor;
    
    Eegeo::Space::LatLongAltitude m_interestLocation;
    const Eegeo::Rendering::ScreenProperties& m_screenProperties;
    Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;

	GlobeCameraStateRestorer m_globeCameraStateRestorer;
    Eegeo::Camera::GlobeCamera::GlobeCameraController& m_cameraController;

public:
	Pick3DObjectExample(Eegeo::Space::LatLongAltitude interestLocation,
                        const Eegeo::Rendering::ScreenProperties& screenProperties,
                        Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                        Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

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
    const Eegeo::Camera::RenderCamera& GetRenderCamera() const;

	bool Event_TouchPan				(const AppInterface::PanData& data);
	bool Event_TouchDown            (const AppInterface::TouchData& data);
	bool Event_TouchUp              (const AppInterface::TouchData& data);

private:
	void CreateSphereAtLocation(const Eegeo::dv3& location, const Eegeo::v3& colour);
	bool IsScreenPointInsideModel(const Eegeo::v2& screenPoint);
	void CreateWorldSpaceRayFromScreen(const Eegeo::v2& screenPoint, Ray& ray);
};
}

#endif /* defined(__ExampleApp__Pick3DObjectExample__) */
