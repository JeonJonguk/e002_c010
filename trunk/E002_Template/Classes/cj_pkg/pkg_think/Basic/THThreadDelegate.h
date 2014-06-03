//
//  THThreadDelegate.h
//  ithink
//
//  Created by pureMini on 13. 1. 14..
//
//

#ifndef ithink_THThreadDelegate_h
#define ithink_THThreadDelegate_h

class THThreadDelegate
{
public:
	virtual void end(){}
	virtual void error(int type, const char *description){}
};

#endif
