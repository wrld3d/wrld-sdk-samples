set(headers ${headers} ../src/Examples/ResourceSpatialQuery
)
set(currsources
  ../src/Examples/ResourceSpatialQuery/ResourceSpatialQueryExample.cpp
  ../src/Examples/ResourceSpatialQuery/ResourceSpatialQueryExample.h
  ../src/Examples/ResourceSpatialQuery/ResourceSpatialQueryExampleFactory.cpp
  ../src/Examples/ResourceSpatialQuery/ResourceSpatialQueryExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\ResourceSpatialQuery FILES ${currsources})
