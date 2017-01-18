set(headers ${headers} ../src/Examples/Markers
)
set(currsources
  ../src/Examples/Markers/MarkersExample.cpp
  ../src/Examples/Markers/MarkersExample.h
  ../src/Examples/Markers/MarkersExampleFactory.cpp
  ../src/Examples/Markers/MarkersExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\Markers FILES ${currsources})
