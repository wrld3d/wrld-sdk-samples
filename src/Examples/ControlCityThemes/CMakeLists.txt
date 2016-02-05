set(headers ${headers} ../src/Examples/ControlCityThemes
)
set(currsources
  ../src/Examples/ControlCityThemes/ControlCityThemeExample.cpp
  ../src/Examples/ControlCityThemes/ControlCityThemeExample.h
  ../src/Examples/ControlCityThemes/ControlCityThemeExampleFactory.cpp
  ../src/Examples/ControlCityThemes/ControlCityThemeExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\ControlCityThemes FILES ${currsources})
