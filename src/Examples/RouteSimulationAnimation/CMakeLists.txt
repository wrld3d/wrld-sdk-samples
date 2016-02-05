set(headers ${headers} ../src/Examples/RouteSimulationAnimation
)
set(currsources
  ../src/Examples/RouteSimulationAnimation/RouteSimulationAnimationExample.cpp
  ../src/Examples/RouteSimulationAnimation/RouteSimulationAnimationExample.h
  ../src/Examples/RouteSimulationAnimation/RouteSimulationAnimationExampleFactory.cpp
  ../src/Examples/RouteSimulationAnimation/RouteSimulationAnimationExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\RouteSimulationAnimation FILES ${currsources})
