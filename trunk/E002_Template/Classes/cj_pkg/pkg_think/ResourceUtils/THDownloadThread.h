//
//  THDownloadThread.h
//  Think
//
//  Created by pureye4u BX on 12. 6. 14..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef Think_THDownloadThread_h
#define Think_THDownloadThread_h

#include "THThread.h"
#include "THDownloadDelegate.h"
#include <string>


class THDownloadThread : public THThread
{
private:
	int m_num;
	int m_pause;
	double m_before;
	double m_current;
	double m_current_add;
	double m_total;
	long long m_currentSize;
	long m_fullSize;
	bool m_checkWaiting;
	bool m_downloadCompleted;
	std::string m_fileName;
	std::string m_URL;
	std::string m_destination;
	THDownloadDelegate *m_delegate;
//	CURL *m_curl;
//	FILE *m_fp;
	
	int startDownload(const char *outfileName);
	int unpackFile(const char *fileName);
	
public:
	static THDownloadThread *getCurrentThread();
	static void destroy();
	THDownloadThread(int num = 0);
	~THDownloadThread();
	void download(const char *fileName, long long currentSize, long fullSize, const char *URL, const char *destination, THDownloadDelegate *delegate);
//	void clear();
	int run();
	void play();
	void pause();
	void progress(double current, double total);
	
};

#endif
