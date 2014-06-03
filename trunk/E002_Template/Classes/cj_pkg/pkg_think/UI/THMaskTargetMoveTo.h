//
//  THMaskTargetMoveTo.h
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 5..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef PackageApp_THMaskTargetMoveTo_h
#define PackageApp_THMaskTargetMoveTo_h

#include "cocos2d.h"

class THMaskTargetMoveTo : public cocos2d::CCMoveTo
{
public:
	static THMaskTargetMoveTo* actionWithDuration(float duration, const cocos2d::CCPoint& position);
protected:
	virtual void startWithTarget(cocos2d::CCNode *target);
	virtual void update(float time);
	virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone *pZone);
};

#endif
