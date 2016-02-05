set(headers ${headers} ../src/Examples/ScreenUnproject
)
set(currsources
  ../src/Examples/ScreenUnproject/ScreenUnprojectExample.cpp
  ../src/Examples/ScreenUnproject/ScreenUnprojectExample.h
  ../src/Examples/ScreenUnproject/ScreenUnprojectExampleFactory.cpp
  ../src/Examples/ScreenUnproject/ScreenUnprojectExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\ScreenUnproject FILES ${currsources})
