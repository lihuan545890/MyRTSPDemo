LOCAL_PATH := $(call my-dir)
MY_WEBRTC_ROOT_PATH := $(LOCAL_PATH)

include $(CLEAR_VARS)
LOCAL_MODULE    := libavcodec
LOCAL_SRC_FILES := ffmpeg/lib/libavcodec.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libavfilter
LOCAL_SRC_FILES := ffmpeg/lib/libavfilter.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libavformat
LOCAL_SRC_FILES := ffmpeg/lib/libavformat.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libavutil
LOCAL_SRC_FILES := ffmpeg/lib/libavutil.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libswresample
LOCAL_SRC_FILES := ffmpeg/lib/libswresample.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libswscale
LOCAL_SRC_FILES := ffmpeg/lib/libswscale.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := libx264
LOCAL_SRC_FILES := ffmpeg/lib/libx264.a
include $(PREBUILT_STATIC_LIBRARY)

include $(LOCAL_PATH)/live/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/webrtc/system_wrappers/Android.mk
include $(CLEAR_VARS)


LOCAL_WHOLE_STATIC_LIBRARIES := \
			libUsageEnvironment \
			libBasicUsageEnvironment \
			libgroupsock \
			libliveMedia \
			libx264 \
			libavformat \
			libavcodec \
			libavutil \
			libavfilter \
			libswresample \
			libswscale \
			libsystem_wrappers			
			
LOCAL_LDLIBS += -llog -lGLESv2 -lOpenSLES -lz	
LOCAL_MODULE := librtspdemo-jni
include $(BUILD_SHARED_LIBRARY)
