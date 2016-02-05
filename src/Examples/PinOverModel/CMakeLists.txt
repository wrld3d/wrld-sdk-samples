set(headers ${headers} ../src/Examples/PinOverModel
)
set(currsources
  ../src/Examples/PinOverModel/PinOverModelExample.cpp
  ../src/Examples/PinOverModel/PinOverModelExample.h
  ../src/Examples/PinOverModel/PinOverModelExampleFactory.cpp
  ../src/Examples/PinOverModel/PinOverModelExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\PinOverModel FILES ${currsources})
