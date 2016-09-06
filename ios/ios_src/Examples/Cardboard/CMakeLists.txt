if(${IOS})
set(headers ${headers} ios_src/Examples/Cardboard
)
set(currsources
    ios_src/Examples/Cardboard/IosVRModeTracker.cpp    ios_src/Examples/Cardboard/IosVRModeTracker.h
    ios_src/Examples/Cardboard/CardboardSDKService.h    ios_src/Examples/Cardboard/CardboardSDKService.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Examples\\Cardboard FILES ${currsources})
endif(${IOS})
