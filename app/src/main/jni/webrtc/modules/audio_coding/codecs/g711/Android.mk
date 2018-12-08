LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libg711

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
				    $(LOCAL_PATH)/include \

LOCAL_SRC_FILES := g711_interface.c \
				   g711.c \
				   audio_encoder_pcm.cc 
				   

include $(BUILD_STATIC_LIBRARY)

