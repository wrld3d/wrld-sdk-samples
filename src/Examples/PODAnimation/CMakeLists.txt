set(headers ${headers} ../src/Examples/PODAnimation
)
set(currsources
  ../src/Examples/PODAnimation/PODAnimationExample.cpp
  ../src/Examples/PODAnimation/PODAnimationExample.h
  ../src/Examples/PODAnimation/PODAnimationExampleFactory.cpp
  ../src/Examples/PODAnimation/PODAnimationExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\PODAnimation FILES ${currsources})
