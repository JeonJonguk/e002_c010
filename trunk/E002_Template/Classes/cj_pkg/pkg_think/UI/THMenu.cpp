//
//  THMenu.cpp
//  PackageApp
//
//  Created by pureye4u BX on 12. 9. 12..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THMenu.h"

using namespace cocos2d;

THMenu *THMenu::menuWithPriorityAndItems(int priority, cocos2d::CCMenuItem *item, ...)
{
	va_list args;
	va_start(args,item);
	THMenu *pRet = new THMenu();
	if (pRet && pRet->create(item, args))
	{
		pRet->setPriority(priority);
		pRet->autorelease();
		va_end(args);
		return pRet;
	}
	va_end(args);
	CC_SAFE_DELETE(pRet);
	return NULL;
}

THMenu* THMenu::menuWithPriorityAndItem(int priority, cocos2d::CCMenuItem *item)
{
	return menuWithPriorityAndItems(priority, item, NULL);
}

THMenu *THMenu::menuWithItems(CCMenuItem* item, ...)
{
	va_list args;
	va_start(args,item);
	THMenu *pRet = new THMenu();
	if (pRet && pRet->create(item, args))
	{
		pRet->autorelease();
		va_end(args);
		return pRet;
	}
	va_end(args);
	CC_SAFE_DELETE(pRet);
	return NULL;
}

THMenu* THMenu::menuWithItem(CCMenuItem* item)
{
	return menuWithItems(item, NULL);
}

int THMenu::getPriority()
{
	return m_priority;
}

void THMenu::setPriority(int priority)
{
	m_priority = priority;
}

void THMenu::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_priority, true);
}
