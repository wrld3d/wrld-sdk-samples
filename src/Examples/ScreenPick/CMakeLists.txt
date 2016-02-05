set(headers ${headers} ../src/Examples/ScreenPick
)
set(currsources
  ../src/Examples/ScreenPick/ScreenPickExample.cpp
  ../src/Examples/ScreenPick/ScreenPickExample.h
  ../src/Examples/ScreenPick/ScreenPickExampleFactory.cpp
  ../src/Examples/ScreenPick/ScreenPickExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\ScreenPick FILES ${currsources})
