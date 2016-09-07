set(headers ${headers} ../src/Modules/VRDistortionModule/
)
set(currsources  ../src/Modules/VRDistortionModule/VRDistortionMaterial.cpp  ../src/Modules/VRDistortionModule/VRDistortionMaterial.h  ../src/Modules/VRDistortionModule/VRDistortionRenderable.cpp  ../src/Modules/VRDistortionModule/VRDistortionRenderable.h  ../src/Modules/VRDistortionModule/VRDistortionRenderer.cpp  ../src/Modules/VRDistortionModule/VRDistortionRenderer.h  ../src/Modules/VRDistortionModule/VRDistortionShader.cpp  ../src/Modules/VRDistortionModule/VRDistortionShader.h  ../src/Modules/VRDistortionModule/VRDistortionModule.cpp  ../src/Modules/VRDistortionModule/VRDistortionModule.h
  ../src/Modules/VRDistortionModule/VRDistortionIncludes.h
  ../src/Modules/VRDistortionModule/VRCardboardDeviceProfile.cpp
  ../src/Modules/VRDistortionModule/VRCardboardDeviceProfile.h
  ../src/Modules/VRDistortionModule/VRDistortionMeshHelper.cpp
  ../src/Modules/VRDistortionModule/VRDistortionMeshHelper.h
  ../src/Modules/VRDistortionModule/IVRDistortionTransitionModel.h
  ../src/Modules/VRDistortionModule/VRDistortionTransitionModel.cpp
  ../src/Modules/VRDistortionModule/VRDistortionTransitionModel.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\VRDistortionModule\\ FILES ${currsources})
