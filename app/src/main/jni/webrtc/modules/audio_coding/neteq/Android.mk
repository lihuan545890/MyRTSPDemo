LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libneteq

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(JNI_PATH)/webrtc/webrtc/third_party/opus/src/celt \
					$(JNI_PATH)/webrtc/webrtc/third_party/opus/src/include \
					$(JNI_PATH)/webrtc/webrtc/third_party/opus/src/src

LOCAL_SRC_FILES := accelerate.cc \
				   audio_classifier.cc \
				   audio_decoder_impl.cc \
				   audio_multi_vector.cc \
				   audio_vector.cc \
				   background_noise.cc \
				   buffer_level_filter.cc \
				   comfort_noise.cc \
				   decision_logic.cc \
				   decision_logic_fax.cc \
				   decision_logic_normal.cc \
				   decoder_database.cc \
				   delay_manager.cc \
				   delay_peak_detector.cc \
				   dsp_helper.cc \
				   dtmf_buffer.cc \
				   dtmf_tone_generator.cc \
				   expand.cc \
				   merge.cc \
				   neteq_impl.cc \
				   neteq.cc \
				   statistics_calculator.cc \
				   normal.cc \
				   packet_buffer.cc \
				   payload_splitter.cc \
				   post_decode_vad.cc \
				   preemptive_expand.cc \
				   random_vector.cc \
				   rtcp.cc \
				   sync_buffer.cc \
				   timestamp_scaler.cc \
				   time_stretch.cc

include $(BUILD_STATIC_LIBRARY)