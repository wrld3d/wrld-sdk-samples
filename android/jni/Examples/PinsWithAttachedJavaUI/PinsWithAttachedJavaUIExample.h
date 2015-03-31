// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "GlobeCameraExampleBase.h"

#include "Rendering.h"
#include "Camera.h"
#include "ITextureFileLoader.h"

#include "PinsModule.h"
#include <string>

#include <jni.h>
#include "EegeoWorld.h"
#include "AndroidNativeState.h"
#include "RenderContext.h"

namespace Examples
{
/*!
 *  PinsWithAttachedJavaUIExample demonstrates how to place a pin in the 3D world, with some Java UI anchored to it
 *
 *  This is a combination of the PinsExample & the PositionJavaPinButtonExample
 */
class PinsWithAttachedJavaUIExample : public GlobeCameraExampleBase
{
private:
	// pin stuff
	Eegeo::Rendering::ITexturePageLayout* m_pPinIconsTexturePageLayout;
	Eegeo::Helpers::GLHelpers::TextureInfo m_pinIconsTexture;
	Eegeo::Pins::PinsModule* m_pPinsModule;
	std::string m_pinUserData;

	// java ui stuff
	AndroidNativeState& m_nativeState;
	Eegeo::EegeoWorld& m_world;

	int m_buttonID;
	jclass m_hudPinControllerClass;
	jobject m_hudPinController;
	jmethodID m_updateLocationMethodId;

public:
	PinsWithAttachedJavaUIExample(
	    Eegeo::EegeoWorld& world,
	    AndroidNativeState& nativeState,
	    Eegeo::Helpers::ITextureFileLoader& textureLoader,
	    Eegeo::Rendering::GlBufferPool& glBufferPool,
	    Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
	    Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
	    Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
	    Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
	    Eegeo::Rendering::RenderableFilters& renderableFilters,
	    Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
	    Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
	    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
	    const Eegeo::Rendering::ScreenProperties& screenProperties
	);
	virtual ~PinsWithAttachedJavaUIExample();

	static std::string GetName()
	{
		return "PinsWithAttachedJavaUIExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt);
	void Draw();
	void Suspend();

	void Event_TouchTap(const AppInterface::TapData& data);

private:
	void CreateExamplePins();
	void CreateJavaUIButton();
};
}
