cmake_minimum_required (VERSION 3.0)

PROJECT (platform-sdk)
SET (OUTPUT_NAME platform-sdk)


# --------------------- Add Sources ----------------------- #

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


# ------------------- Add Includes ------------------------ #

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


# --------------- Add Library Dependencies ---------------- #

SET(CMAKE_EXE_LINKER_FLAGS
    "-framework CoreLocation -framework MobileCoreServices -framework SystemConfiguration -framework CFNetwork -framework GLKit -framework OpenGLES -framework UIKit -framework Foundation -framework CoreGraphics -framework CoreData -LInclude/ -lapps-on-maps -LInclude/ -lapps-on-maps-sim -LInclude/ -lturbojpeg -L/usr/lib/ -lz"
)


# -------------------- Add Resources ---------------------- #

set (Resources "")
FILE (GLOB Resources ${Resources} "Resources/Icons/*.png")
FILE (GLOB Resources ${Resources} "Resources/*.png" "Resources/*.pvr" "Resources/*.fnt" )
set (Resources ${Resources} "Resources/load_model_example")
set (Resources ${Resources} "Resources/pin_over_model_example")
set (Resources ${Resources} "Resources/pins_example")
set (Resources ${Resources} "Resources/pod_animation_example")
set (Resources ${Resources} "Resources/route_simulation_example")
set (Resources ${Resources} "Resources/route_simulation_animation_example")


# ------------------- Configure XCode --------------------- #

SET(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
SET(CMAKE_OSX_ARCHITECTURES "armv7;i386")
SET(CMAKE_CXX_FLAGS "-x objective-c++")


SET(APP_TYPE MACOSX_BUNDLE)

add_executable(
	${OUTPUT_NAME}
    ${APP_TYPE}
   	${SourceFiles}
    ${HeaderFiles}
    ${Resources}
)

# set plist template and properties

set_target_properties(
    ${OUTPUT_NAME} 
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
set_xcode_property (${OUTPUT_NAME} CODE_SIGN_IDENTITY "iPhone Developer")
set_xcode_property (${OUTPUT_NAME} CLANG_CXX_LANGUAGE_STANDARD "c++98")
set_xcode_property (${OUTPUT_NAME} CLANG_CXX_LIBRARY "libstdc++")
set_xcode_property (${OUTPUT_NAME} IPHONEOS_DEPLOYMENT_TARGET "5.0")
set_xcode_property (${OUTPUT_NAME} TARGETED_DEVICE_FAMILY "1,2")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -stdlib=libstdc++")

FUNCTION(groupify_files input_files_to_groupify)
    FOREACH(source_file_name ${input_files_to_groupify})
        MESSAGE(STATUS "Processing file: ${source_file_name}")

        GET_FILENAME_COMPONENT(directory_path ${source_file_name} DIRECTORY)
        MESSAGE(STATUS "Directory path: ${directory_path}")

        STRING(REGEX REPLACE "^/Users/kimbleoperations/Desktop/droid/mobile-sdk-harness/ios/" "" stripped_path ${directory_path})
        STRING(REGEX REPLACE "^../" "" stripped_path ${stripped_path})
        MESSAGE(STATUS "Stripped path: ${stripped_path}")

        STRING(REGEX REPLACE "/" "\\\\" stripped_path ${stripped_path})
        MESSAGE(STATUS "CMake source_groupified: ${stripped_path}")

        source_group("${stripped_path}" FILES ${source_file_name})
    ENDFOREACH(source_file_name)
ENDFUNCTION(groupify_files)

groupify_files("${SRC}")
groupify_files("${HDR}")
groupify_files("${Resources}")


