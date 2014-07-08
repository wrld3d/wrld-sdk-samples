set(headers ${headers} ios_src/Examples
)
set(sources ${sources} 
	ios_src/Examples/iOSExampleControllerView.mm
)


include(ios_src/Examples/RouteMatching/CMakeLists.txt)
include(ios_src/Examples/RouteSimulation/CMakeLists.txt)