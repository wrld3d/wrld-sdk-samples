set(headers ${headers} ../src/Examples/RenderToTexture
)
set(currsources
  ../src/Examples/RenderToTexture/PostProcessVignetteMaterial.cpp
  ../src/Examples/RenderToTexture/PostProcessVignetteMaterial.h
  ../src/Examples/RenderToTexture/PostProcessVignetteRenderable.cpp
  ../src/Examples/RenderToTexture/PostProcessVignetteRenderable.h
  ../src/Examples/RenderToTexture/PostProcessVignetteRenderer.cpp
  ../src/Examples/RenderToTexture/PostProcessVignetteRenderer.h
  ../src/Examples/RenderToTexture/PostProcessVignetteShader.cpp
  ../src/Examples/RenderToTexture/PostProcessVignetteShader.h
  ../src/Examples/RenderToTexture/RenderToTextureExample.cpp
  ../src/Examples/RenderToTexture/RenderToTextureExample.h
  ../src/Examples/RenderToTexture/RenderToTextureExampleFactory.cpp
  ../src/Examples/RenderToTexture/RenderToTextureExampleFactory.h
  ../src/Examples/RenderToTexture/RenderToTextureExampleIncludes.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Examples\\RenderToTexture FILES ${currsources})
