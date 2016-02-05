set(headers ${headers} ../src/Examples/DynamicText3D
)
set(currsources
  ../src/Examples/DynamicText3D/DynamicText3DExample.cpp
  ../src/Examples/DynamicText3D/DynamicText3DExample.h
  ../src/Examples/DynamicText3D/DynamicText3DExampleFactory.cpp
  ../src/Examples/DynamicText3D/DynamicText3DExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\DynamicText3D FILES ${currsources})
