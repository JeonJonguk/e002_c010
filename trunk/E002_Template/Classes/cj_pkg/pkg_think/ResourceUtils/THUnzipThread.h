//
//  THUnzipThread.h
//  ithink
//
//  Created by pureMini on 13. 1. 14..
//
//

#ifndef ithink_THUnzipThread_h
#define ithink_THUnzipThread_h

#include "THThread.h"
#include "THThreadDelegate.h"
#include <string>


class THUnzipThread : public THThread
{
private:
	int m_num;
	std::string m_filePath;
	std::string m_destPath;
	THThreadDelegate *m_delegate;
	bool m_live;
	
public:
	
	THUnzipThread(int num = 0);
	~THUnzipThread();
	void unzip(const char *pszFilePath, const char *pszDestPath, THThreadDelegate *pDelegate);
	int run();
	void stop();
	void cleanup();
};

#endif
