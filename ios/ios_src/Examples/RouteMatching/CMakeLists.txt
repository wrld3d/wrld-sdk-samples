if(${IOS})
set(headers ${headers} ios_src/Examples/RouteMatching
)
set(currsources
  ios_src/Examples/RouteMatching/iOSRouteMatchingExampleView.h
  ios_src/Examples/RouteMatching/iOSRouteMatchingExampleView.mm
  ios_src/Examples/RouteMatching/iOSRouteMatchingExampleViewFactory.h
  ios_src/Examples/RouteMatching/iOSRouteMatchingExampleViewFactory.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Examples\\RouteMatching FILES ${currsources})
endif(${IOS})
