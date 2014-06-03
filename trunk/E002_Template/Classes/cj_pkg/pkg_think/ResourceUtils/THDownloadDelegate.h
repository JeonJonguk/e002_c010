//
//  THDownloadDelegate.h
//  Think
//
//  Created by pureye4u BX on 12. 6. 13..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef Think_THDownloadDelegate_h
#define Think_THDownloadDelegate_h

class THDownloadDelegate
{
public:
	virtual void begin(){}
	virtual void setProgress(double current){}
	virtual void setStatus(int type){}
	virtual void end(){}
	virtual void error(int type, const char *description){}
	virtual void trace(const char *message){}
};

#endif
