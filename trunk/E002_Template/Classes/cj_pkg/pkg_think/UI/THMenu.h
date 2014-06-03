//
//  THMenu.h
//  PackageApp
//
//  Created by pureye4u BX on 12. 9. 12..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef PackageApp_THMenu_h
#define PackageApp_THMenu_h

#include "cocos2d.h"

class THMenu : public cocos2d::CCMenu
{
public:
	static THMenu *menuWithPriorityAndItems(int priority, cocos2d::CCMenuItem* item, ...);
	static THMenu *menuWithPriorityAndItem(int priority, cocos2d::CCMenuItem* item);
	static THMenu *menuWithItems(cocos2d::CCMenuItem* item, ...);
	static THMenu *menuWithItem(cocos2d::CCMenuItem* item);
	virtual int getPriority();
	virtual void setPriority(int priority);
	virtual void registerWithTouchDispatcher();

	
protected:
	int m_priority;
	
};

#endif
