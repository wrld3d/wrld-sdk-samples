set(headers ${headers} ../src/Modules/SkyboxModule/
)
set(currsources
  ../src/Modules/SkyboxModule/SkyboxModule.cpp
  ../src/Modules/SkyboxModule/SkyboxModule.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Modules\\SkyboxModule\\ FILES ${currsources})
