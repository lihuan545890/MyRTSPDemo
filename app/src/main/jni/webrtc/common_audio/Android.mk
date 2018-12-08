LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libcommon_audio

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc
LOCAL_CFLAGS += -DWEBRTC_POSIX

LOCAL_SRC_FILES := audio_converter.cc \
				   audio_util.cc \
				   blocker.cc \
				   fir_filter.cc \
				   resampler/push_resampler.cc \
				   resampler/push_sinc_resampler.cc \
				   resampler/resampler.cc \
				   resampler/sinc_resampler.cc \
				   ring_buffer.c \
				   signal_processing/auto_corr_to_refl_coef.c \
				   signal_processing/auto_correlation.c \
				   signal_processing/complex_fft.c \
				   signal_processing/complex_bit_reverse.c \
				   signal_processing/copy_set_operations.c \
				   signal_processing/cross_correlation.c \
				   signal_processing/division_operations.c \
				   signal_processing/dot_product_with_scale.c \
				   signal_processing/downsample_fast.c \
				   signal_processing/energy.c \
				   signal_processing/filter_ar.c \
				   signal_processing/filter_ar_fast_q12.c \
				   signal_processing/filter_ma_fast_q12.c \
				   signal_processing/get_hanning_window.c \
				   signal_processing/get_scaling_square.c \
				   signal_processing/ilbc_specific_functions.c \
				   signal_processing/levinson_durbin.c \
				   signal_processing/lpc_to_refl_coef.c \
				   signal_processing/min_max_operations.c \
				   signal_processing/randomization_functions.c \
				   signal_processing/refl_coef_to_lpc.c \
				   signal_processing/real_fft.c \
				   signal_processing/resample.c \
				   signal_processing/resample_48khz.c \
				   signal_processing/resample_by_2.c \
				   signal_processing/resample_by_2_internal.c \
				   signal_processing/resample_fractional.c \
				   signal_processing/spl_init.c \
				   signal_processing/spl_sqrt.c \
				   signal_processing/spl_sqrt_floor.c \
				   signal_processing/splitting_filter.c \
				   signal_processing/sqrt_of_one_minus_x_squared.c \
				   signal_processing/vector_scaling_operations.c \
				   vad/vad.cc \
				   vad/webrtc_vad.c \
				   vad/vad_core.c \
				   vad/vad_filterbank.c \
				   vad/vad_gmm.c \
				   vad/vad_sp.c \
				   wav_header.cc \
				   wav_file.cc \
				   window_generator.cc
				   
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := libcommon_audio_neon

LOCAL_CFLAGS += -mfloat-abi=softfp -mfpu=neon
LOCAL_CFLAGS +=  -DWEBRTC_ARCH_ARM_V7

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc

LOCAL_SRC_FILES := fir_filter_neon.cc \
				   resampler/sinc_resampler_neon.cc \
				   signal_processing/cross_correlation_neon.S \
				   signal_processing/downsample_fast_neon.S \
				   signal_processing/min_max_operations_neon.S
				   
include $(BUILD_STATIC_LIBRARY)				   