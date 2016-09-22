set(headers ${headers} ../src/Examples/Interiors
)
set(currsources
    ../src/Examples/Interiors/ExampleInteriorController.h
    ../src/Examples/Interiors/ExampleInteriorController.cpp
    ../src/Examples/Interiors/ExampleInteriorModule.h
    ../src/Examples/Interiors/ExampleInteriorModule.cpp
    ../src/Examples/Interiors/Interiors.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\Interiors FILES ${currsources})
