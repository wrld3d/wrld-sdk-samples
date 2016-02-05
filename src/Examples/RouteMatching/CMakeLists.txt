set(headers ${headers} ../src/Examples/RouteMatching
)
set(currsources
  ../src/Examples/RouteMatching/IRouteMatchingExampleView.h
  ../src/Examples/RouteMatching/IRouteMatchingExampleViewFactory.h
  ../src/Examples/RouteMatching/RouteMatchingExample.cpp
  ../src/Examples/RouteMatching/RouteMatchingExample.h
  ../src/Examples/RouteMatching/RouteMatchingExampleFactory.cpp
  ../src/Examples/RouteMatching/RouteMatchingExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\RouteMatching FILES ${currsources})
