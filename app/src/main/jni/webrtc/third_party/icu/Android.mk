LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libi18n

LOCAL_CPPFLAGS += -frtti -DU_I18N_IMPLEMENTATION

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc/webrtc \
					$(LOCAL_PATH)/source/common \
					$(LOCAL_PATH)/source/i18n

FILE_LIST := $(wildcard $(LOCAL_PATH)/source/i18n/*.cpp)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)


LOCAL_MODULE    := libicudata

#LOCAL_CPPFLAGS += -frtti -DU_I18N_IMPLEMENTATION

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc/webrtc \
					$(LOCAL_PATH)/source/common \
					$(LOCAL_PATH)/source/i18n

FILE_LIST := $(wildcard $(LOCAL_PATH)/source/stubdata/*.cpp)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := libicuuc

LOCAL_CPPFLAGS += -frtti -DU_COMMON_IMPLEMENTATION

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc/webrtc \
					$(LOCAL_PATH)/source/common \
					$(LOCAL_PATH)/source/i18n

FILE_LIST := $(wildcard $(LOCAL_PATH)/source/common/*.cpp)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

include $(BUILD_STATIC_LIBRARY)