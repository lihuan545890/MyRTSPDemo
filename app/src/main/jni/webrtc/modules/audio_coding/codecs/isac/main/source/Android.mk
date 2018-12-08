LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libisac

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(LOCAL_PATH)/../interface \
					$(JNI_PATH)/webrtc/webrtc/common_audio/signal_processing/include 

LOCAL_SRC_FILES := arith_routines.c \
				   arith_routines_hist.c \
				   arith_routines_logist.c \
				   audio_encoder_isac.cc \
				   bandwidth_estimator.c \
				   crc.c \
				   decode.c \
				   decode_bwe.c \
				   encode.c \
				   encode_lpc_swb.c \
				   entropy_coding.c \
				   fft.c \
				   filter_functions.c \
				   filterbank_tables.c \
				   intialize.c \
				   isac.c \
				   filterbanks.c \
				   pitch_lag_tables.c \
				   lattice.c \
				   lpc_gain_swb_tables.c \
				   lpc_analysis.c \
				   lpc_shape_swb12_tables.c \
				   lpc_shape_swb16_tables.c \
				   lpc_tables.c \
				   pitch_estimator.c \
				   pitch_filter.c \
				   pitch_gain_tables.c \
				   spectrum_ar_model_tables.c \
				   transform.c \
				   
				   

include $(BUILD_STATIC_LIBRARY)

