set(headers ${headers} ../src/Examples/StencilArea
)
set(currsources
  ../src/Examples/StencilArea/StencilAreaExample.cpp
  ../src/Examples/StencilArea/StencilAreaExample.h
  ../src/Examples/StencilArea/StencilAreaExampleFactory.cpp
  ../src/Examples/StencilArea/StencilAreaExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\StencilArea FILES ${currsources})
