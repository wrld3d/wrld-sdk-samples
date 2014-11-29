// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__LoadModelExample__
#define __ExampleApp__LoadModelExample__

#include "IExample.h"
#include "RenderCamera.h"
#include "LatLongAltitude.h"
#include "IAsyncTextureRequestor.h"
#include "Model.h"

namespace Examples
{
class BoundsVisualiser
{
	struct Shader
	{
		int m_positionSlot;
		int m_mvpUniform;
		u32 m_programHandle;
	};

	struct Vertex
	{
		float m_x, m_y, m_z;
	};

	static const size_t NumVerts;
	static const size_t NumIndices;
	Shader* m_pShader;
	u32 m_glVertexBuffer;
	u32 m_glIndexBuffer;

	std::string VertexShader();
	std::string FragmentShader();
	void CompileShaders();
	void InitMeshGLBuffers(Vertex* verts, u16* indices);
	void Build(const Eegeo::v3& minExtents, const Eegeo::v3& maxExtents);
	void DestroyGeometry();

public:
	BoundsVisualiser();
	~BoundsVisualiser();

	void Draw(const Eegeo::v3& minExtents, const Eegeo::v3& maxExtents, const Eegeo::Camera::RenderCamera& renderCamera);
};


class LoadModelExample : public IExample
{
private:
	struct MeshInstance
	{
		float m_scale;
		Eegeo::dv3 m_positionEcef;
		Eegeo::v3 m_forward;
		Eegeo::v3 m_up;
		Eegeo::Node* m_pNode;
	};

	Eegeo::Helpers::IFileIO& m_fileIO;
	Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& m_textureRequestor;
	Eegeo::Space::LatLongAltitude m_interestLocation;
	Eegeo::Lighting::GlobalFogging& m_globalFogging;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;
    Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pCameraController;

	Eegeo::Model* m_pModel;
	BoundsVisualiser m_boundsVisualiser;
	MeshInstance m_mesh;
	Eegeo::ModelMaterial* m_pDiscMaterial;
	float m_elapsedTime;

public:
	LoadModelExample(
	                 Eegeo::Helpers::IFileIO& fileIO,
	                 Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
	                 Eegeo::Lighting::GlobalFogging& fogging,
	                 Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController);

	static std::string GetName()
	{
		return "LoadModelExample";
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
    Eegeo::dv3 GetInterestPoint() const;
};
}


#endif /* defined(__ExampleApp__LoadModelExample__) */
