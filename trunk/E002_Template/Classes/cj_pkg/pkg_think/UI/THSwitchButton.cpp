//
//  THSwitchButton.cpp
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 10..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THSwitchButton.h"
#include "THMaskTargetMoveTo.h"

using namespace cocos2d;

THSwitchButton::THSwitchButton()
{
	//CCLog("THSwitchButton constrected");
	
	m_hitArea = CCRectZero;
}

THSwitchButton::~THSwitchButton()
{
	//CCLog("THSwitchButton destrected");
	
	this->removeAllChildrenWithCleanup(true);
}

bool THSwitchButton::init(const char *pszSwitchImage, const char *pszThumbImage, int iTouchPriority)
{
	CCSprite *switchImage = CCSprite::create(pszSwitchImage);
	m_hitArea.size = switchImage->getContentSize();
	m_hitArea.origin.x = - m_hitArea.size.width / 2;
	m_hitArea.origin.y = - m_hitArea.size.height / 2;
	
	if(!CCLayerColor::create(ccc4(0, 0, 0, 0), m_hitArea.size.width, m_hitArea.size.height))
	{
		return false;
	}
	
	// Initialize
	m_isOn = false;
	m_isScrolling = false;
	m_returnToMin = false;
	m_returnToMax = false;
	m_direction = 0;
	m_limitMinX = 0;
	m_limitMaxX = 0;
	m_delegate = NULL;
	m_scrollDistance = CCPointZero;
	CCPoint p = CCPointZero;
	
	this->addChild(switchImage);
	
	m_thumb = new CCSprite();
	m_thumb->initWithFile(pszThumbImage);
	
	
	float margin = m_hitArea.size.width - m_thumb->getContentSize().width;
	m_limitMinX = MIN(0, -margin / 2);
	m_limitMaxX = MAX(0, margin / 2);
	p.x = m_limitMinX;
	
	m_thumb->setPosition(p);
	this->addChild(m_thumb);
	
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, iTouchPriority, true);
	
	
	return true;
}

bool THSwitchButton::getValue()
{
	return m_isOn;
}

void THSwitchButton::setValue(bool isOn, bool withAnimation)
{
	if(m_isOn != isOn)
	{
		m_isOn = isOn;
		if(m_delegate)
		{
			m_delegate->switchValueChanged(this);
		}
	}
	
	if(m_isOn)
	{
		this->setToOn();
	}
	else
	{
		this->setToOff();
	}
}

void THSwitchButton::setDelegate(THSwitchButtonDelegate *delegate)
{
	m_delegate = delegate;
}

void THSwitchButton::setToOn()
{
	CCPoint p = CCPointZero;
	p.x = m_limitMaxX;
	m_thumb->runAction(CCEaseSineOut::create(CCMoveTo::create(0.1, p)));
}

void THSwitchButton::setToOff()
{
	CCPoint p = CCPointZero;
	p.x = m_limitMinX;
	m_thumb->runAction(CCEaseSineOut::create(CCMoveTo::create(0.1, p)));
}

void THSwitchButton::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool THSwitchButton::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint p = this->convertTouchToNodeSpace(pTouch);
	
	if(m_hitArea.containsPoint(p))
	{
		m_isScrolling = true;
		m_returnToMin = false;
		m_returnToMax = false;
		m_direction = 0;
		m_scrollDistance.x = m_thumb->getPosition().x - p.x;
		
		return true;
	}
	
	return false;
}

void THSwitchButton::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint p = this->convertTouchToNodeSpace(pTouch);
	
	if(m_isScrolling)
	{
		CCPoint currentPosition = m_thumb->getPosition();
		CCPoint top = CCPointMake(p.x + m_scrollDistance.x, currentPosition.y);
		m_direction = top.x - currentPosition.x;
		
		if(top.x < m_limitMinX)
		{
			top.x = m_limitMinX;
		}
		else if(top.x > m_limitMaxX)
		{
			top.x = m_limitMaxX;
		}
		else
		{
			m_returnToMin = false;
			m_returnToMax = false;
		}
		
		m_thumb->setPosition(top);
	}
}

void THSwitchButton::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(m_returnToMin || m_direction < 0)
	{
		this->setValue(false, true);
		m_returnToMin = false;
		m_direction = 0;
	}
	else if(m_returnToMax || m_direction > 0)
	{
		this->setValue(true, true);
		m_returnToMax = false;
		m_direction = 0;
	}
	else
	{
		if(m_isOn)
		{
			this->setValue(false, true);
		}
		else
		{
			this->setValue(true, true);
		}
	}
}

void THSwitchButton::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	this->ccTouchEnded(pTouch, pEvent);
}

