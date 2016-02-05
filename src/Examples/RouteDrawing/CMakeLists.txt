set(headers ${headers} ../src/Examples/RouteDrawing
)
set(currsources
  ../src/Examples/RouteDrawing/RouteDrawingExample.cpp
  ../src/Examples/RouteDrawing/RouteDrawingExample.h
  ../src/Examples/RouteDrawing/RouteDrawingExampleFactory.cpp
  ../src/Examples/RouteDrawing/RouteDrawingExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\RouteDrawing FILES ${currsources})
