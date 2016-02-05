if(${IOS})
set(headers ${headers} ios_src/Examples
)
set(currsources
  ios_src/Examples/iOSExampleControllerView.h
  ios_src/Examples/iOSExampleControllerView.mm
  ios_src/Examples/iOSUIHelpers.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Examples FILES ${currsources})
include(ios_src/Examples/RouteMatching/CMakeLists.txt)
include(ios_src/Examples/RouteSimulation/CMakeLists.txt)
endif(${IOS})
