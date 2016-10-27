set(headers ${headers} ../src/Examples/RouteSelection
)
set(currsources
  ../src/Examples/RouteSelection/RouteSelectionHelper.cpp
  ../src/Examples/RouteSelection/RouteSelectionHelper.h
  ../src/Examples/RouteSelection/RouteSelectionExample.cpp
  ../src/Examples/RouteSelection/RouteSelectionExample.h
  ../src/Examples/RouteSelection/RouteSelectionExampleFactory.cpp
  ../src/Examples/RouteSelection/RouteSelectionExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\RouteSelection FILES ${currsources})
