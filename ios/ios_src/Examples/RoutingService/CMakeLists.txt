if(${IOS})
set(headers ${headers} ios_src/Examples/RoutingService
)
set(currsources
  ios_src/Examples/RoutingService/iOSRoutingServiceExampleView.h
  ios_src/Examples/RoutingService/iOSRoutingServiceExampleView.mm
  ios_src/Examples/RoutingService/iOSRoutingServiceExampleViewFactory.h
  ios_src/Examples/RoutingService/iOSRoutingServiceExampleViewFactory.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Examples\\RoutingService FILES ${currsources})
endif(${IOS})
