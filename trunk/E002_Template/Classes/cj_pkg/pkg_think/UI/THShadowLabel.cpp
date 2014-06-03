//
//  THShadowLabel.cpp
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 12..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THShadowLabel.h"
#include "../Basic/THNodeUtil.h"

using namespace cocos2d;

THShadowLabel::THShadowLabel()
:m_eAlignment(kCCTextAlignmentCenter)
,m_pFontName(NULL)
,m_fFontSize(0.0)
,m_pString(NULL)
,m_fillLabel(NULL)
,m_shadowLabel(NULL)
{
}

THShadowLabel::~THShadowLabel()
{
	if(m_pString)
	{
		delete m_pString;
		m_pString = NULL;
	}
//	this->removeAllChildrenWithCleanup(true);
	THNodeUtil::removeAllChildren(this);
	delete m_pFontName;
}

THShadowLabel *THShadowLabel::labelWithString(const char *label, const CCSize &dimensions, CCTextAlignment alignment, const char *fontName, float fontSize, const CCSize &shadowOffset)
{
	THShadowLabel *pRet = new THShadowLabel();
	if(pRet && pRet->initWithString(label, dimensions, alignment, fontName, fontSize, shadowOffset))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

THShadowLabel *THShadowLabel::labelWithString(const char *label, const char *fontName, float fontSize)
{
	THShadowLabel *pRet = new THShadowLabel();
	if(pRet && pRet->initWithString(label, fontName, fontSize))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

THShadowLabel *THShadowLabel::labelWithString(const char *label, const CCSize &dimensions, CCTextAlignment alignment, const char *fontName, float fontSize, const CCSize &shadowOffset, const ccColor4B &shadowColor, const ccColor4B &fillColor)
{
	THShadowLabel *pRet = new THShadowLabel();
	if(pRet && pRet->initWithString(label, dimensions, alignment, fontName, fontSize, shadowOffset, shadowColor, fillColor))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

THShadowLabel *THShadowLabel::labelWithString(const char *label, const char *fontName, float fontSize, const ccColor4B &shadowColor, const ccColor4B &fillColor)
{
	THShadowLabel *pRet = new THShadowLabel();
	if(pRet && pRet->initWithString(label, fontName, fontSize, shadowColor, fillColor))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool THShadowLabel::initWithString(const char *label, const CCSize &dimensions, CCTextAlignment alignment, const char *fontName, float fontSize, const CCSize &shadowOffset)
{
	if(!this->initWithString(label, dimensions, alignment, fontName, fontSize, shadowOffset, ccc4(0, 0, 0, 255), ccc4(255, 255, 255, 255)))
	{
		return false;
	}
	
	return true;
}

bool THShadowLabel::initWithString(const char *label, const char *fontName, float fontSize)
{
	if(!this->initWithString(label, CCSizeMake(0, 0), kCCTextAlignmentCenter, fontName, fontSize, CCSizeMake(1, 1)))
	{
		return false;
	}
	
	return true;
}

bool THShadowLabel::initWithString(const char *label, const CCSize &dimensions, CCTextAlignment alignment, const char *fontName, float fontSize, const CCSize &shadowOffset, const ccColor4B &shadowColor, const ccColor4B &fillColor)
{
	if(!CCSprite::init())
	{
		return false;
	}
	
	m_tDimensions = CCSizeMake(dimensions.width * CC_CONTENT_SCALE_FACTOR(), dimensions.height * CC_CONTENT_SCALE_FACTOR());
	m_eAlignment = alignment;
	
	if(m_pFontName)
	{
		delete m_pFontName;
		m_pFontName = NULL;
	}
	m_pFontName = new std::string(fontName);
	
	m_fFontSize = fontSize * CC_CONTENT_SCALE_FACTOR();
	
	m_tShadowOffset = CCSizeMake(shadowOffset.width * CC_CONTENT_SCALE_FACTOR(), shadowOffset.height * CC_CONTENT_SCALE_FACTOR());
	m_tShadowColor = shadowColor;
	m_tFillColor = fillColor;
	
	if(m_shadowLabel)
	{
		delete m_shadowLabel;
		m_shadowLabel = NULL;
	}
	m_shadowLabel = CCLabelTTF::create(label, fontName, fontSize, dimensions, alignment);
//	m_shadowLabel->getTexture()->setAliasTexParameters();
//	m_shadowLabel->setAnchorPoint(CCPointZero);
//	m_shadowLabel->setPosition(CCPointZero);
	m_shadowLabel->setPosition(CCPointMake(-floorf(dimensions.width / 2 - m_tShadowOffset.width), -floorf(dimensions.height / 2 + m_tShadowOffset.height)));
	this->addChild(m_shadowLabel);
	
	if(m_fillLabel)
	{
		delete m_fillLabel;
		m_fillLabel = NULL;
	}
	m_fillLabel = CCLabelTTF::create(label, fontName, fontSize, dimensions, alignment);
//	m_fillLabel->getTexture()->setAliasTexParameters();
//	m_fillLabel->setAnchorPoint(CCPointZero);
//	m_fillLabel->setPosition(CCPointMake(-floorf(dimensions.width / 2), -floorf(dimensions.height / 2)));
	this->addChild(m_fillLabel);
	
	this->setString(label);
	
	return true;
}

bool THShadowLabel::initWithString(const char *label, const char *fontName, float fontSize, const ccColor4B &shadowColor, const ccColor4B &fillColor)
{
	if(!this->initWithString(label, CCSizeMake(0, 0), kCCTextAlignmentCenter, fontName, fontSize, CCSizeMake(1, 1), shadowColor, fillColor))
	{
		return false;
	}
	
	return true;
}

ccColor4B THShadowLabel::getFillColor()
{
	return m_tFillColor;
}

void THShadowLabel::setFillColor(ccColor4B &color)
{
	m_tFillColor = color;
	this->setString(m_fillLabel->getString());
}

ccColor4B THShadowLabel::getShadowColor()
{
	return m_tShadowColor;
}

void THShadowLabel::setShadowColor(ccColor4B &color)
{
	m_tShadowColor = color;
	this->setString(m_shadowLabel->getString());
}

void THShadowLabel::setString(const char *label)
{
	if(m_pString)
	{
		delete m_pString;
		m_pString = NULL;
	}
	m_pString = new std::string(label);
	
	if(m_shadowLabel)
	{
		m_shadowLabel->setPosition(CCPointMake(floorf(m_tShadowOffset.width), floorf(m_tShadowOffset.height)));
		m_shadowLabel->setColor(ccc3(m_tShadowColor.r, m_tShadowColor.g, m_tShadowColor.b));
        
        /*
         * cocos2dx v2.1.4 change inherit struct, CC_PROPERTY variable removed.
         * m_nOpacity in CCSprite class -> _displayedOpacity in CCNodeRGBA(CCNode) class.
         *
         * m_shadowLabel->setOpacity(m_tShadowColor.a * m_nOpacity / 255.0f);
         */
        m_shadowLabel->setOpacity(m_tShadowColor.a * _displayedOpacity / 255.0f);
		m_shadowLabel->setString(label);
		m_shadowLabel->getTexture()->setAliasTexParameters();
	}
	
	if(m_fillLabel)
	{
        
		m_fillLabel->setColor(ccc3(m_tFillColor.r, m_tFillColor.g, m_tFillColor.b));
        
        /*
         * cocos2dx v2.1.4 change inherit struct, CC_PROPERTY variable removed.
         * m_nOpacity in CCSprite class -> _displayedOpacity in CCNodeRGBA(CCNode) class.
         *
         * m_fillLabel->setOpacity(m_tFillColor.a * m_nOpacity / 255.0f);
         */
		m_fillLabel->setOpacity(m_tFillColor.a * _displayedOpacity / 255.0f);
		m_fillLabel->setString(label);
		m_fillLabel->getTexture()->setAliasTexParameters();
	}
}

void THShadowLabel::setOpacity(GLubyte opacity)
{
	if(m_shadowLabel)
	{
		m_shadowLabel->setOpacity(m_tShadowColor.a * opacity / 255.0f);
	}
	if(m_fillLabel)
	{
		m_fillLabel->setOpacity(m_tFillColor.a * opacity / 255.0f);
	}
}

void THShadowLabel::setAnchorPoint(const cocos2d::CCPoint &anchor)
{
	CCSprite::setAnchorPoint(anchor);
	if(m_shadowLabel)
	{
		m_shadowLabel->setAnchorPoint(anchor);
	}
	if(m_fillLabel)
	{
		m_fillLabel->setAnchorPoint(anchor);
	}
}

const char *THShadowLabel::getString(void)
{
	return m_pString->c_str();
}

char *THShadowLabel::description()
{
	char *ret = new char[100];
//	sprintf(ret, "<THShadowLabel | FontName = %s, FontSizee = %.1f>", m_pFontName->c_str(), m_fFontSize);
	return ret;
}
