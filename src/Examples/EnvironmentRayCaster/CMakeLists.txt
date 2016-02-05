set(headers ${headers} ../src/Examples/EnvironmentRayCaster
)
set(currsources
  ../src/Examples/EnvironmentRayCaster/EnvironmentRayCasterExample.cpp
  ../src/Examples/EnvironmentRayCaster/EnvironmentRayCasterExample.h
  ../src/Examples/EnvironmentRayCaster/EnvironmentRayCasterExampleFactory.cpp
  ../src/Examples/EnvironmentRayCaster/EnvironmentRayCasterExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\EnvironmentRayCaster FILES ${currsources})
