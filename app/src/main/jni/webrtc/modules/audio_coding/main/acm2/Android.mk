LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -DWEBRTC_CODEC_OPUS

LOCAL_MODULE    := libaudio_coding_module

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc
					
LOCAL_SRC_FILES := acm_amr.cc \
				   acm_amrwb.cc \
				   acm_cng.cc \
				   acm_codec_database.cc \
				   acm_dtmf_playout.cc \
				   acm_g722.cc \
				   acm_g7221.cc \
				   acm_g7221c.cc \
				   acm_g729.cc \
				   acm_g7291.cc \
				   acm_generic_codec.cc \
				   acm_gsmfr.cc \
				   acm_ilbc.cc \
				   acm_isac.cc \
				   acm_opus.cc \
				   acm_speex.cc \
				   acm_pcm16b.cc \
				   acm_pcma.cc \
				   acm_pcmu.cc \
				   acm_red.cc \
				   acm_receiver.cc \
				   acm_resampler.cc \
				   audio_coding_module.cc \
				   audio_coding_module_impl.cc \
				   call_statistics.cc \
				   initial_delay_manager.cc \
				   nack.cc
				   

include $(BUILD_STATIC_LIBRARY)	