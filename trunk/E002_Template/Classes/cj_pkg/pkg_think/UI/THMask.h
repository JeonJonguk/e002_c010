//
//  THMask.h
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 5..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef PackageApp_THMask_h
#define PackageApp_THMask_h

#include "cocos2d.h"

class THMask : public cocos2d::CCSprite
{
public:
	THMask();
	~THMask();
	virtual bool init();
	virtual cocos2d::CCSprite *getMask();
	virtual void setMask(cocos2d::CCSprite *mask);
	virtual cocos2d::CCSprite *getTarget();
	virtual void setTarget(cocos2d::CCSprite *target);
	virtual cocos2d::CCPoint getTargetPosition();
	virtual void setTargetPosition(cocos2d::CCPoint position);
	virtual void refresh();
protected:
	cocos2d::CCSprite *m_mask;
	cocos2d::CCSprite *m_target;
	cocos2d::CCSize m_maskSize;
	cocos2d::CCSize m_targetSize;
	cocos2d::CCPoint m_targetPosition;
	
	virtual void updateMask();
};

#endif
