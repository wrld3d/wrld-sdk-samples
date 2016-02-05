set(headers ${headers} ../src/Examples/EnvironmentNotifier
)
set(currsources
  ../src/Examples/EnvironmentNotifier/EnvironmentNotifierExample.cpp
  ../src/Examples/EnvironmentNotifier/EnvironmentNotifierExample.h
  ../src/Examples/EnvironmentNotifier/EnvironmentNotifierExampleFactory.cpp
  ../src/Examples/EnvironmentNotifier/EnvironmentNotifierExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\EnvironmentNotifier FILES ${currsources})
