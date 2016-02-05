set(headers ${headers} ../src/Examples/Fireworks
)
set(currsources
  ../src/Examples/Fireworks/FireworksExample.cpp
  ../src/Examples/Fireworks/FireworksExample.h
  ../src/Examples/Fireworks/FireworksExampleFactory.cpp
  ../src/Examples/Fireworks/FireworksExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\Fireworks FILES ${currsources})
