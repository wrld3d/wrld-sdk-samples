set(headers ${headers} ../src/
)
set(currsources
  ../src/ExampleApp.cpp
  ../src/ExampleApp.h
  ../src/Logger.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\ FILES ${currsources})
include(../src/Examples/CMakeLists.txt)
