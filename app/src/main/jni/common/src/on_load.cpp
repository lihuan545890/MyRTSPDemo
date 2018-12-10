#include <android/log.h>
#include <jni.h>

#include <map>
#include <string>
#include <stdlib.h>
#include "jnividcapture.h"

static JavaVM* g_vm = NULL;


jint JNIEXPORT JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
  JNIEnv * env = NULL;
  jint result = -1;
  
  if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
     return result;
  }
  g_vm = vm;
//  av_log_set_callback(ff_log_callback_brief);
//  av_jni_set_java_vm(vm, NULL);
  LoadVideoCaptureJNI(env);
  return JNI_VERSION_1_4;
}


