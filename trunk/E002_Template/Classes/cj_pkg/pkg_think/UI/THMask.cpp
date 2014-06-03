//
//  THMask.cpp
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 5..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THMask.h"

using namespace cocos2d;

THMask::THMask()
{
	
}

THMask::~THMask()
{
	//	CCLog("~THMask");
	
	m_mask->release();
	m_target->release();
}

bool THMask::init()
{
	if(!CCSprite::init())
	{
		return false;
	}
	
	m_mask = NULL;
	m_target = NULL;
	m_maskSize = CCSizeZero;
	m_targetSize = CCSizeZero;
	m_targetPosition = CCPointZero;
	
	return true;
}

CCSprite *THMask::getMask()
{
	return m_mask;
}

void THMask::setMask(CCSprite *mask)
{
	m_mask = mask;
	m_mask->retain();
	m_maskSize = m_mask->getContentSize();
	m_mask->setBlendFunc((ccBlendFunc){GL_ONE, GL_ZERO});
	
	this->updateMask();
}

CCSprite *THMask::getTarget()
{
	return m_target;
}

void THMask::setTarget(CCSprite *target)
{
	m_target = target;
	m_target->retain();
	m_targetSize = target->getContentSize();
	m_target->setBlendFunc((ccBlendFunc){GL_DST_ALPHA, GL_ZERO});
	
	this->updateMask();
}

CCPoint THMask::getTargetPosition()
{
	return m_targetPosition;
}

void THMask::setTargetPosition(CCPoint position)
{
	m_targetPosition = position;
	
	this->updateMask();
}

void THMask::refresh()
{
	this->updateMask();
}

void THMask::updateMask()
{
	if(m_mask == NULL || m_target == NULL)
	{
		return;
	}
	
	CCSize size = m_mask->getContentSize();// getContentSizeInPixels();
	CCRenderTexture *rt = CCRenderTexture::create(size.width, size.height);
	rt->retain();
	
	m_mask->setPosition(CCPointMake(m_maskSize.width / 2.0f, m_maskSize.height / 2.0f));
	m_target->setPosition(CCPointMake(m_targetSize.width / 2.0f + m_targetPosition.x, m_targetSize.height / 2.0f + m_targetPosition.y));
	
	rt->begin();
	m_mask->visit();
	m_target->visit();
	rt->end();
	rt->release();
	
	CCRect rect = CCRectZero;
	rect.size = m_mask->getContentSize();
	this->setTexture(rt->getSprite()->getTexture());
	this->setTextureRect(rect);
	this->setFlipY(true);
}
