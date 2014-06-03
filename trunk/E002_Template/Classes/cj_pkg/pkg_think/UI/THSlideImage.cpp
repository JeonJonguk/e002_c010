//
//  THSlideImage.cpp
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 5..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THSlideImage.h"
#include "THMaskTargetMoveTo.h"
#include "../Basic/THNodeUtil.h"
#include <stdarg.h>

using namespace cocos2d;

enum
{
	kZIndexBaseImage,
	kZIndexMaskedImage,
	kZIndexExtensionEffectImage,
	kZIndexEffectImage,
	kZIndexIndexes,
};

THSlideImage::THSlideImage()
{
//	CCLog("THSlideImage construct");
}

THSlideImage::~THSlideImage()
{
//	CCLog("THSlideImage destruct");
//	this->removeAllChildrenWithCleanup(true);
	THNodeUtil::removeAllChildren(this);
	
	m_contentImageContainer->release();
	m_indexContainer->release();
	m_mask->release();
	m_maskImage->release();
}

bool THSlideImage::init()
{
	return this->initWithEnvImages(NULL, NULL, NULL);
}

bool THSlideImage::initWithEnvImages(const char *pszBaseImage, const char *pszMaskImage, const char *pszEffectImage, float indexMargin, int touchPriority)
{
	if(!CCLayer::init())
	{
		return false;
	}
	
	// Initialize
	m_lastImagePositionX = 0;
	m_indexMarginX = indexMargin;
	m_currentSlideIndex = -1;
	m_slideCount = 0;
	m_imageY = 0;
	m_hitArea = CCRectZero;
	m_limitMinX = 0;
	m_limitMaxX = 0;
	
	m_imageContainerSize = CCSizeZero;
	
	if(pszBaseImage != NULL)
	{
		CCSprite *baseImage = CCSprite::create(pszBaseImage);
		this->addChild(baseImage, kZIndexBaseImage);
	}
	
	if(pszMaskImage != NULL)
	{
		m_maskImage = new CCSprite();
		m_maskImage->initWithFile(pszMaskImage);
		m_hitArea.size = m_maskImage->getContentSize();
		m_imageContainerSize.height = m_hitArea.size.height;
		m_imageY = m_imageContainerSize.height / 2;
		
//		CCLayerColor *area = CCLayerColor::layerWithColorWidthHeight(ccc4f(255, 0, 0, 127), m_hitArea.size.width, m_hitArea.size.height);
//		CCPoint p = m_hitArea.origin;
//		p.x -= m_hitArea.size.width / 2;
//		p.y -= m_hitArea.size.height / 2;
//		area->setPosition(p);
//		this->addChild(area, 100);
	}
	
	if(pszEffectImage != NULL)
	{
		CCSprite *effectImage = CCSprite::create(pszEffectImage);
		this->addChild(effectImage, kZIndexEffectImage);
	}
	
	m_contentImageContainer = new CCSprite();
	m_contentImageContainer->init();
	m_contentImageContainer->setAnchorPoint(CCPointZero);
	
	m_indexContainer = new CCLayer();
	m_indexContainer->init();
	
	m_mask = new THMask();
	m_mask->init();
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, touchPriority, true);
	
	
	return true;
}

bool THSlideImage::initWithEnvImages(const char *pszBaseImage, const char *pszMaskImage, const char *pszEffect1Image, const char *pszEffect2Image, float indexMargin, int touchPriority)
{
	if(this->initWithEnvImages(pszBaseImage, pszMaskImage, pszEffect1Image, indexMargin, touchPriority))
	{
		if(pszEffect2Image)
		{
			CCSprite *effectImage = CCSprite::create(pszEffect2Image);
			this->addChild(effectImage, kZIndexExtensionEffectImage);
		}
		
	}
	   
	return false;
}

void THSlideImage::addContentImage(const char *pszContentImage, const char *pszIndexDefaultImage, const char *pszIndexSelectedImage)
{
//	CCLog("====================");
//	CCLog("===== %s", pszContentImage);
//	CCLog("===== %s", pszIndexDefaultImage);
//	CCLog("===== %s", pszIndexSelectedImage);
	m_currentSlideIndex = -1;
	CCSprite *image = CCSprite::create(pszContentImage);
	image->setAnchorPoint(CCPointZero);
	image->getTexture()->setAliasTexParameters();
	
	float w = image->getContentSize().width + 1;
	float hw = w / 2;
	
	m_imageContainerSize.width += w;
	
	if(m_slideCount)
	{
		m_lastImagePositionX += w;
	}
	
	CCPoint p = CCPointMake(m_lastImagePositionX, 0);
	CCPoint dp = CCPointMake(m_slideCount * m_indexMarginX, 0);
	
	m_imageX.push_back(m_lastImagePositionX);
	image->setPosition(p);
	m_limitMinX = -p.x;
	m_contentImageContainer->addChild(image);
	
//	m_lastImagePositionX += hw;
	m_imageHoldX.push_back(m_lastImagePositionX + hw);
	
	CCSprite *indexDefaultImage = CCSprite::create(pszIndexDefaultImage);
	indexDefaultImage->getTexture()->setAliasTexParameters();
	indexDefaultImage->setPosition(dp);
	m_indexContainer->addChild(indexDefaultImage);
	
	CCSprite *indexSelectedImage = CCSprite::create(pszIndexSelectedImage);
	indexDefaultImage->getTexture()->setAliasTexParameters();
	indexSelectedImage->setTag(m_slideCount);
	indexSelectedImage->setPosition(dp);
	if(m_slideCount)
	{
		indexSelectedImage->setScale(0);
	}
	m_indexContainer->addChild(indexSelectedImage);
	m_indexContainer->setPosition(CCPointMake(-dp.x / 2, - m_imageY - m_indexMarginX));
	
	//	m_mask->refresh();
//	if(!m_slideCount)
//	{
//		m_contentImageContainer->setPosition(CCPointMake(-w, 0));
//		m_mask->setTargetPosition(CCPointMake(-0, 0));
//		this->addChild(m_mask, kZIndexMaskedImage);
//		this->addChild(m_contentImageContainer);
//		this->addChild(m_indexContainer);
//	}
//	m_mask->refresh();
	
	m_slideCount++;
}

