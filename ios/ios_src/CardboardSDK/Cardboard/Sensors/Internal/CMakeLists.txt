if(${IOS})
set(headers ${headers} ios_src/CardboardSDK/Cardboard/Sensors/Internal
)
set(currsources
  ios_src/CardboardSDK/Cardboard/Sensors/Internal/Matrix3x3d.h
  ios_src/CardboardSDK/Cardboard/Sensors/Internal/Matrix3x3d.mm
  ios_src/CardboardSDK/Cardboard/Sensors/Internal/OrientationEKF.h
  ios_src/CardboardSDK/Cardboard/Sensors/Internal/OrientationEKF.mm
  ios_src/CardboardSDK/Cardboard/Sensors/Internal/SO3Util.h
  ios_src/CardboardSDK/Cardboard/Sensors/Internal/SO3Util.mm
  ios_src/CardboardSDK/Cardboard/Sensors/Internal/Vector3d.h
  ios_src/CardboardSDK/Cardboard/Sensors/Internal/Vector3d.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\CardboardSDK\\Cardboard\\Sensors\\Internal FILES ${currsources})
endif(${IOS})
