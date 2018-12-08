LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libwebrtc_opus

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(JNI_PATH)/webrtc/webrtc/third_party/opus/src/include
					
					
LOCAL_SRC_FILES := audio_encoder_opus.cc \
				   opus_interface.c
				   

include $(BUILD_STATIC_LIBRARY)

