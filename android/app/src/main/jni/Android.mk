LOCAL_PATH := $(call my-dir)


$(info TARGET_ARCH_ABI is $(TARGET_ARCH_ABI))

$(info LOCAL_PATH is $(LOCAL_PATH))

PREBUILT_LIBS := ./libs/prebuilt/android-$(TARGET_ARCH_ABI)

include $(CLEAR_VARS)
LOCAL_MODULE := eegeo-sdk-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libeegeo-sdk.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := png-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libpng.a
LOCAL_EXPORT_C_INCLUDES := ./libs/png
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := curl-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libcurl.a
LOCAL_EXPORT_C_INCLUDES := ./libs/curl/android-$(TARGET_ARCH_ABI) 
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := uv-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libuv.a
LOCAL_EXPORT_C_INCLUDES := ./libs/uv/android-$(TARGET_ARCH_ABI) 
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := ssl-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := crypto-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := http-parser-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libhttp-parser.a
LOCAL_EXPORT_C_INCLUDES := ./libs/http-parser 
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := jpeg-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libjpeg.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := turbojpeg-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libturbojpeg.a
LOCAL_EXPORT_C_INCLUDES := ./libs/jpeg-turbo 
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := eegeo-sdk-samples
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 -lz -lm
LOCAL_LDLIBS += -fuse-ld=bfd
LOCAL_STATIC_LIBRARIES := eegeo-sdk-lib png-lib curl-lib uv-lib ssl-lib crypto-lib http-parser-lib jpeg-lib turbojpeg-lib

ifdef COMPILE_CPP_03
  $(info Configured for C++0x)
  LOCAL_CPPFLAGS += -std=c++0x
else
  $(info Configured for C++11)
  LOCAL_CPPFLAGS += -DCOMPILE_CPP_11=1 -std=c++11
endif

os_name:=$(shell uname -s)

ifeq ($(os_name),Darwin)
	android_specific_cpp_files := $(shell cd jni; find ./ -type f  -iname "*.cpp")
	LOCAL_SRC_FILES := $(android_specific_cpp_files:$(LOCAL_PATH)/%=%)

	shared_example_cpp_files := $(shell cd jni; find ./../../src/ -type f  -iname "*.cpp")
	LOCAL_SRC_FILES += $(shared_example_cpp_files:$(LOCAL_PATH)/%=%)

	platformincludes := $(shell find ./libs/platform -type d ! -path "*/OSX/*" ! -path "*/iOS/*")
	LOCAL_C_INCLUDES := $(platformincludes:$(LOCAL_PATH)/%=%)

	exampleincludes := $(shell find ./libs/../../src -type d)
	LOCAL_C_INCLUDES += $(exampleincludes:$(LOCAL_PATH)/%=%)
	
	java_exampleincludes := $(shell find ./jni/Examples -type d)
	LOCAL_C_INCLUDES += $(java_exampleincludes:$(LOCAL_PATH)/%=%)
else
	# assume windows if not specified for now (due to no uname)
	
	android_specific_cpp_files := $(shell cd jni && dir /a-d /b /s *.cpp)
	LOCAL_SRC_FILES := $(android_specific_cpp_files:$(LOCAL_PATH)/%=%)
    
    shared_example_cpp_files := $(shell cd jni\..\..\src\ && dir /a-d /b /s *.cpp)
	LOCAL_SRC_FILES += $(shared_example_cpp_files:$(LOCAL_PATH)/%=%)
	
	platformincludes := $(shell dir .\libs\platform /ad-h /s /b)
	LOCAL_C_INCLUDES := $(platformincludes:$(LOCAL_PATH)/%=%)
	LOCAL_C_INCLUDES += ./libs/platform 

	exampleincludes := $(shell dir .\libs\..\..\src /ad-h /s /b)
	LOCAL_C_INCLUDES += $(exampleincludes:$(LOCAL_PATH)/%=%)
	LOCAL_C_INCLUDES += .\libs\..\..\src
	
	java_exampleincludes := $(shell dir .\jni\Examples /ad-h /s /b)
	LOCAL_C_INCLUDES += $(java_exampleincludes:$(LOCAL_PATH)/%=%)
	LOCAL_C_INCLUDES += .\jni\Examples
endif 

LOCAL_C_INCLUDES += ./libs/rapidjson

$(info LOCAL_C_INCLUDES is $(LOCAL_C_INCLUDES))

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
