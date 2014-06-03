//
//  THURLRequest.h
//  ithink
//
//  Created by pureMini on 13. 2. 4..
//
//

#ifndef __ithink__THURLRequest__
#define __ithink__THURLRequest__

#include "THURLRequestDelegate.h"
#include <string>

class THURLRequest
{
public:
	// Member
	
	// Mehod
	THURLRequest();
	virtual ~THURLRequest();
	bool init();
	bool initWithURL(const char *pszURL = NULL);
	void setHeader();
	void setMethod();
	void setData();
	
protected:
	// Member
	THURLRequestDelegate *m_pDelegate;
	
	// Mehod
	void load(const char *pszURL = NULL);
	
};

#endif /* defined(__ithink__THURLRequest__) */
