LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libwebrtc_utility

LOCAL_C_INCLUDES := $(MY_WEBRTC_ROOT_PATH)

LOCAL_SRC_FILES := helpers_android.cc \
				   process_thread_impl.cc \
				   rtp_dump_impl.cc 
				   

include $(BUILD_STATIC_LIBRARY)