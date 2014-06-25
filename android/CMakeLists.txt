cmake_minimum_required (VERSION 2.8.12.2)

PROJECT (my-project)


SET( MY_C_FLAGS "-s -O2 -mthumb-interwork -mthumb -march=armv7-a -mfloat-abi=softfp -mfpu=vfp3")
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_C_FLAGS}" )
SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MY_C_FLAGS}" )

SET (LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/)
#LINK_DIRECTORIES(${LIBS_DIR})

SET(LIBRARY_DEPS -llog -landroid -lEGL -lGLESv2 -L${LIBS_DIR} -lnative-activity-lib -L${LIBS_DIR} -lpng -lz -lm -L${LIBS_DIR} -lcrypto -L${LIBS_DIR} -lssl -L${LIBS_DIR} -lcurl -L${LIBS_DIR} -lcares -L${LIBS_DIR} -lsimd -L${LIBS_DIR} -lmyjpeg)

SET (ANDROID_EXAMPLE_SOURCE_DIR "jni/")
SET (CROSS_PLATFORM_EXAMPLE_SOURCE_DIR "../src/")

SET (CROSS_PLATFORM_EXAMPLE_SOURCES "${CROSS_PLATFORM_EXAMPLE_SOURCE_DIR}/*.cpp")
FILE (GLOB_RECURSE SourceFiles 
    "${ANDROID_EXAMPLE_SOURCE_DIR}/*.cpp"
    "${CROSS_PLATFORM_EXAMPLE_SOURCES}"
)

 SET (SRC ${SourceFiles})
# SET (SRC test.cpp)

SET (SDK_INCLUDE_DIR "./libs/")
SET (PLATFORM_DIR "${SDK_INCLUDE_DIR}/platform/")

SET (PLATFORM_INCLUDES "${PLATFORM_DIR}/*.h" "${PLATFORM_DIR}/*.hpp" "${PLATFORM_DIR}/*.impl")
SET (CURL_INCLUDES "${SDK_INCLUDE_DIR}/curl/*.h")
SET (LIB_JPEG_INCLUDES "${SDK_INCLUDE_DIR}/jpeg/*.h") 
SET (LIB_PNG_INCLUDES "${SDK_INCLUDE_DIR}/png/*.h") 
SET (ANDROID_INCLUDES "${ANDROID_EXAMPLE_SOURCE_DIR}/*.h" )
SET (CROSS_PLATFORM_EXAMPLE_INCLUDES "${CROSS_PLATFORM_EXAMPLE_SOURCE_DIR}/*.h")

# Includes
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list 
    	${PLATFORM_INCLUDES} 
    	${CURL_INCLUDES} 
    	${LIB_JPEG_INCLUDES} 
    	${LIB_PNG_INCLUDES} 
    	${ANDROID_INCLUDES} 
    	${CROSS_PLATFORM_EXAMPLE_INCLUDES}
    )
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(HeaderDirectories)
SET (HDR ${HeaderDirectories})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -fPIC" )

INCLUDE_DIRECTORIES(${HDR})

# building .a works fine
# add_library(platform-sdk STATIC ${SRC})

#SET (LINKER_FLAGS "${LINKER_FLAGS} -Wl,--as-needed -Wl,--gc-sections -Wl,--no-undefined -Wl,--strip-all -Wl,-rpath-#link=${ANDROID_NDK_SYSROOT}/usr/lib/ -L${ANDROID_NDK_SYSROOT}/usr/lib/")

add_library(platform-sdk SHARED ${SRC})

target_link_libraries(platform-sdk ${LIBRARY_DEPS})



#include("../toolchain/Apk.cmake" REQUIRED) 
#set_target_properties(platform-sdk PROPERTIES COMPILE_DEFINITIONS "ANDROID")
#set(APP_SHARED_LIBRARIES ${LIBRARY_OUTPUT_PATH}/libplatform-sdk.so)
#android_create_apk(platform-sdk "${CMAKE_BINARY_DIR}/apk" "${APP_SHARED_LIBRARIES}" "assets" "./")



