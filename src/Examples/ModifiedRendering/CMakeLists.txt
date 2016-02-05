set(headers ${headers} ../src/Examples/ModifiedRendering
)
set(currsources
  ../src/Examples/ModifiedRendering/ModifiedRenderingExample.cpp
  ../src/Examples/ModifiedRendering/ModifiedRenderingExample.h
  ../src/Examples/ModifiedRendering/ModifiedRenderingExampleFactory.cpp
  ../src/Examples/ModifiedRendering/ModifiedRenderingExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\ModifiedRendering FILES ${currsources})
