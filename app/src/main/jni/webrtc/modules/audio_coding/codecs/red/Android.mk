LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libred

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					
					

LOCAL_SRC_FILES := audio_encoder_copy_red.cc 
				   

include $(BUILD_STATIC_LIBRARY)

