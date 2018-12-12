#ifndef VIDCAPTURE_H
#define VIDCAPTURE_H

#include <pthread.h>
#include <set>
#include <string>
#include "webrtc/modules/video_capture/include/video_capture.h"
#include "webrtc/system_wrappers/interface/scoped_refptr.h"
#include "webrtc/modules/video_capture/include/video_capture_factory.h"
#include "webrtc/modules/video_capture/include/video_capture_defines.h"
#include "webrtc/video_frame.h"
#include "RtspServerInstance.h"

using namespace webrtc;
class CVidCapture : public VideoCaptureDataCallback, public VideoCaptureFeedBack
{
public:
    CVidCapture();

    static bool IsValid(CVidCapture * p);
   	void AttachPreviewHolder(void *prevHolder);
    
    int32_t StartCapture(VideoCaptureCapability& capability, int nOrient);
    void StopCapture();  
    void SetPreviewRotation(int nRotation);
    void GetCapability(VideoCaptureCapability& capability);
    void SetOrientation(int nOrient);
    inline int32_t GetOrientation() { return m_nOutOrient; }


    // implements VideoCaptureDataCallback
    virtual void OnIncomingCapturedFrame(const int32_t id,
            I420VideoFrame& videoFrame);

    virtual void OnCaptureDelayChanged(const int32_t id, const int32_t delay);
    // implements VideoCaptureFeedBack
    virtual void OnCaptureFrameRate(const int32_t id,
                                    const uint32_t frameRate);
    virtual void OnNoPictureAlarm(const int32_t id,
                                  const VideoCaptureAlarm alarm);
    virtual ~CVidCapture();

    bool StartPushStream();

    bool StopPushStream();

 protected:
     scoped_refptr<VideoCaptureModule>
       OpenVideoCaptureDevice(uint32_t device);
    unsigned int m_nNumberOfDevices;  
    int32_t m_nOutOrient;
    int32_t m_nCamera;
    VideoCaptureCapability  m_capability;   //!< current working capability
    std::string             m_strCaptureId; //!< current camera id    
    scoped_ptr<VideoCaptureModule::DeviceInfo>  m_spDeviceInfo;
    scoped_refptr<VideoCaptureModule>           m_spVcm;
    VideoCaptureRotation    m_initialOrient;
    uint32_t m_bIsFrontCamera;
    void* m_jPreviewHolder;
    int32_t m_nWidth;
    int32_t m_nHeight;
    int32_t m_nFps;
    RTSPServerInstance *m_RtspServer;
    u_int8_t *m_pBuf;
};

#endif
