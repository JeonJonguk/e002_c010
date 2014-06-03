//
//  THProgress.h
//  PackageApp
//
//  Created by pureye4u BX on 12. 8. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef PackageApp_THProgress_h
#define PackageApp_THProgress_h

#include "cocos2d.h"

class THProgress : public cocos2d::CCLayer
{
public:
	THProgress();
	~THProgress();
	virtual bool init();
	
	CREATE_FUNC(THProgress);
	
protected:
	int m_currentProgress;
	
	virtual void hndUpdateProgress();
};

#endif
