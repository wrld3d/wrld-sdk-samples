set(headers ${headers} ../src/Examples/SingleCity
)
set(currsources
  ../src/Examples/SingleCity/SingleCityExample.cpp
  ../src/Examples/SingleCity/SingleCityExample.h
  ../src/Examples/SingleCity/SingleCityExampleFactory.cpp
  ../src/Examples/SingleCity/SingleCityExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\SingleCity FILES ${currsources})
