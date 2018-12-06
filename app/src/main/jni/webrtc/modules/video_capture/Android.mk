LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := libvideo_capture_module
LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc
LOCAL_CFLAGS += -DWEBRTC_LINUX
LOCAL_SRC_FILES := device_info_impl.cc \
				   video_capture_factory.cc \
				   video_capture_impl.cc

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := libvideo_capture_module_impl

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc

LOCAL_SRC_FILES := external/device_info_external.cc \
				   external/video_capture_external.cc 

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)


LOCAL_MODULE    := libvideo_capture_module_internal_impl

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(JNI_PATH)/webrtc/webrtc/third_party/jsoncpp/source/include \
					$(JNI_PATH)/webrtc/webrtc \
					$(JNI_PATH)/webrtc/webrtc/third_party/icu/source/common

LOCAL_SRC_FILES := android/device_info_android.cc \
				   android/video_capture_android.cc

include $(BUILD_STATIC_LIBRARY)