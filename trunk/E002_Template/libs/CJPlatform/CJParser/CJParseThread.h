//
//  CJParseThread.h
//
//
//  Created by pdj1117  on 14. 1. 22..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef CJParseThread_h
#define CJParseThread_h

#include <string>

#include "CJAnimationParserDelegate.h"


class CJParseThread
{
private:
	pthread_t m_thread;
	int m_retval;
    
public:
    static void *run_(void *);
	static void cleanup_(void *);
    
	void setRetval(int r);
	void cleanup();
    
private:
    
    CJAnimationParserDelegate* m_delegate;

	
public:
	static CJParseThread *getCurrentThread();
	static void destroy();
	CJParseThread();
	~CJParseThread();
    
    void parseStart(CJAnimationParserDelegate* delegate);
    
    void start();
	int join();

	int run();
    
private:
	
};

#endif
