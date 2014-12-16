// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PODAnimationExample.h"
#include "ShaderCompiler.h"
#include "CameraHelpers.h"
#include "Model.h"
#include "Node.h"
#include "GLState.h"
#include "RenderCamera.h"
#include "RenderableFilters.h"
#include "RenderQueue.h"
#include "LayerIds.h"
#include "NullMaterial.h"
#include "NullMaterialFactory.h"
#include "EffectHandler.h"
#include "GlobeCameraController.h"
#include "EcefTangentBasis.h"

#include <sys/time.h>

namespace Examples
{
    PODAnimationExample::PODAnimationExample(Eegeo::Helpers::IFileIO& fileIO,
                                             Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
                                             Eegeo::Lighting::GlobalFogging& fogging,
                                             Eegeo::Rendering::RenderableFilters& renderableFilters,
                                             Eegeo::Rendering::Materials::NullMaterialFactory& nullMaterialFactory,
                                             Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
	: GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_fileIO(fileIO)
	,m_textureRequestor(textureRequestor)
	,m_pModel(NULL)
    ,m_pMyModelRenderable(NULL)
    ,m_pMyRenderableFilter(NULL)
	,m_globalFogging(fogging)
    ,m_renderableFilters(renderableFilters)
    ,m_nullMaterialFactory(nullMaterialFactory)
    ,m_pNullMaterial(NULL)
{
	Eegeo::Space::EcefTangentBasis cameraInterestBasis;

	Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
	    Eegeo::Space::LatLong::FromDegrees(37.780642, -122.385876).ToECEF(),
	    16.472872f,
	    cameraInterestBasis);

	pCameraController->SetView(cameraInterestBasis, 1209.007812f);
}
    
PODAnimationExample::~PODAnimationExample()
{
    m_renderableFilters.RemoveRenderableFilter(*m_pMyRenderableFilter);
    
	Eegeo_DELETE m_pMyRenderableFilter;
	Eegeo_DELETE m_pMyModelRenderable;
    Eegeo_DELETE m_pNullMaterial;
}

void PODAnimationExample::Start()
{
	m_pModel = Eegeo::Model::CreateFromPODFile("pod_animation_example/Test_ROBOT_ARM.pod", m_fileIO, &m_textureRequestor, "pod_animation_example/");
	Eegeo_ASSERT(m_pModel->GetRootNode());
    
    m_pNullMaterial = m_nullMaterialFactory.Create("PODAnimationExampleNullMaterial");
    
    m_pMyModelRenderable = Eegeo_NEW (MyModelRenderable)(*m_pModel, m_globalFogging, *m_pNullMaterial, GetRenderCamera());
	m_pMyRenderableFilter = Eegeo_NEW (MyRenderableFilter)(*m_pMyModelRenderable);
	m_renderableFilters.AddRenderableFilter(*m_pMyRenderableFilter);
}

void PODAnimationExample::Suspend()
{
	delete m_pModel;
	m_pModel = NULL;
    
    
    
}

void PODAnimationExample::Update(float dt)
{
	m_pModel->UpdateAnimator(1.0f/30.0f);
}

void PODAnimationExample::Draw()
{

}

PODAnimationExample::MyModelRenderable::MyModelRenderable(Eegeo::Model& model,
                                                          Eegeo::Lighting::GlobalFogging& globalFogging,
                                                          Eegeo::Rendering::Materials::NullMaterial& nullMat,
                                                          const Eegeo::Camera::RenderCamera& renderCamera)
: Eegeo::Rendering::RenderableBase(Eegeo::Rendering::LayerIds::Buildings,
                                   Eegeo::dv3(4256955.9749164,3907407.6184668,-2700108.75541722),
                                   &nullMat)
, m_model(model)
, m_globalFogging(globalFogging)
, m_renderCamera(renderCamera)
{
    
}
    
PODAnimationExample::MyRenderableFilter::MyRenderableFilter(Eegeo::Rendering::RenderableBase& renderable)
: m_renderable(renderable)
{
    
}
                                                          
void PODAnimationExample::MyRenderableFilter::EnqueueRenderables(const Eegeo::Rendering::RenderContext &renderContext, Eegeo::Rendering::RenderQueue &renderQueue)
{
    renderQueue.EnqueueRenderable(m_renderable);
}
    
void PODAnimationExample::MyModelRenderable::Render(Eegeo::Rendering::GLState &glState) const
{
    //create basis around a known location off coast of SF
	Eegeo::m44 transform;
    Eegeo::dv3 location = m_ecefPosition;
	Eegeo::v3 up(location.Norm().ToSingle());
	Eegeo::v3 forward = (location  - Eegeo::v3(0.f, 1.f, 0.f)).Norm().ToSingle();
	Eegeo::v3 right(Eegeo::v3::Cross(up, forward).Norm());
	forward = Eegeo::v3::Cross(up, right);
	Eegeo::v3 cameraRelativePos = (location - m_renderCamera.GetEcefLocation()).ToSingle();
    
	Eegeo::m44 scaleMatrix;
	scaleMatrix.Scale(1.f);
	Eegeo::m44 cameraRelativeTransform;
	cameraRelativeTransform.SetFromBasis(right, up, forward, cameraRelativePos);
	Eegeo::m44::Mul(transform, cameraRelativeTransform, scaleMatrix);
	transform.SetRow(3, Eegeo::v4(cameraRelativePos, 1.f));
    
	glState.DepthTest.Enable();
	glState.DepthFunc(GL_LEQUAL);
    
	//loaded model faces are ccw
	glState.FrontFace(GL_CCW);
    
	m_model.GetRootNode()->SetVisible(true);
	m_model.GetRootNode()->SetLocalMatrix(transform);
	m_model.GetRootNode()->UpdateRecursive();
	m_model.GetRootNode()->UpdateSphereRecursive();
	m_model.GetRootNode()->DrawRecursive(glState, m_globalFogging, NULL, true, false);
    
	glState.FrontFace(GL_CW);
    
    Eegeo::EffectHandler::Reset();
}

}
