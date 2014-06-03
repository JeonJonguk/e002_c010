//  CCScrollLayer.cpp
//  Museum
//
//  Created by GParvaneh on 29/12/2010.
//  Copyright 2010. All rights reserved.
//  Ported to C++ by Lior Tamam on 03/04/2011
//  Cleaned for Cocos2d-x V2.x by @HermanJakobi (01/12/12)

#include "CCScrollLayer.h"
#include "CJUtils.h"

USING_NS_CC;

enum
{
    kCCScrollLayerStateIdle,
    kCCScrollLayerStateSliding,
};

#define TOUCH_TAB_INTERVAL 17
#define TOUCH_SWIPE_TIME_INTERVAL 0.2
#define TOUCH_SWIPE_MINIMUM_WIDTH 10


//long millisecondNow()
//{
//    struct cc_timeval now;
//    CCTime::gettimeofdayCocos2d(&now, NULL);
//    CCLog("now.tv_sec = %i",now.tv_sec);
//    return (now.tv_sec * 1000 + now.tv_sec / 1000);
//}



#pragma mark - CCScrollLayerDelegate

void CCScrollLayerDelegate::onScrollLayerSelected(CCLayer* page, int pageIndex, CCNode* container)
{
    CCLog("CCScrollLayerDelegate: _delegate == NULL!");
}
void CCScrollLayerDelegate::onScrollLayerMoveTransform(CCLayer* page, float offset, float scrollWidth)
{
    CCLog("CCScrollLayerDelegate: _delegate == NULL!");
}

void CCScrollLayerDelegate::onScrollLayerMoveCancel()
{
    CCLog("CCScrollLayerDelegate: _delegate == NULL!");
}

void CCScrollLayerDelegate::onScrollLayerTouchBegan(CCTouch* touch){}
void CCScrollLayerDelegate::onScrollLayerTouchMove(CCTouch* touch){}
void CCScrollLayerDelegate::onScrollLayerMoveEnd(){}


#pragma mark - CCScrollLayer

CCScrollLayer::CCScrollLayer():
m_layerArray(NULL),
m_pContainer(NULL),
_touchEnable(false),
m_bSelected(false)
{
    _delegate = NULL;
}


CCScrollLayer::~CCScrollLayer()
{
    m_layerArray->removeAllObjects();
    CC_SAFE_RELEASE(m_layerArray);
}


CCScrollLayer* CCScrollLayer::create(CCArray *layers, int widthOffset, int startIndex /* default = 0 */)
{
	CCScrollLayer *pRet = new CCScrollLayer();
	if (pRet && pRet->init(layers, widthOffset, startIndex))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCScrollLayer::init(CCArray *layers, int widthOffset, int startIndex)
{	
	if (CCLayerColor::init())
	{		
        // offset added to show preview of next/previous screens
        CCSize s=CCDirector::sharedDirector()->getWinSize();
        
        if (!this->m_pContainer)
        {
            m_pContainer = CCLayer::create();
            this->m_pContainer->ignoreAnchorPointForPosition(true);
//            this->m_pContainer->setAnchorPoint(ccp(0.5f, 0.5f));
            this->m_pContainer->setPosition(ccp(0.0f, 0.0f));
            this->addChild(m_pContainer);
//            m_pContainer->setContentSize(CCSize(900.f, 768.f));
        }

        
		// Set up the starting variables
		if(!widthOffset)
		{
			widthOffset = 0;
		}
		currentScreen = startIndex+1;
//		_delegate = delegate;
        m_layerArray = new CCArray();
        m_layerArray->initWithArray(layers);
        
		scrollWidth  = widthOffset;
		scrollHeight = s.height;
		startWidth = scrollWidth;
		startHeight = scrollHeight;
		
		// Loop through the array and add the screens
		unsigned int i;
		for (i=0; i<layers->count(); i++)
		{
			CCLayer* l = static_cast<CCLayer*>(layers->objectAtIndex(i));
//			l->setAnchorPoint(ccp(0,0));
            l->ignoreAnchorPointForPosition(true);
            //l->setPosition(ccp(i*scrollWidth - (l->getContentSize().width/2), l->getPositionY()));
			l->setPosition(ccp((i*scrollWidth + (s.width/2 - l->getContentSize().width/2)), l->getPositionY()));
			m_pContainer->addChild(l);
		}
		
		// Setup a count of the available screens
		totalScreens = layers->count();
       
        float width = s.width/2 + (scrollWidth * totalScreens);
        m_pContainer->setContentSize(CCSize(width, 100));
        
		return true;	
	}
	
    
    return false;
    
}

void CCScrollLayer::onEnter()
{
    CCLayerColor::onEnter();
    
    m_fMinimumTouchLengthToSlide = 20.0f;
    
    registerWithTouchDispatcher();
    
    
    
    _touchEnable = true;
    schedule(schedule_selector(CCScrollLayer::setTransform), 1/60.f);
    schedule(schedule_selector(CCScrollLayer::tick), 1/10.f);
}

void CCScrollLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    unscheduleAllSelectors();
    CCLayerColor::onExit();
}

void CCScrollLayer::setDelegate(CCScrollLayerDelegate* pDelegate)
{
    _delegate = pDelegate;
    
    // for first positioning.
    float delay = (float)(currentScreen-1.0) / 3.0;
    moveToPage(currentScreen, delay);
}

#pragma mark - touch

bool CCScrollLayer::ccTouchBegan(CCTouch *touch, CCEvent *withEvent)
{
    if (m_bSelected)
        return false;
    
    if (!_touchEnable)
        return false;

    CCPoint touchPoint = touch->getLocation(); // Get the touch position
    touchPoint = this->getParent()->convertToNodeSpace(touchPoint);
    
    
    CCRect frame = this->boundingBox();
    frame.origin = this->getParent()->convertToNodeSpace(frame.origin);

    
    if (!frame.containsPoint(m_pContainer->convertToWorldSpace(m_pContainer->convertTouchToNodeSpace(touch)))) {
        return false;
    }
    
	startSwipe = (int)touchPoint.x;
    m_iState = kCCScrollLayerStateIdle;
//    m_pContainer->stopActionByTag(0); //remove action by m_pContainer
    
    beginTime = _currentTime;
    
    
    
	return true;
}

void CCScrollLayer::ccTouchMoved(CCTouch *touch, CCEvent *withEvent)
{
//    if(m_pScrollTouch != touch)
//        return;
    
    CCPoint touchPoint = touch->getLocation(); // Get the touch position
    touchPoint = this->getParent()->convertToNodeSpace(touchPoint);
    
    // If finger is dragged for more distance then minimum - start sliding and cancel pressed buttons.
    // Of course only if we not already in sliding mode
    if ((m_iState != kCCScrollLayerStateSliding) && (fabsf(touchPoint.x - startSwipe) >= m_fMinimumTouchLengthToSlide))
    {
        m_iState = kCCScrollLayerStateSliding;
        
        // Avoid jerk after state change.
        startSwipe = touchPoint.x;
        cancelAndStoleTouch(touch, withEvent);
    }
    
    if (m_iState == kCCScrollLayerStateSliding)
    {
        m_pContainer->setPosition(ccp((-(currentScreen-1)*scrollWidth)+(touchPoint.x-startSwipe), m_pContainer->getPositionY()));
        _delegate->onScrollLayerTouchMove(touch);
    }
    
}

void CCScrollLayer::ccTouchEnded(CCTouch *touch, CCEvent *withEvent)
{
    
//    if(m_pScrollTouch != touch)
//        return;
//    m_pScrollTouch = NULL;
    
    CCPoint touchPoint = touch->getLocation(); // Get the touch position
    touchPoint = this->getParent()->convertToNodeSpace(touchPoint);
	
	float endX = touchPoint.x;
    endTime = _currentTime;

    
    float dist =  (startSwipe - endX) / scrollWidth * 1.2;
    dist = CJUtils::roundValue(dist, 0);
    
   
    
    
    // tab
	if (fabsf(startSwipe - endX) < TOUCH_TAB_INTERVAL)
	{
        touchPoint = m_pContainer->convertToNodeSpace(touchPoint);
        
        for (int i = 0; i < m_layerArray->count(); i++)
        {
            CCLayer* layer = (CCLayer*)m_layerArray->objectAtIndex(i);
            
            if (layer->boundingBox().containsPoint(touchPoint))
            {
                CCLog("%d",i);
                this->selectedPage(i);
                break;
            }
        }
        return;
	}
    
    // fast flicking
    if (endTime - beginTime < TOUCH_SWIPE_TIME_INTERVAL)
    {
        if ( (startSwipe - endX  > TOUCH_SWIPE_MINIMUM_WIDTH) )
        {
            dist = MAX(1, dist);
        }
        else if( (endX - startSwipe > TOUCH_SWIPE_MINIMUM_WIDTH) )
        {
            dist = MIN(-1,dist);
        }
        
    }
    
    // set Limited position.
    if (dist + currentScreen > totalScreens || dist + currentScreen-1 < 0 ) {
        dist = dist + currentScreen > totalScreens ? totalScreens - currentScreen : -currentScreen + 1 ;
    }

    
    // move scroll
    this->moveToPage(currentScreen+dist);

    

}


// Register with more priority than CCMenu's but don't swallow touches
void CCScrollLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority + 1, false);
}

/** Hackish stuff - stole touches from other CCTouchDispatcher targeted delegates.
 Used to claim touch without receiving ccTouchBegan. */
void CCScrollLayer::claimTouch(CCTouch* pTouch)
{
    CCTargetedTouchHandler* handler = (CCTargetedTouchHandler*)CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(this);
    if (handler)
    {
        CCSet* claimedTouches = handler->getClaimedTouches();
        if (!claimedTouches->containsObject(pTouch))
        {
            claimedTouches->addObject(pTouch);
        }
        else
        {
            CCLOGERROR("CCScrollLayer::claimTouch is already claimed!");
        }
    }
}

void CCScrollLayer::cancelAndStoleTouch(CCTouch* pTouch, CCEvent* pEvent)
{
    // Throw Cancel message for everybody in TouchDispatcher.
    CCSet* touchSet = new CCSet();
    touchSet->addObject(pTouch);
    touchSet->autorelease();
    CCDirector::sharedDirector()->getTouchDispatcher()->touchesCancelled(touchSet, pEvent);

    
    //< after doing this touch is already removed from all targeted handlers
    
    // Squirrel away the touch
    claimTouch(pTouch);
}


#pragma mark - transform



void CCScrollLayer::moveToPage(int page, float delay /* = 0.3 */)
{
    _touchEnable = false;
	currentScreen = page;
   
    float targetPositionX = -((currentScreen-1)*scrollWidth);
    
    m_pContainer->stopActionByTag(0);
    
	CCEaseSineOut* changePage = CCEaseSineOut::create(CCMoveTo::create(delay, ccp(targetPositionX, m_pContainer->getPositionY())));
    CCAction* action = CCSequence::create(changePage,
                                          CCCallFuncND::create(this, callfuncND_selector(CCScrollLayer::setTouchActivate),(void*)true),
                                          CCCallFunc::create(this, callfunc_selector(CCScrollLayer::moveToPageEnd)),
//                                          CCDelayTime::create(0.4),
                                          NULL);
    action->setTag(0);
	m_pContainer->runAction(action);
    
}

void CCScrollLayer::moveToPageEnd()
{
    _delegate->onScrollLayerMoveEnd();
}

void CCScrollLayer::selectedPage(int pageIndex)
{
    if (currentScreen == pageIndex +1) {
//        m_bSelected = true;
        
        if (_delegate != NULL)
        {
            CCLayer* layer = (CCLayer*)m_layerArray->objectAtIndex(pageIndex);
            _delegate->onScrollLayerSelected(layer, pageIndex, m_pContainer);
        }
    }
    
    else
    {
        m_pContainer->stopActionByTag(0);
        moveToPage(pageIndex+1);
    }
    
}

void CCScrollLayer::setTransform()
{
    if (_delegate)
    {
        for (int i = 0; i < m_layerArray->count(); i++) {
            CCLayer* page = (CCLayer*)m_layerArray->objectAtIndex(i);
            float offset = m_pContainer->getPositionX() + (page->getPositionX()+page->getContentSize().width/2) - this->getContentSize().width/2;
             _delegate->onScrollLayerMoveTransform(page, offset, scrollWidth);
        }
    }
}


#pragma mark - utils

void CCScrollLayer::setTouchActivate(CCNode *sender, bool enable)
{
    _touchEnable = enable;
}

void CCScrollLayer::tick(float dt)
{
    _currentTime = _currentTime+0.1;
}

