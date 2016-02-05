set(headers ${headers} ../src/Examples/ToggleTraffic
)
set(currsources
  ../src/Examples/ToggleTraffic/ToggleTrafficExample.cpp
  ../src/Examples/ToggleTraffic/ToggleTrafficExample.h
  ../src/Examples/ToggleTraffic/ToggleTrafficExampleFactory.cpp
  ../src/Examples/ToggleTraffic/ToggleTrafficExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\ToggleTraffic FILES ${currsources})
