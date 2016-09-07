if(${IOS})
set(headers ${headers} ios_src/CardboardSDK
)
set(currsources
  ios_src/CardboardSDK/CardboardSDK.h
  ios_src/CardboardSDK/CBDStereoGLView.h
  ios_src/CardboardSDK/CBDStereoGLView.m
  ios_src/CardboardSDK/CBDViewController.h
  ios_src/CardboardSDK/CBDViewController.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\CardboardSDK FILES ${currsources})
include(ios_src/CardboardSDK/Cardboard/CMakeLists.txt)
include(ios_src/CardboardSDK/Misc/CMakeLists.txt)
endif(${IOS})
