set(headers ${headers} ../src/Examples/DebugPrimitiveRendering
)
set(currsources
  ../src/Examples/DebugPrimitiveRendering/DebugPrimitiveRenderingExample.cpp
  ../src/Examples/DebugPrimitiveRendering/DebugPrimitiveRenderingExample.h
  ../src/Examples/DebugPrimitiveRendering/DebugPrimitiveRenderingExampleFactory.cpp
  ../src/Examples/DebugPrimitiveRendering/DebugPrimitiveRenderingExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\DebugPrimitiveRendering FILES ${currsources})
