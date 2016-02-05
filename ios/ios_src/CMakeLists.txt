if(${IOS})
set(headers ${headers} ios_src/
)
set(currsources
  ios_src/AppHost.h
  ios_src/AppHost.mm
  ios_src/AppInputDelegate.h
  ios_src/AppInputDelegate.mm
  ios_src/AppLocationDelegate.h
  ios_src/AppLocationDelegate.mm
  ios_src/AppRunner.h
  ios_src/AppRunner.mm
  ios_src/GlDisplayService.h
  ios_src/GlDisplayService.mm
  ios_src/Main.m
  ios_src/ViewController.h
  ios_src/ViewController.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\ FILES ${currsources})
include(ios_src/Examples/CMakeLists.txt)
endif(${IOS})
