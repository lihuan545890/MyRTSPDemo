/*
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "H264LiveCaptureThread.h"
#include "framequeue.h"

using namespace std;
extern FrameQueue videoqueue;
FILE *fp1 =fopen("/sdcard/test.h264", "wb");
FILE *fp =fopen("/sdcard/test.yuv", "wb");
H264LiveCaptureThread::H264LiveCaptureThread()
    : mRunning(false), mExitFlag(false), mFrameBufLen(0), mTruncatedLen(0)
{
    memset(mFrameBuf, 0, sizeof(mFrameBuf));

}
 
H264LiveCaptureThread::~H264LiveCaptureThread()
{

}

bool H264LiveCaptureThread::Create(int width, int height, int fps)
{	
    if (mRunning)
    {
        return false;
    }

	mWidth     = width;
	mHeight    = height;
	mFrameRate = fps;
	
	InitVideo();

    if (0 != pthread_create(&mThread, NULL, H264LiveCaptureThread::H264LiveCaptureProc, this))
    {
        return false;
    }

    mRunning = true;

    Capture();

    return true;
}

void H264LiveCaptureThread::Destroy()
{
    if (mRunning)
    {
        mExitFlag = true;
        pthread_cond_signal(&mCondThread);

        pthread_join(mThread, NULL);

        pthread_mutex_destroy(&mLockBuf);
        pthread_mutex_destroy(&mLockThread);
        pthread_cond_destroy(&mCondThread);
        
        mRunning = false;
    }
}

void H264LiveCaptureThread::Capture()
{
    if (!mRunning)
    {
        return;
    }

    pthread_cond_signal(&mCondThread);
}

void H264LiveCaptureThread::Export(void* buf, int len, int* frameLen, int* truncatedLen)
{
    int exportLen = mFrameBufLen;

    pthread_mutex_lock(&mLockBuf);
    if (mFrameBufLen > len) 
    {   
        *truncatedLen = mTruncatedLen + mFrameBufLen - len;
        exportLen = len;
    }
    else
    {
        *truncatedLen = mTruncatedLen;
    }
    memcpy(buf, mFrameBuf, exportLen);
//	fwrite(buf, 1, exportLen, fp);
	//LOGI("exportLen: %d", exportLen);
    *frameLen = exportLen;

    pthread_mutex_unlock(&mLockBuf);
}

bool H264LiveCaptureThread::GetExitFlag()
{
    return mExitFlag;
}


void* H264LiveCaptureThread::H264LiveCaptureProc(void* ptr)
{
    H264LiveCaptureThread* thread = (H264LiveCaptureThread*)ptr;

    while (1)
    {
        if (thread->GetExitFlag())
        {
            break;
        }

        thread->CaptureProc();
    }

    pthread_exit(NULL);
}

#if 1
void H264LiveCaptureThread::CaptureProc()
{
    int ret;
    void* outBuf = NULL;  
    int outLen = 0;
	struct timeval t_enc_start,t_enc_end;	
	struct timeval t_queue_start,t_queue_end;		
	int nRes = -1;
//	gettimeofday(&t_queue_start, NULL);

    pthread_mutex_lock(&mLockThread);
    pthread_cond_wait(&mCondThread, &mLockThread);
    pthread_mutex_unlock(&mLockThread);

   // ret = H264LiveCapture(&mCtx, &outBuf, &outLen);
   	StreamBuf frameBuf;
 	ret = frame_queue_get(&videoqueue, &frameBuf, 1);
//	fwrite(frameBuf.frame, 1, frameBuf.bufsize, fp1);
//	gettimeofday(&t_queue_end, NULL);
 
//	LOGI("queue time: %ld ms", ((t_queue_end.tv_usec - t_queue_start.tv_usec)/1000 + (t_queue_end.tv_sec - t_queue_start.tv_sec)*1000));

   
    if (frameBuf.bufsize> 0)
    {	
	   	if(frame_queue_count(&videoqueue) >= 0)
	   	
		{
			gettimeofday(&t_enc_start, NULL);
			if(frameBuf.frame!=NULL)
			{
			//	fwrite(frameBuf.frame, 1, frameBuf.bufsize, fp);
				nRes = EncVideo(frameBuf.frame, &outBuf, &outLen);
			}
			else
			{
				return ;
			}
			
		//	LOGI("outLen..............................%d, nRes:%d, mWidth:%d, mHeight:%d", outLen, nRes, mWidth, mHeight);
			gettimeofday(&t_enc_end, NULL);	
		//	LOGI("enc time: %lld ms", ((t_enc_end.tv_usec - t_enc_start.tv_usec)/1000 + (t_queue_end.tv_sec - t_queue_start.tv_sec)*1000));

/*			if(nRes > 0)
			{	
				fwrite((uint8_t*)outBuf, 1, outLen, fp1);
			}
*/	
	        unsigned int frameSize = outLen;
	        int truncatedSize = 0;
	        if (frameSize > sizeof(mFrameBuf))
	        {
	            truncatedSize = frameSize - sizeof(mFrameBuf);
	            frameSize = sizeof(mFrameBuf); 
	        }  
			if(outBuf != NULL)
			{	
				memcpy(mFrameBuf, outBuf, frameSize);
			}

	        pthread_mutex_lock(&mLockBuf);
			
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        

	        mFrameBufLen = frameSize;
	        mTruncatedLen = truncatedSize;
	        pthread_mutex_unlock(&mLockBuf);			
		}
		else
		{
	        pthread_mutex_lock(&mLockBuf);
	        mFrameBufLen = 0;
	        mTruncatedLen = 0;
	        pthread_mutex_unlock(&mLockBuf);
		}

    }
    else
    {
        pthread_mutex_lock(&mLockBuf);
        mFrameBufLen = 0;
        mTruncatedLen = 0;
        pthread_mutex_unlock(&mLockBuf);
    }


}
#else
void H264LiveCaptureThread::CaptureProc()
{

}
#endif

