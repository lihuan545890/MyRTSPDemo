LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libjsoncpp

LOCAL_CPPFLAGS += -DJSON_USE_EXCEPTION=0

LOCAL_C_INCLUDES := $(MY_WEBRTC_ROOT_PATH)/webrtc \
					$(LOCAL_PATH)/overrides/include \
					$(LOCAL_PATH)/source/include \
					$(LOCAL_PATH)/source/src/lib_json \
					
					
LOCAL_SRC_FILES := overrides/src/lib_json/json_reader.cpp \
				   overrides/src/lib_json/json_value.cpp \
				   source/src/lib_json/json_writer.cpp 
				   
include $(BUILD_STATIC_LIBRARY)				   