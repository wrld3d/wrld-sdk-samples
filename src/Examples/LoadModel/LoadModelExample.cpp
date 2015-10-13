// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "LoadModelExample.h"
#include "ShaderCompiler.h"
#include "Model.h"
#include "ModelMaterial.h"
#include "Mesh.h"
#include "Node.h"
#include "GlobeCameraController.h"
#include "SceneModelLoader.h"
#include "SceneModel.h"
#include "SceneModelNode.h"
#include "SceneModelMaterialResource.h"
#include "SceneModelRenderableFilter.h"
#include "DebugRenderer.h"

#include "SceneModelTransformHelpers.h"


#include <sys/time.h>

#include "GLState.h"

namespace Examples
{

    LoadModelExample::LoadModelExample(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                       Eegeo::Rendering::SceneModels::SceneModelFactory::TMaterialRepo& sceneModelMaterials,
                                       Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter,
                                       Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                       Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
	, m_interestLocation(Eegeo::Space::LatLongAltitude::FromECEF(pCameraController->GetEcefInterestPoint()))
    ,m_sceneModelLoader(sceneModelLoader)
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
    m_pModel = m_sceneModelLoader.LoadPOD("load_model_example/sanfrancisco_vehicles_alpha.POD");

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
    
	//set some big scale value so we can see the vehicle - vary between x20 and x70
    float scale = 20.0f + ((Eegeo::Math::Sin(m_elapsedTime)/ 2.0f + 0.5f) * 50.0f);
    Eegeo::m44 scaleMatrix;
    scaleMatrix.Scale(scale);
    
    Eegeo::Rendering::SceneModels::SceneModelTransformHelpers::PositionOnEarthSurface(*m_pModel, m_interestLocation, 0.f, scaleMatrix);

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
