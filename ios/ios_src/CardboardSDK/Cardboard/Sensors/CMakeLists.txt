if(${IOS})
set(headers ${headers} ios_src/CardboardSDK/Cardboard/Sensors
)
set(currsources
  ios_src/CardboardSDK/Cardboard/Sensors/HeadTracker.h
  ios_src/CardboardSDK/Cardboard/Sensors/HeadTracker.mm
  ios_src/CardboardSDK/Cardboard/Sensors/MagnetSensor.h
  ios_src/CardboardSDK/Cardboard/Sensors/MagnetSensor.mm

)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\CardboardSDK\\Cardboard\\Sensors FILES ${currsources})
include(ios_src/CardboardSDK/Cardboard/Sensors/Internal/CMakeLists.txt)
endif(${IOS})
