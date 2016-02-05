set(headers ${headers} ../src/Examples/Geofencing
)
set(currsources
  ../src/Examples/Geofencing/GeofenceExample.cpp
  ../src/Examples/Geofencing/GeofenceExample.h
  ../src/Examples/Geofencing/GeofenceExampleFactory.cpp
  ../src/Examples/Geofencing/GeofenceExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\Geofencing FILES ${currsources})
