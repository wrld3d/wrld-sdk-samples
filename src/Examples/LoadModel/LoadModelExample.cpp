// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "LoadModelExample.h"
#include "ShaderCompiler.h"
#include "Model.h"
#include "ModelMaterial.h"
#include "Mesh.h"
#include "Node.h"
#include "GlobeCameraController.h"
#include "SceneModelFactory.h"
#include "SceneModel.h"
#include "SceneModelNode.h"
#include "SceneModelMaterialResource.h"
#include "SceneModelRenderableFilter.h"
#include "DebugRenderer.h"


#include <sys/time.h>

#include "GLState.h"

namespace Examples
{

    LoadModelExample::LoadModelExample(Eegeo::Helpers::IFileIO& fileIO,
                                       Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
                                       Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory,
                                       Eegeo::Rendering::SceneModels::SceneModelFactory::TMaterialRepo& sceneModelMaterials,
                                       Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter,
                                       Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
	, m_interestLocation(Eegeo::Space::LatLongAltitude::FromECEF(pCameraController->GetEcefInterestPoint()))
	,m_fileIO(fileIO)
	,m_textureRequestor(textureRequestor)
    ,m_sceneModelFactory(sceneModelFactory)
    ,m_sceneModelMaterials(sceneModelMaterials)
    ,m_sceneModelRenderableFilter(sceneModelRenderableFilter)
    ,m_debugRenderer(debugRenderer)
	,m_pModel(NULL)
	,m_pDiscMaterialResource(NULL)
	,m_elapsedTime(0.0f)
{
}

void LoadModelExample::Start()
{
    m_pModel = m_sceneModelFactory.CreateSceneModelFromFile("load_model_example/sanfrancisco_vehicles_alpha.POD", m_fileIO, m_textureRequestor, "load_model_example");

    // Look up the material for the disc so that we can animate its alpha value.
    // Materials will be loaded into the material resource repository and id' by 'filename/materials/material name'
    std::string materialId = "load_model_example/sanfrancisco_vehicles_alpha.POD/materials/alpha_disc_material";
    
	if(!m_sceneModelMaterials.HasResource(materialId))
	{
		Eegeo_TTY("Failed to find disc material.\n");
	}
    else
    {
        // This action increments the material resource's reference count.  When suspending, decrement it again to release.
        m_pDiscMaterialResource = &m_sceneModelMaterials.UseResource(materialId);
    }

	//it should have some children, which are the vehicle meshes...
	Eegeo_ASSERT(m_pModel->GetRootNode().GetChildCount() > 0);
    
    //To render a scene model, add it to the SceneModelRenderableFilter
    m_sceneModelRenderableFilter.AddSceneModel(*m_pModel);
}

void LoadModelExample::Suspend()
{
    // Remove the model from the renderable filter when finished.
    m_sceneModelRenderableFilter.RemoveSceneModel(*m_pModel);
    
	//destroy the example...
	delete m_pModel;
	m_pModel = NULL;
    
    // When pulling out the material from the materials repository it increases the reference count.  By reducing that again it will be correctly destroyed.
    if(m_pDiscMaterialResource != NULL)
    {
        m_pDiscMaterialResource->DecrementReferenceCount();
    }
}

void LoadModelExample::Update(float dt)
{
	//let's put the vehicle in the air
	m_interestLocation.SetAltitude(100.0f);

	//put the vehicle at interest point
    m_pModel->SetEcefPosition(m_interestLocation.ToECEF());

	//up is relative to earth location, normal to tangent plane formed at surface below model
    Eegeo::v3 up = m_pModel->GetEcefPosition().Norm().ToSingle();

	//cross with north pole (0,1,0) for a forward vector
    Eegeo::v3 forward = -Eegeo::v3::Cross(up, Eegeo::v3(0.0f, 1.0f, 0.0f));
    
    // Calculate right & recalculate up for the final correct axes.
    Eegeo::v3 right(Eegeo::v3::Cross(up, forward).Norm());
    up = Eegeo::v3::Cross(forward, right);

	//set some big scale value so we can see the vehicle - vary between x20 and x70
    float scale = 20.0f + ((Eegeo::Math::Sin(m_elapsedTime)/ 2.0f + 0.5f) * 50.0f);
    Eegeo::m44 scaleMatrix;
    scaleMatrix.Scale(scale);
    
    Eegeo::m44 basisMatrix;
    basisMatrix.SetFromBasis(right, up, forward, Eegeo::v3::Zero());
    
    // And calculate and assign the final transform
    Eegeo::m44::Mul(m_transform, basisMatrix, scaleMatrix);
    m_pModel->GetRootNode().SetTransform(m_transform);

	// pulse the opacity of the disk material up and down over time.
    m_pDiscMaterialResource->GetMaterial()->SetAlpha(std::abs(Eegeo::Math::Sin(m_elapsedTime * 2)));

	m_elapsedTime += dt;
}

void LoadModelExample::Draw()
{
    // Draw debug bounds.
    m_debugRenderer.DrawSphere(m_pModel->GetEcefPosition() +  Eegeo::dv3::FromSingle(m_pModel->GetRootNode().GetSubtreeBoundingSphere().centre),
                               m_pModel->GetRootNode().GetSubtreeBoundingSphere().radius,
                               Eegeo::v4(1.0f, 0.0f, 0.0f, 0.5f));
}
}
