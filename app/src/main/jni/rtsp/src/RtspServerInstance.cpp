#include "RtspServerInstance.h"
#include "H264LiveServerMediaSubsession.h"

RTSPServerInstance::RTSPServerInstance()
	:m_rtspServer(NULL),
	m_scheduler(NULL),
	m_uEnv(NULL)
	
{

}

RTSPServerInstance::~ RTSPServerInstance()
{

}

bool RTSPServerInstance::Start(int nWidth, int nHeight, int nFps)
{
	m_scheduler = BasicTaskScheduler::createNew();
	if(!m_scheduler)
	{
		return false;
	}

	m_uEnv = BasicUsageEnvironment::createNew(*m_scheduler);
	if(!m_uEnv)
	{
		return false;
	}

	m_rtspServer = RTSPServer::createNew(*m_uEnv, 554);
    if (m_rtspServer == NULL) 
    {
        m_rtspServer = RTSPServer::createNew(*m_uEnv, 8554, NULL);
    }	

	ServerMediaSession* sms = ServerMediaSession::createNew(*m_uEnv, "RTSPServer",
			0, "Camera server, streamed by the LIVE555 Media Server");	

	sms->addSubsession(H264LiveServerMediaSubsession::createNew(*m_uEnv,
		 nWidth, nHeight, nFps));

//	char* url = m_rtspServer->rtspURL(sms);
//	LOGI("Play this Stream %d x %d fps:%d using the URL: \"%s\"",nWidth,  nHeight,  nFps, url);
//	delete[] url;	

	m_uEnv->taskScheduler().doEventLoop();

	return true;
}

bool RTSPServerInstance::Stop()
{

}