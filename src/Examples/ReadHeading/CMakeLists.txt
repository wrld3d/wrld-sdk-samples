set(headers ${headers} ../src/Examples/ReadHeading
)
set(currsources
  ../src/Examples/ReadHeading/ReadHeadingExample.cpp
  ../src/Examples/ReadHeading/ReadHeadingExample.h
  ../src/Examples/ReadHeading/ReadHeadingExampleFactory.cpp
  ../src/Examples/ReadHeading/ReadHeadingExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\ReadHeading FILES ${currsources})
