set(headers ${headers} ../src/Examples/VRCardboard
)
set(currsources  ../src/Examples/VRCardboard/IVRModeTracker.h  ../src/Examples/VRCardboard/VRCardboardExample.cpp  ../src/Examples/VRCardboard/VRCardboardExample.h  ../src/Examples/VRCardboard/VRCardboardExampleFactory.cpp  ../src/Examples/VRCardboard/VRCardboardExampleFactory.h  ../src/Examples/VRCardboard/VRCameraController.cpp  ../src/Examples/VRCardboard/VRCameraController.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\VRCardboard FILES ${currsources})