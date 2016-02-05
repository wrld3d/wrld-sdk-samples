set(headers ${headers} ../src/Examples/Pins
)
set(currsources
  ../src/Examples/Pins/PinsExample.cpp
  ../src/Examples/Pins/PinsExample.h
  ../src/Examples/Pins/PinsExampleFactory.cpp
  ../src/Examples/Pins/PinsExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\Pins FILES ${currsources})
