#ifndef _FRAMEQUEUE_H
#define _FRAMEQUEUE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "androidlog.h"

#include	"libavcodec/avcodec.h"
#include	"libavformat/avformat.h"
#include	"libavutil/opt.h"
#include	"libavutil/imgutils.h"
#include    "libavutil/avstring.h"
#include    "libavutil/error.h"
#include 	"libavutil/time.h"
#include	"libswscale/swscale.h"
#include 	"libswresample/swresample.h"

typedef struct StreamBuf{
    AVFrame *frame;
    int bufsize;	
}StreamBuf;


typedef struct MyAVFrameList {
	StreamBuf buffer;
    struct MyAVFrameList *next;
    int serial;
} MyAVFrameList;


typedef struct FrameQueue {
    MyAVFrameList *first_frame, *last_frame;
    int nb_packets;
    int abort_request;
    int serial;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} FrameQueue;

int  frame_queue_init(FrameQueue *q);
void frame_queue_destroy(FrameQueue *q);
void frame_queue_start(FrameQueue *q);
int  frame_queue_put(FrameQueue *q, StreamBuf *frame);
void frame_queue_flush(FrameQueue *q);
void frame_queue_abort(FrameQueue *q);
int  frame_queue_get(FrameQueue *q, StreamBuf *frame, int block);
int  frame_queue_count(FrameQueue *q);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif




