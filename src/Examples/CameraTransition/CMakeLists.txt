set(headers ${headers} ../src/Examples/CameraTransition
)
set(currsources
  ../src/Examples/CameraTransition/CameraTransitionExample.cpp
  ../src/Examples/CameraTransition/CameraTransitionExample.h
  ../src/Examples/CameraTransition/CameraTransitionExampleFactory.cpp
  ../src/Examples/CameraTransition/CameraTransitionExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\CameraTransition FILES ${currsources})
