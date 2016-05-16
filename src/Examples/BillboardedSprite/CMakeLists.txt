set(headers ${headers} ../src/Examples/BillboardedSprite
)
set(currsources
  ../src/Examples/BillboardedSprite/BillboardedSpriteExample.cpp
  ../src/Examples/BillboardedSprite/BillboardedSpriteExample.h
  ../src/Examples/BillboardedSprite/BillboardedSpriteExampleFactory.cpp
  ../src/Examples/BillboardedSprite/BillboardedSpriteExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\BillboardedSprite FILES ${currsources})
