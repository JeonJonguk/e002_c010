//
//  THThread.h
//  Think
//
//  Created by pureye4u BX on 12. 6. 14..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef Think_THThread_h
#define Think_THThread_h

#include <pthread.h>

class THThread
{
private:
	pthread_t m_thread;
	int m_retval;
	
public:
	static void *run_(void *);
	static void cleanup_(void *);
	
	THThread();
	~THThread();
	virtual int run();
	void start();
	int join();
	void setRetval(int r);
	void cleanup();
};

#endif
