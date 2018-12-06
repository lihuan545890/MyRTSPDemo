LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libsystem_wrappers

LOCAL_C_INCLUDES := $(MY_WEBRTC_ROOT_PATH)

LOCAL_CFLAGS += -DWEBRTC_LINUX
LOCAL_CFLAGS += -DWEBRTC_ANDROID
LOCAL_CFLAGS += -DWEBRTC_POSIX

LOCAL_SRC_FILES := source/aligned_malloc.cc \
				   source/atomic32_posix.cc \
				   source/clock.cc \
				   source/condition_variable.cc \
				   source/condition_variable_posix.cpp \
				   source/cpu_info.cc \
				   source/cpu_features.cc \
				   source/critical_section.cc \
				   source/critical_section_posix.cc \
				   source/data_log.cc \
				   source/data_log_c.cc \
				   source/event.cc \
				   source/event_posix.cc \
				   source/event_tracer.cc \
				   source/file_impl.cc \
				   source/field_trial_default.cc \
				   source/logcat_trace_context.cc \
				   source/logging.cc \
				   source/metrics_default.cc \
				   source/rtp_to_ntp.cc \
				   source/rw_lock.cc \
				   source/rw_lock_generic.cpp \
				   source/rw_lock_posix.cc \
				   source/sleep.cc \
				   source/sort.cc \
				   source/tick_util.cc \
				   source/thread.cc \
				   source/thread_posix.cc \
				   source/timestamp_extrapolator.cc \
				   source/trace_impl.cc \
				   source/trace_posix.cc


LOCAL_STATIC_LIBRARIES := cpufeatures

include $(BUILD_STATIC_LIBRARY)
$(call import-module, android/cpufeatures)