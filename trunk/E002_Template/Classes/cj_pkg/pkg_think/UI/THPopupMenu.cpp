//
//  THPopupMenu.cpp
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THPopupMenu.h"

enum
{
	// CCMenu priority on PopupMenu
	kPopupMenuPriority = -131,
};

using namespace cocos2d;

THPopupMenu *THPopupMenu::menuWithItems(CCMenuItem* item, ...)
{
	va_list args;
	va_start(args,item);
	THPopupMenu *pRet = new THPopupMenu();
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

THPopupMenu* THPopupMenu::menuWithItem(CCMenuItem* item)
{
	return menuWithItems(item, NULL);
}

void THPopupMenu::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kPopupMenuPriority, true);
}
