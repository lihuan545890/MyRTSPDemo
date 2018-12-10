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
#ifndef _H264_LIVE_CAPTURE_THREAD_HPP
#define _H264_LIVE_CAPTURE_THREAD_HPP

#include <pthread.h>
#include <stdlib.h>

extern "C" {
#include	"libavcodec/avcodec.h"
#include	"libavformat/avformat.h"
#include	"libavutil/opt.h"
#include	"libavutil/imgutils.h"
#include    "libavutil/avstring.h"
#include    "libavutil/error.h"
#include 	"libavutil/time.h"
#include	"libswscale/swscale.h"
#include 	"libswresample/swresample.h"
}

#define H264_MAX_FRAME_SIZE (100 * 1024)

#define H264_LIVE_CAPTURE_SUCCESS                 0

class H264LiveCaptureThread
{
public:
    H264LiveCaptureThread();
    ~H264LiveCaptureThread();

    bool Create(int width, int height, int fps);
    void Destroy();

    void Capture();
    void Export(void* buf, int len, int* frameLen, int* truncatedLen);

    bool GetExitFlag();

    static void* H264LiveCaptureProc(void* ptr);
    void CaptureProc();
    int InitVideo();
    int EncVideo(AVFrame* frame, void** output, int* len);

private:
 //   H264LiveCaptureContext mCtx;
    bool mRunning;
    bool mExitFlag;
    pthread_t mThread;
    pthread_cond_t mCondThread;
    pthread_mutex_t mLockThread;
    pthread_mutex_t mLockBuf;
    char mFrameBuf[H264_MAX_FRAME_SIZE];
    int mFrameBufLen;
    int mTruncatedLen;
	int mWidth;
	int mHeight;
	int mFrameRate;
	
	AVCodecContext *codecContext;

	AVFrame *frame;
	AVFrame *tmpFrame;
	AVPacket packet;
	int count, got_output;
    
};

#endif
