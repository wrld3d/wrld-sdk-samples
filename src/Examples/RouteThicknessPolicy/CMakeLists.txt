set(headers ${headers} ../src/Examples/RouteThicknessPolicy
)
set(currsources
  ../src/Examples/RouteThicknessPolicy/RouteThicknessPolicyExample.cpp
  ../src/Examples/RouteThicknessPolicy/RouteThicknessPolicyExample.h
  ../src/Examples/RouteThicknessPolicy/RouteThicknessPolicyExampleFactory.cpp
  ../src/Examples/RouteThicknessPolicy/RouteThicknessPolicyExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\RouteThicknessPolicy FILES ${currsources})
