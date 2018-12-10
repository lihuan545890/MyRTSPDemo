#ifndef RTSP_SERVER_INSTANCE_H
#define RTSP_SERVER_INSTANCE_H
#include "BasicUsageEnvironment.hh"
#include "GroupsockHelper.hh"
#include "liveMedia.hh"
#include "androidlog.h"

class RTSPServerInstance
{
	public:
		RTSPServerInstance();
		~RTSPServerInstance();
		bool Start(int nWidth, int nHeight, int nFps);
		bool Stop();

	private:
		UsageEnvironment* m_uEnv;
		TaskScheduler* m_scheduler;
		RTSPServer* m_rtspServer;
};


#endif