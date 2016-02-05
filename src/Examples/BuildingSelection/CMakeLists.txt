set(headers ${headers} ../src/Examples/BuildingSelection
)
set(currsources
  ../src/Examples/BuildingSelection/BuildingSelectionExample.cpp
  ../src/Examples/BuildingSelection/BuildingSelectionExample.h
  ../src/Examples/BuildingSelection/BuildingSelectionExampleFactory.cpp
  ../src/Examples/BuildingSelection/BuildingSelectionExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\BuildingSelection FILES ${currsources})
