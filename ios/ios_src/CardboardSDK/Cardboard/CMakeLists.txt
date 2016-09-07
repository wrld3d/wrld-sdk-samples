if(${IOS})
set(headers ${headers} ios_src/CardboardSDK/Cardboard
)
set(currsources
  ios_src/CardboardSDK/Cardboard/CardboardDeviceParams.h
  ios_src/CardboardSDK/Cardboard/CardboardDeviceParams.mm
  ios_src/CardboardSDK/Cardboard/CardboardUnity.h
  ios_src/CardboardSDK/Cardboard/CardboardUnity.mm
  ios_src/CardboardSDK/Cardboard/Distortion.h
  ios_src/CardboardSDK/Cardboard/Distortion.mm
  ios_src/CardboardSDK/Cardboard/DistortionRenderer.h
  ios_src/CardboardSDK/Cardboard/DistortionRenderer.mm
  ios_src/CardboardSDK/Cardboard/Eye.h
  ios_src/CardboardSDK/Cardboard/Eye.mm
  ios_src/CardboardSDK/Cardboard/FieldOfView.h
  ios_src/CardboardSDK/Cardboard/FieldOfView.mm
  ios_src/CardboardSDK/Cardboard/GLStateBackup.h
  ios_src/CardboardSDK/Cardboard/GLStateBackup.mm
  ios_src/CardboardSDK/Cardboard/HeadMountedDisplay.h
  ios_src/CardboardSDK/Cardboard/HeadMountedDisplay.mm
  ios_src/CardboardSDK/Cardboard/HeadTransform.mm
  ios_src/CardboardSDK/Cardboard/ScreenParams.h
  ios_src/CardboardSDK/Cardboard/ScreenParams.mm
  ios_src/CardboardSDK/Cardboard/Viewport.h
  ios_src/CardboardSDK/Cardboard/Viewport.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\CardboardSDK\\Cardboard FILES ${currsources})
include(ios_src/CardboardSDK/Cardboard/Sensors/CMakeLists.txt)
endif(${IOS})
