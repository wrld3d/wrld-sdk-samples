set(headers ${headers} ../src/Examples/NavigationGraph
)
set(currsources
  ../src/Examples/NavigationGraph/NavigationGraphExample.cpp
  ../src/Examples/NavigationGraph/NavigationGraphExample.h
  ../src/Examples/NavigationGraph/NavigationGraphExampleFactory.cpp
  ../src/Examples/NavigationGraph/NavigationGraphExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\NavigationGraph FILES ${currsources})
