//
//  THThread.cpp
//  Think
//
//  Created by pureye4u BX on 12. 6. 14..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THThread.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Class methods

void *THThread::run_(void *pthis_)
{
	printf("THThread::run_(\n");
	THThread *pthis = (THThread *)pthis_;
	pthread_cleanup_push(THThread::cleanup_, (void *)pthis);
	pthis->setRetval(pthis->run());
//	pthread_exit(0);
	pthread_cleanup_pop(1);
	printf("THThread::run_)\n");
}

void THThread::cleanup_(void *pthis_)
{
	printf("THThread::cleanup_(\n");
	THThread *pthis = (THThread *)pthis_;
	pthis->cleanup();
	printf("THThread::cleanup_)\n");
}

// Member methods

// Constructor
THThread::THThread()
{
	printf("THThread::THThread()\n");
}

// Destructor
THThread::~THThread()
{
	printf("THThread::~THThread()\n");
}

// Run thread (for override)
int THThread::run()
{
	printf("THThread::run()\n");
	return 0;
}

// Create new thread
void THThread::start()
{
	printf("THThread::start()\n");
	pthread_create(&m_thread, NULL, THThread::run_, (void *)this);
	pthread_detach(m_thread);
}

// Join thread
int THThread::join()
{
	printf("THThread::join()\n");
	pthread_join(m_thread, NULL);
	return m_retval;
}

// Return value
void THThread::setRetval(int r)
{
	m_retval = r;
}

void THThread::cleanup()
{
	printf("THThread::cleanup()\n");
	
}