void THSlideImage::setSlide(int index, bool withAnimation)
{
	if(index >= 0 && index < m_slideCount)
	{
		if(m_currentSlideIndex < 0)
		{
//			CCLog("+++++ %f x %f", m_imageContainerSize.width, m_imageContainerSize.height);
			CCRenderTexture *texture = CCRenderTexture::create(m_imageContainerSize.width, m_imageContainerSize.height);
			
			texture->begin();
			m_contentImageContainer->visit();
			texture->end();
			
//			CCSprite *capture = texture->getSprite();
			
			m_mask->setMask(m_maskImage);
			m_mask->setTarget(texture->getSprite());
			m_mask->setTargetPosition(CCPointMake(m_imageX[1], 0));
			
			this->addChild(m_mask, kZIndexMaskedImage);
			this->addChild(m_indexContainer, kZIndexIndexes);
		}
		else if(index != m_currentSlideIndex)
		{
			CCNode *beforeDot = m_indexContainer->getChildByTag(m_currentSlideIndex);
			if(beforeDot)
			{
				beforeDot->stopAllActions();
				beforeDot->runAction(CCEaseSineInOut::create(CCScaleTo::create(0.3, 0)));
			}
			
			CCNode *currentDot = m_indexContainer->getChildByTag(index);
			if(currentDot)
			{
				currentDot->stopAllActions();
				currentDot->runAction(CCEaseSineInOut::create(CCScaleTo::create(0.3, 1)));
			}
		}
		
		m_currentSlideIndex = index;
		
		CCPoint top = m_mask->getTargetPosition();// m_contentImageContainer->getPosition();
		top.x = m_limitMaxX - m_imageX[m_currentSlideIndex];
		m_mask->stopAllActions();
		if(withAnimation)
		{
			m_mask->runAction(CCEaseSineOut::create(THMaskTargetMoveTo::create(0.25, top)));
		}
		else
		{
			m_mask->setTargetPosition(top);
		}
//		m_contentImageContainer->runAction(CCEaseSineInOut::actionWithAction(CCMoveTo::actionWithDuration(0.25, top)));
	}
}

//void THSlideImage::onEnter()
//{
//	if(m_imageX.size())
//	{
//		m_contentImageContainer->runAction(CCSequence::actions(
////															   CCDelayTime::actionWithDuration(0.2),
//															   CCEaseSineInOut::actionWithAction(CCMoveTo::actionWithDuration(0.3, CCPointZero)),
//															   NULL));
//	}
//}

void THSlideImage::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

int THSlideImage::getImageHoldIndex(float x)
{
	if(m_slideCount < 1)
	{
		return -1;
	}
	
	if(x < m_limitMinX)
	{
		return m_slideCount - 1;
	}
	
	if(x > m_limitMaxX)
	{
		return 0;
	}
	
	for(int i = 0; i < m_slideCount; i++)
	{
		if(x > (m_limitMaxX - m_imageHoldX[i]))
		{
			return i;
		}
	}
	
	return -1;
}

bool THSlideImage::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint p = m_mask->convertTouchToNodeSpace(pTouch);
	
	if(m_hitArea.containsPoint(p))
	{
//		CCLog("THSlideImage in touch");
		
		m_mask->stopAllActions();
		m_distanceX = m_mask->getTargetPosition().x - p.x;
		m_beforeX = m_nowX = p.x;
		
		return true;
	}
	
//	CCLog("THSlideImage out of touch");
	return false;
}

void THSlideImage::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint p = m_mask->convertTouchToNodeSpace(pTouch);
	
	if(m_hitArea.containsPoint(p))
	{
		m_beforeX = m_nowX;
		m_nowX = p.x;
		CCPoint top = m_mask->getTargetPosition();
		top.x = MAX(m_limitMinX, MIN(p.x + m_distanceX, m_limitMaxX));
		
		m_mask->setTargetPosition(top);
	}
}

void THSlideImage::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	int i = m_currentSlideIndex;

	double distanceBefore = m_beforeX - m_nowX;
	if(fabs(distanceBefore) > 10)
	{
		if(distanceBefore > 0)
		{
			if(m_currentSlideIndex + 1 < m_slideCount)
			{
				i = m_currentSlideIndex + 1;
			}
		}
		else
		{
			if(m_currentSlideIndex > 0)
			{
				i = m_currentSlideIndex - 1;
			}
		}
	}
	else
	{
		int holdIndex = this->getImageHoldIndex(m_mask->getTargetPosition().x);
		if(0 <= holdIndex && holdIndex < m_slideCount)
		{
			i = holdIndex;
		}
	}
	this->setSlide(i);
}

void THSlideImage::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	this->ccTouchEnded(pTouch, pEvent);
}
