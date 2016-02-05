set(headers ${headers} ../src/Examples/Heatmap
)
set(currsources
  ../src/Examples/Heatmap/HeatmapExample.cpp
  ../src/Examples/Heatmap/HeatmapExample.h
  ../src/Examples/Heatmap/HeatmapExampleFactory.cpp
  ../src/Examples/Heatmap/HeatmapExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\Heatmap FILES ${currsources})
