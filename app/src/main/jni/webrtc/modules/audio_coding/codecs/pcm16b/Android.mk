LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libpcm16b

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(LOCAL_PATH)/include
					

LOCAL_SRC_FILES := audio_encoder_pcm16b.cc \
				   pcm16b.c
				   

include $(BUILD_STATIC_LIBRARY)

