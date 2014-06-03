//
//  THPopupManager.cpp
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef PackageApp_THPopupManager_h
#define PackageApp_THPopupManager_h

#include "cocos2d.h"
#include "THPopupView.h"
#include "THPopupDelegate.h"

class THPopupManager : public cocos2d::CCObject
{
public:
	static void destroy();
	static void reset();
	static bool isOpened();
	static void show(THPopupView *THPopupView, bool isModal = true, THPopupDelegate *delegate = NULL);
	static void setSharedReturnValue(int value);
	static void hndPopupRemoved(THPopupView *popupView);
	
	
};

#endif
