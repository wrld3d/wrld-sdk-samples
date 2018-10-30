cmake_minimum_required(VERSION 3.12)

set(CMAKE_TOOLCHAIN_FILE "../cmake/toolchain/ios/iOS.cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/templates/ios)

if(NOT ${IOS}) 
	message(FATAL_ERROR "Incorrect toolchain set: ${CMAKE_TOOLCHAIN_FILE}")
endif(NOT ${IOS})

project(SDKSamplesApp)
set(executable_name SDKSamplesApp)




if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Include/eegeo/CMakeLists.txt")
  include("${CMAKE_CURRENT_SOURCE_DIR}/Include/eegeo/CMakeLists.txt")
else(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Include/eegeo/CMakeLists.txt")
  message(FATAL_ERROR "Couldn't detect platform headers. Have you ran update.platform.sh?")
endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Include/eegeo/CMakeLists.txt")

include(../src/CMakeLists.txt)
include(ios_src/CMakeLists.txt)
include(Resources/CMakeLists.txt)

set(storyboards
    ExampleApp/en.lproj/MainStoryboard_iPad.storyboard
    ExampleApp/en.lproj/MainStoryboard_iPhone.storyboard)

# plist settings
set(EEGEO_PLIST_BUNDLE_EXECUTABLE "\${EXECUTABLE_NAME}")
set(EEGEO_PLIST_BUNDLE_IDENTIFIER "eegeo.\${PRODUCT_NAME:rfc1034identifier}")
set(EEGEO_PLIST_BUNDLE_SHORT_VERSION_STRING "\${PRODUCT_VERSION}")
set(EEGEO_PLIST_BUNDLE_DISPLAY_NAME "SDK Samples")
set(EEGEO_PLIST_BUNDLE_NAME "\${PRODUCT_NAME}")


# compiler/linker settings
set(IOS_WARNING_FLAGS "-Wmost -Wno-four-char-constants -Wno-unknown-pragmas -Wno-reorder")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++ ${IOS_WARNING_FLAGS}")

set(ios_frameworks   
  CoreLocation
  MobileCoreServices 
  SystemConfiguration 
  CFNetwork 
  GLKit 
  OpenGLES 
  UIKit
  Foundation
  CoreGraphics 
  CoreData
  Security
  )

set(static_libs 
  apps-on-maps-cpp11 
  apps-on-maps-cpp11-sim 
  turbojpeg 
  z 
  curl 
  uv
  )

include_directories(${headers})

add_executable(${executable_name} MACOSX_BUNDLE ${sources} ${resources} ${storyboards})

set(
allresources
${resources}
${storyboards}
)

set_target_properties(
${executable_name} 
PROPERTIES 
RESOURCE "${allresources}"
)


foreach (FRAMEWORK_NAME ${ios_frameworks})
  list(APPEND linked_ios_frameworks "-framework ${FRAMEWORK_NAME}")
endforeach (FRAMEWORK_NAME)

foreach (LIB_NAME ${static_libs})
  list(APPEND linked_static_libs "-l${LIB_NAME}")
endforeach (LIB_NAME)


target_link_libraries(${executable_name} ${linked_static_libs})
target_link_libraries(${executable_name} ${linked_ios_frameworks})



set_xcode_property(${executable_name} LIBRARY_SEARCH_PATHS "Include/eegeo")

# project settings
set_xcode_property (${executable_name} DEBUG_INFORMATION_FORMAT[variant=Debug] "dwarf")
set_xcode_property (${executable_name} DEBUG_INFORMATION_FORMAT[variant=MinSizeRel] "dwarf-with-dsym")
set_xcode_property (${executable_name} DEBUG_INFORMATION_FORMAT[variant=RelWithDebInfo] "dwarf-with-dsym")
set_xcode_property (${executable_name} DEBUG_INFORMATION_FORMAT[variant=Release] "dwarf-with-dsym")

add_custom_command(
  TARGET ${executable_name}
  COMMENT "Touching Info.plist to ensure properties set from xcodebuild params appear correctly in app bundle in incremental builds."
  PRE_BUILD COMMAND touch "\${INFOPLIST_FILE}"
)

set_xcode_property (${executable_name} GCC_TREAT_WARNINGS_AS_ERRORS "YES")
set_xcode_property (${executable_name} CODE_SIGN_IDENTITY "iPhone Developer")
set_xcode_property (${executable_name} DEVELOPMENT_TEAM "QBCVJ28BRW")
set_xcode_property (${executable_name} IPHONEOS_DEPLOYMENT_TARGET "8.0")
set_xcode_property (${executable_name} TARGETED_DEVICE_FAMILY "1,2")
set_xcode_property (${executable_name} ENABLE_BITCODE "No")

set_xcode_property (${executable_name} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
set_xcode_property (${executable_name} ASSETCATALOG_COMPILER_LAUNCHIMAGE_NAME "LaunchImage")
set_xcode_property (${executable_name} COMBINE_HIDPI_IMAGES "No")

set_xcode_property(${executable_name} GCC_PRECOMPILE_PREFIX_HEADER "YES")
set_xcode_property(${executable_name} GCC_PREFIX_HEADER "ExampleApp/SDKSamplesApp-Prefix.pch")

set_xcode_property(${executable_name} CLANG_CXX_LANGUAGE_STANDARD "c++11")
set_xcode_property(${executable_name} CLANG_CXX_LIBRARY "libc++")

set_xcode_property(${executable_name} ONLY_ACTIVE_ARCH "YES")





