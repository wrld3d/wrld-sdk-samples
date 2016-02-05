set(headers ${headers} ../src/Examples/BuildingHighlight
)
set(currsources
  ../src/Examples/BuildingHighlight/BuildingHighlightExample.cpp
  ../src/Examples/BuildingHighlight/BuildingHighlightExample.h
  ../src/Examples/BuildingHighlight/BuildingHighlightExampleFactory.cpp
  ../src/Examples/BuildingHighlight/BuildingHighlightExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\BuildingHighlight FILES ${currsources})
