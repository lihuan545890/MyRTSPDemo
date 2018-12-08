LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libg722

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
                    $(LOCAL_PATH)/include \

LOCAL_SRC_FILES := audio_encoder_g722.cc \
				   g722_interface.c \
				   g722_encode.c \
				   g722_decode.c
				   

include $(BUILD_STATIC_LIBRARY)

