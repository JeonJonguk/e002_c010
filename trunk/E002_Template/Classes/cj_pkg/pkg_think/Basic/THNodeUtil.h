//
//  THNodeUtil.h
//  Think
//
//  Created by pureye4u BX on 12. 7. 9..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef Think_THNodeUtil_h
#define Think_THNodeUtil_h

#include "cocos2d.h"

class THNodeUtil : public cocos2d::CCObject
{
public:
	static void removeAllChildren(cocos2d::CCNode *pParent);
	static bool isChildren(cocos2d::CCNode *pParent, cocos2d::CCNode *pChild);
	
	static void setAliasTexParameters(cocos2d::CCSprite *pSprite);
	static void setAliasTexParameters(cocos2d::CCMenuItemImage *pItem);
	static void setAntiAliasTexParameters(cocos2d::CCSprite *pSprite);
	static void setAntiAliasTexParameters(cocos2d::CCMenuItemImage *pItem);
	
	static cocos2d::CCSprite *capture(cocos2d::CCNode *pTarget);
	static cocos2d::CCSprite *captureWithSize(cocos2d::CCNode *pTarget, const cocos2d::CCRect &tBounds);
	
private:
	static void cleanNode(cocos2d::CCNode *pNode);
};

#endif
