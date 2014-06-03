//
//  CJParseThread.cpp
//  Think
//
//  Created by pureye4u BX on 12. 6. 14..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "CJParseThread.h"
#include "cocos2d.h"


static CJParseThread *s_currentThread = NULL;


CJParseThread *CJParseThread::getCurrentThread()
{
	if(s_currentThread == NULL)
	{
		s_currentThread = new CJParseThread();
	}
	
	return s_currentThread;
}

void CJParseThread::destroy()
{
	if(s_currentThread != NULL)
	{
		s_currentThread->join();
		pthread_exit(NULL);
		delete s_currentThread;
		s_currentThread = NULL;
	}
}

CJParseThread::CJParseThread()
{

}

CJParseThread::~CJParseThread()
{
    
}


void CJParseThread::parseStart(CJAnimationParserDelegate* delegate)
{
    m_delegate = delegate;
    this->start();
}


int CJParseThread::run()
{
    m_delegate->begin();
    
    m_delegate->parseThreadStartCallback();
    
    m_delegate->parseThreadEndCallback();
    
    m_delegate->end();
    
    return 1;
}


void *CJParseThread::run_(void *pthis_)
{
	printf("THThread::run_(\n");
	CJParseThread *pthis = (CJParseThread *)pthis_;
	pthread_cleanup_push(CJParseThread::cleanup_, (void *)pthis);
	pthis->setRetval(pthis->run());
    //	pthread_exit(0);
	pthread_cleanup_pop(1);
	printf("THThread::run_)\n");
}

void CJParseThread::cleanup_(void *pthis_)
{
	printf("THThread::cleanup_(\n");
	CJParseThread *pthis = (CJParseThread *)pthis_;
	pthis->cleanup();
	printf("THThread::cleanup_)\n");
}

// Create new thread
void CJParseThread::start()
{
	printf("THThread::start()\n");
	pthread_create(&m_thread, NULL, CJParseThread::run_, (void *)this);
	pthread_detach(m_thread);
}

// Join thread
int CJParseThread::join()
{
	printf("THThread::join()\n");
	pthread_join(m_thread, NULL);
	return m_retval;
}

// Return value
void CJParseThread::setRetval(int r)
{
	m_retval = r;
}

void CJParseThread::cleanup()
{
	printf("THThread::cleanup()\n");
	
}
