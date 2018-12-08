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


LOCAL_MODULE    := libvideo_capture

LOCAL_C_INCLUDES := $(MY_WEBRTC_ROOT_PATH) \
					$(MY_WEBRTC_ROOT_PATH)/webrtc/third_party/jsoncpp/source/include \
					$(MY_WEBRTC_ROOT_PATH)/webrtc \
					$(MY_WEBRTC_ROOT_PATH)/webrtc/third_party/icu/source/common
										
LOCAL_CFLAGS += -DWEBRTC_LINUX
LOCAL_SRC_FILES := video_capture_impl.cc \
				   video_capture_factory.cc \
				   device_info_impl.cc \
				   android/device_info_android.cc \
				   android/video_capture_android.cc

include $(BUILD_STATIC_LIBRARY)