#include "jnividcapture.h"
#include "webrtc/modules/video_capture/android/video_capture_android.h"
#include "webrtc/modules/video_capture/video_capture_internal.h"
#include "vid_global_data.h"
#include "vidcapture.h"


uint32_t	    m_bIsInited       =  0;
JavaVM*         m_jvm             =  NULL;
jobject         m_jPreviewHolder  =  NULL;

using namespace webrtc;

bool InitVideoCapture(JavaVM* javaVM, jobject context)
{

    if (m_bIsInited)
    {
        LOGI("try re-init video capture");
        return false;
    }
    int32_t nErr = webrtc::SetCaptureAndroidVM(javaVM, context);
    if (nErr != 0)
    {
        LOGE("init video capture failed.");
        return false;
    }

	CVidCapture * pCapture = new CVidCapture();
	CVidGlobalData * pVidShared = CVidGlobalData::Instance();
 	pVidShared->m_pVidCapture = pCapture;
	
    m_bIsInited = 1;
    m_jvm = static_cast<JavaVM*>(javaVM);
	return true;
}

void DestroyVideoCapture()
{

    CVidGlobalData * pVidShared = CVidGlobalData::Instance();
    CVidCapture * pVidCapture = NULL;

    //BEGIN_AUTOLOCK(&pVidShared->m_DecPlylock);
    pVidCapture = (CVidCapture*)pVidShared->m_pVidCapture;
    pVidShared->m_pVidCapture = NULL;
	m_bIsInited = false;


    if (pVidCapture != NULL)
    {
        delete pVidCapture;
        LOGI("VidCapture instance freed: %u", sizeof(CVidCapture));
    }

    // destroy global references
    JNIEnv* env = NULL;
    if (m_jvm == NULL || m_jPreviewHolder == NULL)
    {
        return;
    }
    if (m_jvm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
    {
        return;
    }
    env->DeleteGlobalRef(m_jPreviewHolder);
    m_jPreviewHolder = NULL;	
}

bool StartVideoCapture(void *jPrevHolder, int nWidth, int nHeight, int nMaxFPS, int nOrient)
{
    if (!m_bIsInited)
    {
        LOGE("video capture device is not initialized.");
        return false;
    }

    JNIEnv* env = NULL;
    if (m_jvm == NULL)
    {
        return false;
    }	

    if (m_jvm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
    {
        return false;
    }
    if (m_jPreviewHolder != NULL)
    {
        env->DeleteGlobalRef(m_jPreviewHolder);
        m_jPreviewHolder = NULL;
    }
    m_jPreviewHolder = env->NewGlobalRef(static_cast<jobject>(jPrevHolder));	
	CVidGlobalData * pVidShared = CVidGlobalData::Instance();
	CVidCapture * pCapture = (CVidCapture*)pVidShared->m_pVidCapture;

	
    VideoCaptureCapability capability;
    capability.maxFPS = nMaxFPS;
    capability.width = nWidth;
    capability.height = nHeight;
    capability.rawType = kVideoI420;
    capability.interlaced = 0;

	pCapture->AttachPreviewHolder(m_jPreviewHolder);
	if (!pCapture->StartCapture(capability, nOrient))
	{
		return false;
	}
	
}

void StopVideoCapture()
{
	m_bIsInited = false;
}

bool StartPushStream()
{
    if (!m_bIsInited)
    {
        LOGE("video capture device is not initialized.");
        return false;
    }

    JNIEnv* env = NULL;
    if (m_jvm == NULL)
    {
        return false;
    }	

    if (m_jvm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
    {
        return false;
    }	

	CVidGlobalData * pVidShared = CVidGlobalData::Instance();
	CVidCapture * pCapture = (CVidCapture*)pVidShared->m_pVidCapture;	

	pCapture->StartPushStream();
}

void SetOrientation(int nOrient)
{

}

int GetOrientation()
{

}

void SetPreviewRotation(int nRotation)
{

}

bool SwitchCamera()
{

}

int GetCameraId()
{

}

int GetCameraCount()
{

}

int GetCameraDefaultOrientation()
{

}

void * GetCameraParameters()
{

}

void SetCameraParameters(void * params)
{

}

jboolean jni_InitVideoCapture(JNIEnv * env, jclass,
        jobject jContext)
{
    JavaVM* jvm;
    env->GetJavaVM(&jvm);
   return  InitVideoCapture(jvm, jContext);
}


jboolean jni_StartVideoCapture(JNIEnv * env, jclass,
        jobject jPrevHolder, jint nWidth, jint nHeight,
        jint nMaxFPS, jint nOrient)
{
    if(jPrevHolder != NULL)
    {
        // when use auto rotation corrector, the nOrient is duplicated and wrong.
        if (StartVideoCapture(jPrevHolder, nWidth, nHeight, nMaxFPS, 0 /*nOrient*/))
        {
            return JNI_TRUE;
        }
    }
    return JNI_FALSE;
}

void jni_StopVideoCapture(JNIEnv * env, jclass)
{
    StopVideoCapture();
}


void jni_SetOrientation(JNIEnv * env, jclass,
        jint jorient)
{
    LOGI("orient: %d", jorient);
    SetOrientation(jorient);
}

void jni_SetPreviewRotation(JNIEnv * env, jclass,
        jint jrotation)
{
    LOGI("rotation: %d", jrotation);
    SetPreviewRotation(jrotation);
}

jboolean jni_SwitchCamera(JNIEnv * env, jclass)
{
    jboolean jre = JNI_FALSE;
    jre = SwitchCamera()?JNI_TRUE:JNI_FALSE;
    return jre;
}

jint jni_GetCameraId(JNIEnv * env, jclass)
{
    return GetCameraId();
}

jint jni_GetCameraCount(JNIEnv * env, jclass)
{
    return GetCameraCount();
}


jobject jni_getParamters(JNIEnv * env, jclass)
{
    return static_cast<jobject>(GetCameraParameters());
}

void jni_setParameters(JNIEnv * env, jclass, jobject camParams)
{
    SetCameraParameters(camParams);
}

void jni_setScreenSize(JNIEnv * env, jclass,
        jint jwidth, jint jheight)
{
    LOGI("screen-size: %dx%d", jwidth, jheight);
//    SetScreenSize(jwidth, jheight);
}

void jni_startPushStream(JNIEnv * env, jclass)
{
	StartPushStream();
}

void jni_DestroyVideoCapture(JNIEnv * env, jclass)
{
    DestroyVideoCapture();
}

static JNINativeMethod gMethods[] =
{
    {"_initialize", "(Landroid/content/Context;)Z", (void*) jni_InitVideoCapture},
    {"_destroy", "()V", (void*) jni_DestroyVideoCapture},
    {"_start", "(Landroid/view/SurfaceHolder;IIII)Z", (void*) jni_StartVideoCapture},
    {"_stop", "()V", (void*) jni_StopVideoCapture},
    {"_switchCamera", "()Z", (void*) jni_SwitchCamera},
    {"setOrientation", "(I)V", (void*) jni_SetOrientation},
    {"setPreviewRotation", "(I)V", (void*) jni_SetPreviewRotation},
    {"getCameraId", "()I", (void*) jni_GetCameraId},
    {"getCameraCount", "()I", (void*) jni_GetCameraCount},
    {"getParameters", "()Landroid/hardware/Camera$Parameters;", (void*) jni_getParamters},
    {"setParameters", "(Landroid/hardware/Camera$Parameters;)V", (void*) jni_setParameters},
    {"_setScreenSize", "(II)V", (void*) jni_setScreenSize},
    {"_startPushStream", "()V", (void*) jni_startPushStream},
};

#ifndef NELEM
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

int jniRegisterNativeMethods(JNIEnv* env, const char* className, const JNINativeMethod* gMethods, int numMethods)
{

    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {                                                                                    
        char* msg;
        asprintf(&msg, "Native registration unable to find class '%s', aborting", className);
        env->FatalError(msg);
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        char* msg;
        asprintf(&msg, "RegisterNatives failed for '%s', aborting", className);
        env->FatalError(msg);
    }
    env->DeleteLocalRef(clazz);

    return 0;
}

int LoadVideoCaptureJNI(JNIEnv* env)
{
    const char * const class_path_name = "org/lh/myrtspdemo/VideoCapture";
    int ret = 0;
    ret = jniRegisterNativeMethods(env, class_path_name, gMethods, NELEM(gMethods));
	
    if (ret)
    {
        return ret;
    }

    return ret;
}