int H264LiveCaptureThread::InitVideo()
{
	av_register_all();  
 
//	AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_H264);
	AVCodec *codec =  avcodec_find_encoder_by_name("libx264");
	if (!codec) {
		LOGE("AV_CODEC_ID_H264 codec not found!");
		exit(1);
	}  

	codecContext = avcodec_alloc_context3(codec);
	if (!codec) {
		LOGE("couldn't allocate codec context");
		exit(1);
	}

	/* put sample parameters */
	//codecContext->bit_rate = 1024*1000;//400000*4.2;
	/* resolution must be a multiple of two */
	codecContext->width  = mWidth;
	codecContext->height = mHeight;
	/* frames per second */
	codecContext->time_base = (AVRational ) {1, mFrameRate};
	codecContext->gop_size = mFrameRate; /* emit one intra frame every ten frames */
	codecContext->max_b_frames = 1; 
	codecContext->pix_fmt = AV_PIX_FMT_YUV420P;

	av_opt_set(codecContext->priv_data, "profile", "baseline", 0);
	av_opt_set(codecContext->priv_data, "preset", "ultrafast", 0);

	if (avcodec_open2(codecContext, codec, NULL) < 0) {
		LOGE("couldn't open codec");
		exit(1);
	}
	pFrameYUV  = av_frame_alloc();
	out_buffer = (uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, mWidth, mHeight));
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P, mWidth, mHeight);	
	
}

int H264LiveCaptureThread::EncVideo(uint8_t* buf, void** output, int* len)
{
	struct timeval t_start,t_end;	

	int frameBufLen = 0;

	int nSize = mWidth * mHeight;
	memcpy(pFrameYUV->data[0],buf,nSize);
	memcpy(pFrameYUV->data[1],buf + nSize, nSize / 4);		
	memcpy(pFrameYUV->data[2],buf + nSize * 5 / 4,nSize  / 4);	

	pFrameYUV->format = AV_PIX_FMT_YUV420P;
	pFrameYUV->width = mWidth;
	pFrameYUV->height = mHeight;	

	av_init_packet(&packet);	
	packet.data = NULL;
	packet.size = 0;	
	
	if (avcodec_encode_video2(codecContext, &packet, pFrameYUV, &got_output)) {
		LOGE("couldn't encode frame");
		return -1;
	}

	if (got_output) {
	
		*output = packet.data;
		*len = packet.size;
		av_free_packet(&packet);
	} 

	return got_output;
}
