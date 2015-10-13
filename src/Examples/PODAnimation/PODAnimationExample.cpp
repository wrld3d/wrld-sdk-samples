// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PODAnimationExample.h"
#include "CameraHelpers.h"
#include "GLState.h"
#include "RenderCamera.h"
#include "GlobeCameraController.h"
#include "EcefTangentBasis.h"
#include "SceneModelRenderableFilter.h"
#include "SceneModel.h"
#include "SceneModelLoader.h"
#include "SceneModelNode.h"
#include "SceneModelAnimator.h"
#include "SceneModelTransformHelpers.h"

#include <sys/time.h>

namespace Examples
{
    PODAnimationExample::PODAnimationExample(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                             Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter,
                                             Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
	: GlobeCameraExampleBase(pCameraController, cameraTouchController)
    ,m_sceneModelLoader(sceneModelLoader)
    ,m_renderableFilter(renderableFilter)
	,m_pModel(NULL)
    ,m_pModelAnimator(NULL)
{
	

	
}
    
PODAnimationExample::~PODAnimationExample()
{

}

void PODAnimationExample::Start()
{
    
    // Load the model
    m_pModel = m_sceneModelLoader.LoadPOD("pod_animation_example/Test_ROBOT_ARM.pod");
    
    Eegeo::Space::EcefTangentBasis cameraInterestBasis = Eegeo::Rendering::SceneModels::SceneModelTransformHelpers::PositionOnEarthSurface(*m_pModel,
                                                                                      Eegeo::Space::LatLongAltitude::FromDegrees(37.780642, -122.385876, 16.472872f).ToECEF(),
                                                                                      0.f);

    // Set correct layer for shadowing.
    m_pModel->SetLayer(Eegeo::Rendering::LayerIds::BeforeWorldTranslucency);
    
    // Set camera to look at location
    GetGlobeCameraController().SetView(cameraInterestBasis, 1209.007812f);
    
    // Create an animator to animate the model
    const u32 fps = 30;
    m_pModelAnimator = new Eegeo::Rendering::SceneModels::SceneModelAnimator(*m_pModel, fps);
    m_pModelAnimator->Play();
    
    // Add the model to the renderable filter so it will be queued and drawn by the SDK's rendering system.
    m_renderableFilter.AddSceneModel(*m_pModel);
}

void PODAnimationExample::Suspend()
{
    delete m_pModelAnimator;
    m_pModelAnimator = NULL;
    
    m_renderableFilter.RemoveSceneModel(*m_pModel);
    
    delete m_pModel;
    m_pModel = NULL;
}

void PODAnimationExample::Update(float dt)
{
    m_pModelAnimator->Update(dt);
}

void PODAnimationExample::Draw()
{

}
}
