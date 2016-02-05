set(headers ${headers} ../src/Examples/RemoveMapLayer
)
set(currsources
  ../src/Examples/RemoveMapLayer/RemoveMapLayerExample.cpp
  ../src/Examples/RemoveMapLayer/RemoveMapLayerExample.h
  ../src/Examples/RemoveMapLayer/RemoveMapLayerExampleFactory.cpp
  ../src/Examples/RemoveMapLayer/RemoveMapLayerExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\RemoveMapLayer FILES ${currsources})
