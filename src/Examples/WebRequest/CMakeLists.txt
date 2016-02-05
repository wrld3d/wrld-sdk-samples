set(headers ${headers} ../src/Examples/WebRequest
)
set(currsources
  ../src/Examples/WebRequest/WebRequestExample.cpp
  ../src/Examples/WebRequest/WebRequestExample.h
  ../src/Examples/WebRequest/WebRequestExampleFactory.cpp
  ../src/Examples/WebRequest/WebRequestExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\WebRequest FILES ${currsources})
