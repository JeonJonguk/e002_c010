//
//  THPopupManager.cpp
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THPopupManager.h"

using namespace cocos2d;

static THPopupView *s_sharedPopupView = NULL;
static THPopupDelegate *s_sharedPopupDelegate = NULL;
static int s_sharedPopupReturnValue = 0;
static bool s_hasReturnValue = false;
static bool s_isOpened = false;

void THPopupManager::destroy()
{
//	CCLog("######### THPopupManager::destroy");
	if(s_isOpened && s_sharedPopupView != NULL)
	{
//		CCLog("########### has view: %d", s_sharedPopupView->retainCount());
		s_sharedPopupView->stop();
//		if(s_sharedPopupView->getParent())
//		{
//			s_sharedPopupView->removeFromParentAndCleanup(true);
//		}
	}
	
	s_sharedPopupView = NULL;
	s_sharedPopupDelegate = NULL;
	s_sharedPopupReturnValue = 0;
	s_hasReturnValue = false;
	s_isOpened = false;
}

void THPopupManager::reset()
{
//	if(s_isOpened && s_sharedPopupView != NULL)
//	{
//		s_sharedPopupView->release();
//	}
	
	s_sharedPopupView = NULL;
	s_sharedPopupDelegate = NULL;
	s_sharedPopupReturnValue = 0;
	s_hasReturnValue = false;
	s_isOpened = false;
}

bool THPopupManager::isOpened()
{
	return s_isOpened;
}

void THPopupManager::show(THPopupView *popupView, bool isModal, THPopupDelegate *delegate)
{
	if(!s_isOpened && s_sharedPopupView == NULL)
	{
//		CCLog("######### THPopupManager::show");
		s_isOpened = true;
		
		s_sharedPopupView = popupView;
		
		CCScene *currentScene = CCDirector::sharedDirector()->getRunningScene();
	 	
		currentScene->addChild(s_sharedPopupView);
//		s_sharedPopupView->release();
		s_sharedPopupView->setModal(isModal);
		s_sharedPopupView->show();
		
		s_sharedPopupReturnValue = 0;
		
		if(delegate != NULL)
		{
			s_sharedPopupDelegate = delegate;
		}
	}
//	else
//	{
//		CCLog("@@@ Not");
//	}
}

void THPopupManager::setSharedReturnValue(int value)
{
	s_sharedPopupReturnValue = value;
}

void THPopupManager::hndPopupRemoved(THPopupView *popupView)
{
	if(popupView == s_sharedPopupView)
	{
//		CCLog("######### THPopupManager::hndPopupRemoved");
		s_sharedPopupView = NULL;
		s_isOpened = false;
		if(s_sharedPopupDelegate != NULL)
		{
			s_sharedPopupDelegate->hndPopupClosed(s_sharedPopupReturnValue);
		}
	}
//	else
//	{
//		CCLog("Not match");
//	}
}