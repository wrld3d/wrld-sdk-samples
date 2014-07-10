cmake_minimum_required (VERSION 2.8.12.2)

PROJECT (native-activity)
SET (OUTPUT_NAME native-activity)


# --------------- Add Library Dependencies ---------------- #

SET (LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/)

SET (LOCAL_LDLIBS "-llog -landroid -lEGL -lGLESv2 -L${LIBS_DIR} -lnative-activity-lib -L${LIBS_DIR} -lpng -lz -lm -L${LIBS_DIR} -lcrypto -L${LIBS_DIR} -lssl -L${LIBS_DIR} -lcurl -L${LIBS_DIR} -lcares -L${LIBS_DIR} -lsimd -L${LIBS_DIR} -lmyjpeg -L${LIBS_DIR} -lhttpxx-lib")

SET(LIBRARY_DEPS ${LOCAL_LDLIBS})


# --------------------- Add Sources ----------------------- #

SET( MY_C_FLAGS "-s -O2 -mthumb-interwork -mthumb -march=armv7-a -mfloat-abi=softfp -mfpu=vfp3")
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_C_FLAGS}" )
SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MY_C_FLAGS}" )

SET (ANDROID_EXAMPLE_SOURCE_DIR "jni")
SET (CROSS_PLATFORM_EXAMPLE_SOURCE_DIR "../src")
SET (CROSS_PLATFORM_EXAMPLE_SOURCES "${CROSS_PLATFORM_EXAMPLE_SOURCE_DIR}/*.cpp")

FILE (GLOB_RECURSE SourceFiles 
    "${ANDROID_EXAMPLE_SOURCE_DIR}/*.cpp"
    "${CROSS_PLATFORM_EXAMPLE_SOURCES}"
)

SET (SRC ${SourceFiles})


# ------------------- Add Includes ------------------------ #

SET (SDK_INCLUDE_DIR "./libs/")
SET (PLATFORM_DIR "${SDK_INCLUDE_DIR}/platform/")

SET (PLATFORM_INCLUDES "${PLATFORM_DIR}/*.h" "${PLATFORM_DIR}/*.hpp" "${PLATFORM_DIR}/*.impl")
SET (CURL_INCLUDES "${SDK_INCLUDE_DIR}/curl/*.h")
SET (LIB_JPEG_INCLUDES "${SDK_INCLUDE_DIR}/jpeg/*.h") 
SET (LIB_PNG_INCLUDES "${SDK_INCLUDE_DIR}/png/*.h") 
SET (LIB_HTTPX_INCLUDES "${SDK_INCLUDE_DIR}/httpxx/code/*.h ${SDK_INCLUDE_DIR}/httpxx/libs/*.h") 
SET (ANDROID_INCLUDES "${ANDROID_EXAMPLE_SOURCE_DIR}/*.h" )
SET (CROSS_PLATFORM_EXAMPLE_INCLUDES "${CROSS_PLATFORM_EXAMPLE_SOURCE_DIR}/*.h")

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
INCLUDE_DIRECTORIES(${HDR})


# -------------------- Create Library --------------------- #

if(${COMPILE_CPP_11} STREQUAL "1")
    ADD_DEFINITIONS(-std=c++11)
    ADD_DEFINITIONS(-DCOMPILE_CPP_11=1)
else(${COMPILE_CPP_11} STREQUAL "1")
    ADD_DEFINITIONS(-std=c++98)
endif(${COMPILE_CPP_11} STREQUAL "1")

ADD_LIBRARY (${OUTPUT_NAME} SHARED ${SRC})
TARGET_LINK_LIBRARIES (${OUTPUT_NAME} ${LIBRARY_DEPS})


# -------------------- Poke ndk-build --------------------- #

# get list as a string with ';' between values (cmake default seperator), then replace the ';' with a custom seperator

function(JOIN VALUES GLUE OUTPUT)
  string (REPLACE ";" "${GLUE}" _TMP_STR "${VALUES}")
  set (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()

JOIN("${HDR}" " " HDR)
JOIN("${SRC}" " " SRC) 
string (REPLACE "${ANDROID_EXAMPLE_SOURCE_DIR}/" "" SRC "${SRC}")
string (REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" SRC "${SRC}")
string (REPLACE "../src" "../../src" SRC "${SRC}")


if(${COMPILE_CPP_11} STREQUAL "1")
    SET (CPP_11_SETTINGS "NDK_TOOLCHAIN_VERSION:=4.8")
    SET (LOCAL_LDLIBS "${LOCAL_LDLIBS} -fuse-ld=bfd")
    SET (LOCAL_CPPFLAGS "-DCOMPILE_CPP_11=1 -std=c++11")
else(${COMPILE_CPP_11} STREQUAL "1")
    SET (CPP_11_SETTINGS "")
endif(${COMPILE_CPP_11} STREQUAL "1")


CONFIGURE_FILE (
    "../cmake/toolchain/android/Android.mk.in" 
    "${CMAKE_CURRENT_SOURCE_DIR}/${ANDROID_EXAMPLE_SOURCE_DIR}/Android.mk"
)

CONFIGURE_FILE (
    "../cmake/toolchain/android/Application.mk.in" 
    "${CMAKE_CURRENT_SOURCE_DIR}/${ANDROID_EXAMPLE_SOURCE_DIR}/Application.mk"
)


