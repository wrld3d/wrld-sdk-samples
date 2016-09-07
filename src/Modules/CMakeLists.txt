set(headers ${headers} ../src/Modules/
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\ FILES ${currsources})
include(../src/Modules/VRDistortionModule/CMakeLists.txt)
include(../src/Modules/SkyboxModule/CMakeLists.txt)
