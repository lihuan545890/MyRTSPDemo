#include "vidcapture.h"
#include "androidlog.h"

#include "framequeue.h"
FrameQueue videoqueue;

CVidCapture::CVidCapture()
	
{
    m_spDeviceInfo.reset(VideoCaptureFactory::CreateDeviceInfo(0));
    m_nNumberOfDevices = m_spDeviceInfo->NumberOfDevices();
    if (m_nNumberOfDevices > 0)
    {
        char deviceNameUTF8[128];
        char deviceUniqueIdUTF8[128];
        // generally, the last device is the front camera,
        // so start from last
        int32_t nNumber = 0;
        for (int32_t i = m_nNumberOfDevices - 1; i >= 0; --i)
        {
            m_spDeviceInfo->GetDeviceName(i, deviceNameUTF8, 128,
                    deviceUniqueIdUTF8, 128);
            // try to find the front camera
            if (strstr(deviceNameUTF8, "front") != NULL)
            {
                nNumber = i;
                m_bIsFrontCamera = true;
                break;
            }
        }
        m_spVcm = OpenVideoCaptureDevice(nNumber);
    }
    else
    {
        LOGE("no video capture device found");
        return;
    }

    if (m_spVcm != NULL)
    {
        m_spVcm->RegisterCaptureDataCallback(*this);
        m_spVcm->RegisterCaptureCallback(*this);
    }
    else
    {
        LOGE("open video capture device failed");
        return;
    }	

	m_RtspServer = new RTSPServerInstance();
}

CVidCapture::~CVidCapture()
{

}

bool CVidCapture::IsValid(CVidCapture * p)
{

}

void CVidCapture::AttachPreviewHolder(void *prevHolder)
{
    m_spVcm->AttachToPreview(prevHolder);
    m_jPreviewHolder = prevHolder;
}


//FILE *fp2=fopen("/sdcard/test.h264", "wb");
int CVidCapture::StartCapture(VideoCaptureCapability & capability, int nOrient)
{
    int32_t nErr = 0;
    if (m_spVcm.get() == NULL)
    {
        return 0;
    }
    if (m_spVcm->CaptureStarted())
    {
        return 0;
    }

    VideoCaptureRotation orient;
    m_spDeviceInfo->GetOrientation(m_strCaptureId.c_str(), orient);
    int nOrientNew = static_cast<int>(orient / kCameraRotate90) + nOrient;
    while (nOrientNew < 0)
    {
        nOrientNew += 4;
    }
    nOrientNew %= 4;
    orient = static_cast<VideoCaptureRotation>(nOrientNew * kCameraRotate90);
 //   m_spVcm->SetCaptureRotation(orient);

    nErr = m_spVcm->StartCapture(capability);
    if (nErr != 0)
    {
        LOGE("start video capture failed: %d", nErr);
        return 0;
    }
    m_capability = capability;

	m_nWidth = capability.width;
	m_nHeight = capability.height;
	m_nFps = capability.maxFPS;

	m_pBuf = new u_int8_t[m_nWidth * m_nHeight * 3 / 2];
	memset(m_pBuf, 0, m_nWidth * m_nHeight * 3 / 2);

}

void CVidCapture::StopCapture()
{

}

bool CVidCapture::StartPushStream()
{
	LOGI("start video stream push");
	m_RtspServer->Start(m_nWidth, m_nHeight, m_nFps);

	frame_queue_init(&videoqueue);
	frame_queue_start(&videoqueue);		
	return true;
}

bool CVidCapture::StopPushStream()
{
	frame_queue_destroy(&videoqueue);
	return true;
}

void CVidCapture::SetPreviewRotation(int nRotation)
{

}

void CVidCapture::GetCapability(VideoCaptureCapability & capability)
{

}

void CVidCapture::SetOrientation(int nOrient)
{

}

//FILE *fp =fopen("/sdcard/test1.yuv", "wb");
void CVidCapture::OnIncomingCapturedFrame(const int32_t id, I420VideoFrame & videoFrame)
{
	int size = videoFrame.width() * videoFrame.height();
	memcpy(m_pBuf, videoFrame.buffer(kYPlane), size);
	memcpy(m_pBuf + size, videoFrame.buffer(kUPlane), size / 4);	
	memcpy(m_pBuf + size * 5 / 4, videoFrame.buffer(kVPlane), size / 4);		

	StreamBuf struBuf;
	struBuf.frame = m_pBuf;
	struBuf.bufsize = size * 3 / 2;
	
    if(frame_queue_count(&videoqueue) > 0)
    {
		StreamBuf tmpBuf;
	    frame_queue_get(&videoqueue, &tmpBuf, 1);
    }
	
	frame_queue_put(&videoqueue, &struBuf);	
	


}

void CVidCapture::OnCaptureDelayChanged(const int32_t id, const int32_t delay)
{}

void CVidCapture::OnCaptureFrameRate(const int32_t id, const uint32_t frameRate)
{

}

void CVidCapture::OnNoPictureAlarm(const int32_t id, const VideoCaptureAlarm alarm)
{}

webrtc::scoped_refptr<VideoCaptureModule>
CVidCapture::OpenVideoCaptureDevice(uint32_t device)
{
    char device_name[256];
    char unique_name[256];

    int32_t nErr = m_spDeviceInfo->GetDeviceName(device, device_name, 256, unique_name, 256);
    if (nErr != 0)
    {
        LOGE("get video capture name failed: %d", device);
        return NULL;
    }

    m_bIsFrontCamera = (strstr(device_name, "front") != NULL);

    webrtc::scoped_refptr<VideoCaptureModule> module(
            VideoCaptureFactory::Create(device, unique_name));
    if (module.get() == NULL)
    {
        LOGE("create video capture factory of `%s' failed.", unique_name);
        return NULL;
    }

    m_nCamera = (int32_t) device;
    m_strCaptureId = unique_name;
    m_spDeviceInfo->GetOrientation(unique_name, m_initialOrient);
    LOGI("camera: %s, initial-orientation: %d", unique_name, m_initialOrient);
    return module;
}


