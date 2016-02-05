set(headers ${headers} ../src/Examples/PolyChart
)
set(currsources
  ../src/Examples/PolyChart/PolyChartExample.cpp
  ../src/Examples/PolyChart/PolyChartExample.h
  ../src/Examples/PolyChart/PolyChartExampleFactory.cpp
  ../src/Examples/PolyChart/PolyChartExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\PolyChart FILES ${currsources})
