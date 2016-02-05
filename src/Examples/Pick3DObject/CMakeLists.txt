set(headers ${headers} ../src/Examples/Pick3DObject
)
set(currsources
  ../src/Examples/Pick3DObject/Pick3DObjectExample.cpp
  ../src/Examples/Pick3DObject/Pick3DObjectExample.h
  ../src/Examples/Pick3DObject/Pick3DObjectExampleFactory.cpp
  ../src/Examples/Pick3DObject/Pick3DObjectExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\Pick3DObject FILES ${currsources})
