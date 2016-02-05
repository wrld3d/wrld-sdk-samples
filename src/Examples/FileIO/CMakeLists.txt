set(headers ${headers} ../src/Examples/FileIO
)
set(currsources
  ../src/Examples/FileIO/FileIOExample.cpp
  ../src/Examples/FileIO/FileIOExample.h
  ../src/Examples/FileIO/FileIOExampleFactory.cpp
  ../src/Examples/FileIO/FileIOExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\FileIO FILES ${currsources})
