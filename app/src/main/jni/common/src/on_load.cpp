#include <android/log.h>
#include <jni.h>

#include <map>
#include <string>
#include <stdlib.h>
#include "jnividcapture.h"

extern "C"{
	#include "libavcodec/jni.h"	
	#include "libavutil/opt.h"
}

static JavaVM* g_vm = NULL;

inline static int convert_to_android_log(int av_level)
{
    int level = ANDROID_LOG_VERBOSE;
    if      (av_level <= AV_LOG_PANIC)      level = ANDROID_LOG_FATAL;
    else if (av_level <= AV_LOG_FATAL)      level = ANDROID_LOG_FATAL;
    else if (av_level <= AV_LOG_ERROR)      level = ANDROID_LOG_ERROR;
    else if (av_level <= AV_LOG_WARNING)    level = ANDROID_LOG_WARN;
    else if (av_level <= AV_LOG_INFO)       level = ANDROID_LOG_INFO;
    // AV_LOG_VERBOSE means detailed info
    else if (av_level <= AV_LOG_VERBOSE)    level = ANDROID_LOG_INFO;
    else if (av_level <= AV_LOG_DEBUG)      level = ANDROID_LOG_DEBUG;
    else if (av_level <= AV_LOG_TRACE)      level = ANDROID_LOG_VERBOSE;
    else                                    level = ANDROID_LOG_VERBOSE;
    return level;
}

static void ff_log_callback_brief(void *ptr, int level, const char *fmt, va_list vl)
{
	if(level >48)
		return;

	int ffplv __unused = convert_to_android_log(level);
	 __android_log_vprint(ffplv, "ffmpeg-jni", fmt, vl); 
}

jint JNIEXPORT JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
  JNIEnv * env = NULL;
  jint result = -1;
  
  if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
     return result;
  }
  g_vm = vm;
  av_log_set_callback(ff_log_callback_brief);
  av_jni_set_java_vm(vm, NULL);
  LoadVideoCaptureJNI(env);
  return JNI_VERSION_1_4;
}


