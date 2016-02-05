set(headers ${headers} ../src/Examples/TrafficCongestion
)
set(currsources
  ../src/Examples/TrafficCongestion/TrafficCongestionExample.cpp
  ../src/Examples/TrafficCongestion/TrafficCongestionExample.h
  ../src/Examples/TrafficCongestion/TrafficCongestionExampleFactory.cpp
  ../src/Examples/TrafficCongestion/TrafficCongestionExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\TrafficCongestion FILES ${currsources})
