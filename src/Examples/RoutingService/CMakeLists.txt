set(headers ${headers} ../src/Examples/RoutingService
)
set(currsources
  ../src/Examples/RoutingService/RoutingServiceExample.cpp
  ../src/Examples/RoutingService/RoutingServiceExample.h
  ../src/Examples/RoutingService/RoutingServiceExampleFactory.cpp
  ../src/Examples/RoutingService/RoutingServiceExampleFactory.h
  ../src/Examples/RoutingService/IRoutingServiceExampleView.h
  ../src/Examples/RoutingService/IRoutingServiceExampleViewFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\RoutingService FILES ${currsources})
