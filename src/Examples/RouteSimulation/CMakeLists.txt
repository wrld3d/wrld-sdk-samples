set(headers ${headers} ../src/Examples/RouteSimulation
)
set(currsources
  ../src/Examples/RouteSimulation/IRouteSimulationExampleView.h
  ../src/Examples/RouteSimulation/IRouteSimulationExampleViewFactory.h
  ../src/Examples/RouteSimulation/RouteSimulationExample.cpp
  ../src/Examples/RouteSimulation/RouteSimulationExample.h
  ../src/Examples/RouteSimulation/RouteSimulationExampleFactory.cpp
  ../src/Examples/RouteSimulation/RouteSimulationExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\RouteSimulation FILES ${currsources})
