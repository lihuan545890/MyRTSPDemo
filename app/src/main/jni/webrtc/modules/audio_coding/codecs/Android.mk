LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libaudio_decoder_interface

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc

LOCAL_SRC_FILES := audio_decoder.cc 

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := libaudio_encoder_interface

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc

LOCAL_SRC_FILES := audio_encoder.cc 

include $(BUILD_STATIC_LIBRARY)