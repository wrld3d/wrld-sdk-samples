// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__LoadModelExample__
#define __ExampleApp__LoadModelExample__

#include "GlobeCameraExampleBase.h"
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
		int positionSlot;
		int mvpUniform;
		u32 programHandle;
	};

	struct Vertex
	{
		float x, y, z;
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


class LoadModelExample : public GlobeCameraExampleBase
{
private:
	struct MeshInstance
	{
		float scale;
		Eegeo::dv3 positionEcef;
		Eegeo::v3 forward;
		Eegeo::v3 up;
		Eegeo::Node* pNode;
	};

	Eegeo::Helpers::IFileIO& m_fileIO;
	Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& m_textureRequestor;
	Eegeo::Space::LatLongAltitude m_interestLocation;
	Eegeo::Lighting::GlobalFogging& m_globalFogging;
    

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
	                 Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

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
    
    
};
}


#endif /* defined(__ExampleApp__LoadModelExample__) */
