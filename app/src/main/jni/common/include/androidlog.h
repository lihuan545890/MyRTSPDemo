#ifndef ANDROID_LOG_H
#define ANDROID_LOG_H

#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "webrtc_jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif