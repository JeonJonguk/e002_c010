//
//  THPopupView.cpp
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 2..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THPopupView.h"
#include "THPopupManager.h"
#include "THNodeUtil.h"

enum
{
	kZIndexBlock,
	kZIndexView,
};

enum
{
	kTouchProrityPopup = -130,
};

enum
{
	kPopupStatusNone,
	kPopupStatusOpening,
	kPopupStatusOpened,
	kPopupStatusClosing,
	kPopupStatusClosed,
};

using namespace cocos2d;

THPopupView::THPopupView()
{
	//CCLog("THPopupView constrected");
}

THPopupView::~THPopupView()
{
//	CCLog("%%%%%%%%%%%%%%%%%% THPopupView destrected");
//	m_view->removeAllChildrenWithCleanup(true);
	this->stop();
	
	
//	THNodeUtil::removeAllChildren(m_view);
//	m_view->release();
	
//	this->removeAllChildrenWithCleanup(true);
	THNodeUtil::removeAllChildren(this);
}

bool THPopupView::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	
	// Initialize
	m_status = kPopupStatusNone;
	m_isModal = false;
	m_popupArea = CCRectZero;
	
//	m_view = CCLayer::node();
	this->loadView();
	
	return true;
}

void THPopupView::show()
{
	m_status = kPopupStatusOpening;
	this->showBlock();
}

void THPopupView::hide()
{
//	CCLog("Hide");
	this->hidePopup();
}

void THPopupView::stop()
{
//	CCLog("######### %d", m_status);
	
	CCNode *block = this->getChildByTag(kZIndexBlock);
	if(block)
	{
//		CCLog("##### remove block");
		block->stopAllActions();
		block->removeFromParentAndCleanup(false);
	}
	m_view->stopAllActions();
//	m_view->removeFromParentAndCleanup(false);
	
//	this->removeFromParentAndCleanup(false);
	
	THPopupManager::hndPopupRemoved(this);
}

void THPopupView::setModal(bool isModal)
{
	m_isModal = isModal;
}

void THPopupView::showBlock()
{
	m_status = kPopupStatusOpening;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	CCLayer *block = CCLayerColor::create(ccc4(0, 0, 0, 0), winSize.width, winSize.height);
	block->setTag(kZIndexBlock);
	this->addChild(block, kZIndexBlock);
	block->runAction(CCSequence::create(
										 CCFadeTo::create(0.25f, 127),
										 CCCallFunc::create(this, callfunc_selector(THPopupView::showPopup)),
										 NULL));
}

void THPopupView::loadView()
{
	CCLog("Override this method");
//	m_popupArea.origin.x = 100;
//	m_popupArea.origin.y = 100;
//	m_popupArea.size.width = 824;
//	m_popupArea.size.height = 568;
//	
//	m_view = CCLayerColor::layerWithColorWidthHeight(ccc4f(255, 255, 255, 255), m_popupArea.size.width, m_popupArea.size.height);
//	m_view->retain();
//	m_view->setPosition(m_popupArea.origin);
}

void THPopupView::showPopup()
{
	m_status = kPopupStatusOpening;
	
	m_view->setScale(0.0);
	this->addChild(m_view, kZIndexView);
	m_view->release();
	m_view->runAction(CCSequence::create(
										  CCEaseSineInOut::create(CCScaleTo::create(0.25, 1.0)),
										  CCCallFunc::create(this, callfunc_selector(THPopupView::viewDidLoaded)),
										  NULL));
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kTouchProrityPopup, true);
	m_status = kPopupStatusOpened;
	
	// For debug : auto close
//	this->runAction(CCSequence::actions(
//										CCDelayTime::actionWithDuration(5.0),
//										CCCallFunc::actionWithTarget(this, callfunc_selector(PopupView::hidePopup)),
//										NULL));
}

void THPopupView::hidePopup()
{
	m_status = kPopupStatusOpened;
	
	CCNode *block = this->getChildByTag(kZIndexBlock);
	if(block)
	{
		m_status = kPopupStatusClosing;
		m_view->runAction(CCEaseSineInOut::create(CCScaleTo::create(0.25, 0.0)));
		block->runAction(CCSequence::create(
											 CCFadeTo::create(0.25, 0),
											 CCCallFunc::create(this, callfunc_selector(THPopupView::hideBlock)),
											 NULL));
	}
}

void THPopupView::hideBlock()
{
	m_status = kPopupStatusClosing;
	CCNode *block = this->getChildByTag(kZIndexBlock);
	if(block)
	{
		block->removeFromParentAndCleanup(true);
	}
	this->removeFromParentAndCleanup(true);
	m_status = kPopupStatusClosed;
//	CCLog("hideBlock");
	THPopupManager::hndPopupRemoved(this);
}

void THPopupView::hndTouchOutside()
{
	if(!m_isModal)
	{
		if(m_status == kPopupStatusOpening)
		{
			CCNode *block = this->getChildByTag(kZIndexBlock);
			if(block)
			{
				block->stopAllActions();
			}
			this->hide();
		}
		else if(m_status == kPopupStatusOpened)
		{
			this->hide();
		}
	}
}

void THPopupView::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool THPopupView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint p = pTouch->getLocationInView();
	if(m_popupArea.containsPoint(p))
	{
//		CCLog("In popup area");
	}
	else
	{
//		CCLog("Out of popup area");
		this->hndTouchOutside();
	}
	
	return true;
}

//void PopupView::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//	
//}
//
//void PopupView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//	
//}
//
//void PopupView::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
//{
//	this->ccTouchEnded(pTouch, pEvent);
//}
