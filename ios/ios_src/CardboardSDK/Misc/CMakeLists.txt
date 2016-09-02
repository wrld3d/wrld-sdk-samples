if(${IOS})
set(headers ${headers} ios_src/CardboardSDK/Misc
)
set(currsources
  ios_src/CardboardSDK/Misc/DebugUtils.h
  ios_src/CardboardSDK/Misc/VRGLHelpers.h
  ios_src/CardboardSDK/Misc/VRGLHelpers.m
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\CardboardSDK\\Misc FILES ${currsources})
endif(${IOS})
