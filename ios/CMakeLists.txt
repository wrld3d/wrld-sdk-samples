
cmake_minimum_required (VERSION 2.8.12.2)
PROJECT(platform-sdk CXX C)
SET(NAME platform-sdk)

# Source files
SET (IOS_EXAMPLE_SOURCE_DIR "ios_src/")
SET (CROSS_PLATFORM_EXAMPLE_SOURCE_DIR "../src/")

SET (CROSS_PLATFORM_EXAMPLE_SOURCES "${CROSS_PLATFORM_EXAMPLE_SOURCE_DIR}/*.cpp")
FILE (GLOB_RECURSE SourceFiles 
    "${IOS_EXAMPLE_SOURCE_DIR}/*.m" 
    "${IOS_EXAMPLE_SOURCE_DIR}/*.mm" 
    "${IOS_EXAMPLE_SOURCE_DIR}/*.cpp"
    "${CROSS_PLATFORM_EXAMPLE_SOURCES}"
)

SET (SRC ${SourceFiles})

# Headers
SET (SDK_INCLUDE_DIR "Include/")
SET (PLATFORM_DIR "${SDK_INCLUDE_DIR}/platform/")
SET (PLATFORM_INCLUDES "${PLATFORM_DIR}/*.h" "${PLATFORM_DIR}/*.hpp" "${PLATFORM_DIR}/*.impl")

SET (ASI_INCLUDES "${SDK_INCLUDE_DIR}/ASIHttpRequest/*.h")
SET (LIB_JPEG_INCLUDES "${SDK_INCLUDE_DIR}/ios-libjpeg-turbo/*.h") 
SET (IOS_INCLUDES "${IOS_EXAMPLE_SOURCE_DIR}/*.h" )
SET (CROSS_PLATFORM_EXAMPLE_INCLUDES "${CROSS_PLATFORM_EXAMPLE_SOURCE_DIR}/*.h")
FILE (GLOB_RECURSE HeaderFiles 
	"${PLATFORM_INCLUDES}" 	
	"${IOS_INCLUDES}"
	"${CROSS_PLATFORM_EXAMPLE_INCLUDES}"
)
SET (HDR ${HeaderFiles})

SET(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
SET(CMAKE_OSX_ARCHITECTURES "armv7;i386")
#SET(CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT))
SET(CMAKE_CXX_FLAGS "-x objective-c++")

SET(CMAKE_EXE_LINKER_FLAGS
    "-framework CoreLocation -framework MobileCoreServices -framework SystemConfiguration -framework CFNetwork -framework GLKit -framework OpenGLES -framework UIKit -framework Foundation -framework CoreGraphics -framework CoreData -LInclude/ -lapps-on-maps -LInclude/ -lapps-on-maps-sim -LInclude/ -lturbojpeg -Lusr/lib/ -lz"
)

# Includes
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list "${SDK_INCLUDE_DIR}/*.h" "ios_src/*.h" "../src/*.h")
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(HeaderDirectories)
include_directories (${HeaderDirectories})

SET(APP_TYPE MACOSX_BUNDLE)



#MACRO(RESOURCE_DIRECTORIES return_list)
#    FILE(GLOB_RECURSE new_list "Resources/*.png" "Resources/*.POD" "Resources/*.pvr" "Resources/*.fnt")
#    SET(dir_list "")
#    FOREACH(file_path ${new_list})
#        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
#        SET(dir_list ${dir_list} ${dir_path})
#    ENDFOREACH()
#    LIST(REMOVE_DUPLICATES dir_list)
#    SET(${return_list} ${dir_list})
#ENDMACRO()

#RESOURCE_DIRECTORIES(Resources)

FILE (GLOB_RECURSE Resources "Resources/*.png" "Resources/*.POD" "Resources/*.pvr" "Resources/*.fnt")

add_executable(
	${NAME}
    ${APP_TYPE}
   	${SourceFiles}
    ${HeaderFiles}
    ${Resources}
)

# set plist template and properties

set_target_properties(
    ${NAME} 
    PROPERTIES 
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/ios_src/App-Info.plist.in"
    RESOURCE "${Resources}" 
)

#SET (MACOSX_BUNDLE_GUI_IDENTIFIER "com.company.\${NAME:identifier}")
SET (MACOSX_BUNDLE_GUI_IDENTIFIER "com.eegeo.testing")
SET (MACOSX_BUNDLE_SHORT_VERSION_STRING "1.1")
SET (MACOSX_BUNDLE_LONG_VERSION_STRING "1.0")
SET (MACOSX_BUNDLE_BUNDLE_VERSION "1.0")
SET (MACOSX_BUNDLE_BUNDLE_NAME "MyApp!")


# set xcode proj properties
set_xcode_property (${NAME} CODE_SIGN_IDENTITY "iPhone Developer")
set_xcode_property (${NAME} CLANG_CXX_LANGUAGE_STANDARD "c++98")
set_xcode_property (${NAME} CLANG_CXX_LIBRARY "libstdc++")
set_xcode_property (${NAME} IPHONEOS_DEPLOYMENT_TARGET "5.0")
set_xcode_property (${NAME} TARGETED_DEVICE_FAMILY "1,2")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -stdlib=libstdc++")



