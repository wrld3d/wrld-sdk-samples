LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(info TARGET_ARCH_ABI is $(TARGET_ARCH_ABI))

PREBUILT_LIBS := ./libs/prebuilt/android-$(TARGET_ARCH_ABI)

LOCAL_MODULE := native-activity-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libnative-activity-lib.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := native-activity
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 -lz -lm -L${PREBUILT_LIBS} -lpng -lcurl -lssl -lcrypto -lhttp-parser -ljpeg -lturbojpeg
LOCAL_LDLIBS += -fuse-ld=bfd
LOCAL_STATIC_LIBRARIES := native-activity-lib 

ifdef COMPILE_CPP_11
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


$(info LOCAL_C_INCLUDES is $(LOCAL_C_INCLUDES))

LOCAL_C_INCLUDES += ./libs/curl/android-$(TARGET_ARCH_ABI) 
LOCAL_C_INCLUDES += ./libs/http-parser
LOCAL_C_INCLUDES += ./libs/httpxx
LOCAL_C_INCLUDES += ./libs/jpeg-turbo
LOCAL_C_INCLUDES += ./libs/png
LOCAL_C_INCLUDES += ./libs/rapidjson

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
