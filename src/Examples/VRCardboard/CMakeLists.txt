set(headers ${headers} ../src/Examples/VRCardboard
)
set(currsources  ../src/Examples/VRCardboard/IVRModeTracker.h  ../src/Examples/VRCardboard/VRCardboardExample.cpp  ../src/Examples/VRCardboard/VRCardboardExample.h
  ../src/Examples/VRCardboard/VRCameraState.h  ../src/Examples/VRCardboard/VRCardboardExampleFactory.cpp  ../src/Examples/VRCardboard/VRCardboardExampleFactory.h  ../src/Examples/VRCardboard/VRCameraController.cpp  ../src/Examples/VRCardboard/VRCameraController.h
  ../src/Examples/VRCardboard/VRCardboardController.cpp
  ../src/Examples/VRCardboard/VRCardboardController.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\VRCardboard FILES ${currsources})