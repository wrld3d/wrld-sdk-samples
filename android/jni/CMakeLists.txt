set(headers ${headers} jni
)
set(sources ${sources} 
	jni/AppHost.cpp
	jni/AppInputDelegate.cpp
	jni/AppRunner.cpp
	jni/GlDisplayService.cpp
	jni/main.cpp
)


include(jni/Examples/CMakeLists.txt)