//
//  THURLRequestDelegate.h
//  ithink
//
//  Created by pureMini on 13. 2. 4..
//
//

#ifndef ithink_THURLRequestDelegate_h
#define ithink_THURLRequestDelegate_h

class THURLRequestDelegate
{
public:
	virtual void progress(double dCurrent){}
	virtual void complete(const char *pszResult){}
	virtual void error(int iType, const char *pszDescription){}
	virtual void trace(const char *pszMessage){}
};

#endif
