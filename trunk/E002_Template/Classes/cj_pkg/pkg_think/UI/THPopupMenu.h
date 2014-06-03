//
//  THPopupMenu.h
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef PackageApp_PopupMenu_h
#define PackageApp_PopupMenu_h

#include "cocos2d.h"

class THPopupMenu : public cocos2d::CCMenu
{
public:
	static THPopupMenu *menuWithItems(cocos2d::CCMenuItem* item, ...);
	static THPopupMenu *menuWithItem(cocos2d::CCMenuItem* item);
	virtual void registerWithTouchDispatcher();
	
protected:
	
};

#endif
