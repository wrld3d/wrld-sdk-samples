set(headers ${headers} ../src/Examples/UI
)
set(currsources
  ../src/Examples/UI/IUIActionHandler.h
  ../src/Examples/UI/UIActionHandler.h
  ../src/Examples/UI/UIHelpers.cpp
  ../src/Examples/UI/UIHelpers.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\UI FILES ${currsources})
