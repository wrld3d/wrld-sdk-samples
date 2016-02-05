set(headers ${headers} ../src/Examples/CameraSpline
)
set(currsources
  ../src/Examples/CameraSpline/CameraSplineExample.cpp
  ../src/Examples/CameraSpline/CameraSplineExample.h
  ../src/Examples/CameraSpline/CameraSplineExampleFactory.cpp
  ../src/Examples/CameraSpline/CameraSplineExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\CameraSpline FILES ${currsources})
