LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libcng

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(LOCAL_PATH)/include \
					$(JNI_PATH)/webrtc/webrtc/common_audio/signal_processing/include 

LOCAL_SRC_FILES := audio_encoder_cng.cc \
				   webrtc_cng.c \
				   cng_helpfuns.c \
				   

include $(BUILD_STATIC_LIBRARY)

