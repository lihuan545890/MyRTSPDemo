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
include $(MY_WEBRTC_ROOT_PATH)/webrtc/common_video/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/webrtc/modules/video_capture/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/webrtc/modules/utility/source/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/webrtc/third_party/libyuv/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/webrtc/third_party/jsoncpp/Android.mk
include $(MY_WEBRTC_ROOT_PATH)/webrtc/third_party/icu/Android.mk
include $(CLEAR_VARS)


LOCAL_C_INCLUDES := $(MY_WEBRTC_ROOT_PATH)\
                    $(MY_WEBRTC_ROOT_PATH)/ffmpeg/include \
                    $(MY_WEBRTC_ROOT_PATH)/common/include \
                    $(MY_WEBRTC_ROOT_PATH)/video/include \
                    $(MY_WEBRTC_ROOT_PATH)/rtsp/include \
                    $(MY_WEBRTC_ROOT_PATH)/live/liveMedia/include \
                    $(MY_WEBRTC_ROOT_PATH)/live/BasicUsageEnvironment/include \

LOCAL_SRC_FILES := $(MY_WEBRTC_ROOT_PATH)/common/src/on_load.cpp \
                   $(MY_WEBRTC_ROOT_PATH)/common/src/framequeue.cpp \
                   $(MY_WEBRTC_ROOT_PATH)/video/src/vidcapture.cpp \
                   $(MY_WEBRTC_ROOT_PATH)/video/src/jnividcapture.cpp \
                   $(MY_WEBRTC_ROOT_PATH)/rtsp/src/H264LiveFramedSource.cpp \
                   $(MY_WEBRTC_ROOT_PATH)/rtsp/src/H264LiveCaptureThread.cpp \
                   $(MY_WEBRTC_ROOT_PATH)/rtsp/src/H264LiveServerMediaSubsession.cpp \
                   $(MY_WEBRTC_ROOT_PATH)/rtsp/src/RtspServerInstance.cpp


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
			libsystem_wrappers \
			libwebrtc_utility \
			libyuv \
			libjsoncpp \
			libi18n \
			libicudata \
			libicuuc \
			libcommon_video \
			libvideo_capture

LOCAL_LDLIBS += -llog -lGLESv2 -lOpenSLES -lz -Wdeprecated-declarations
LOCAL_MODULE := librtspdemo-jni
include $(BUILD_SHARED_LIBRARY)
