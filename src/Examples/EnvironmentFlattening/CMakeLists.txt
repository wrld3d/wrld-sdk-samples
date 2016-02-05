set(headers ${headers} ../src/Examples/EnvironmentFlattening
)
set(currsources
  ../src/Examples/EnvironmentFlattening/EnvironmentFlatteningExample.cpp
  ../src/Examples/EnvironmentFlattening/EnvironmentFlatteningExample.h
  ../src/Examples/EnvironmentFlattening/EnvironmentFlatteningExampleFactory.cpp
  ../src/Examples/EnvironmentFlattening/EnvironmentFlatteningExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\EnvironmentFlattening FILES ${currsources})
