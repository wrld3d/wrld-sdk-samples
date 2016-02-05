set(headers ${headers} ../src/Examples/Mesh
)
set(currsources
  ../src/Examples/Mesh/ExampleMeshRenderable.cpp
  ../src/Examples/Mesh/ExampleMeshRenderable.h
  ../src/Examples/Mesh/ExampleMeshUnlitTexturedMaterial.cpp
  ../src/Examples/Mesh/ExampleMeshUnlitTexturedMaterial.h
  ../src/Examples/Mesh/GeometryHelpers.cpp
  ../src/Examples/Mesh/GeometryHelpers.h
  ../src/Examples/Mesh/MeshExample.cpp
  ../src/Examples/Mesh/MeshExample.h
  ../src/Examples/Mesh/MeshExampleConfig.h
  ../src/Examples/Mesh/MeshExampleFactory.cpp
  ../src/Examples/Mesh/MeshExampleFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\Mesh FILES ${currsources})
