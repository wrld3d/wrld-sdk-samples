set(headers ${headers} ../src/Examples/LoadModel
)
set(currsources
  ../src/Examples/LoadModel/LoadModelExample.cpp
  ../src/Examples/LoadModel/LoadModelExample.h
  ../src/Examples/LoadModel/LoadModelExampleFactory.cpp
  ../src/Examples/LoadModel/LoadModelExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\LoadModel FILES ${currsources})
