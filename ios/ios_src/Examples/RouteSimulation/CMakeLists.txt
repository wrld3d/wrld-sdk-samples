if(${IOS})
set(headers ${headers} ios_src/Examples/RouteSimulation
)
set(currsources
  ios_src/Examples/RouteSimulation/iOSRouteSimulationExampleView.h
  ios_src/Examples/RouteSimulation/iOSRouteSimulationExampleView.mm
  ios_src/Examples/RouteSimulation/iOSRouteSimulationExampleViewFactory.h
  ios_src/Examples/RouteSimulation/iOSRouteSimulationExampleViewFactory.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Examples\\RouteSimulation FILES ${currsources})
endif(${IOS})
