LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libcommon_video

LOCAL_C_INCLUDES := $(MY_WEBRTC_ROOT_PATH) \
					$(MY_WEBRTC_ROOT_PATH)/webrtc/third_party/libyuv/include

LOCAL_SRC_FILES := i420_video_frame.cc \
				   libyuv/webrtc_libyuv.cc \
				   libyuv/scaler.cc \
				   plane.cc \
				   texture_video_frame.cc

include $(BUILD_STATIC_LIBRARY)