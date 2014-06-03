//
//  THButton.cpp
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 24..
//  Copyright CJ Educations 2012. All rights reserved.
//

#include "THButton.h"

THButton * THButton::create(
										 const char *pszNormalImage,
										 const char *pszSelectedImage)
{
	return THButton::create(
										 pszNormalImage,
										 pszSelectedImage,
										 NULL,
										 NULL,
										 NULL);
}

THButton * THButton::create(
										 const char *pszNormalImage,
										 const char *pszSelectedImage,
										 CCObject* pTarget,
										 SEL_MenuHandler pfnSelector)
{
	return THButton::create(
										 pszNormalImage,
										 pszSelectedImage,
										 NULL,
										 pTarget,
										 pfnSelector);
}

THButton * THButton::create(
										 const char *pszNormalImage,
										 const char *pszSelectedImage,
										 const char *pszDisabledImage,
										 CCObject* pTarget,
										 SEL_MenuHandler pfnSelector)
{
	THButton *pRet = new THButton();
	if (pRet && pRet->initFromNormalImage(
							 pszNormalImage,
							 pszSelectedImage,
							 pszDisabledImage,
							 pTarget,
							 pfnSelector))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

THButton * THButton::create(
										 const char *pszNormalImage,
										 const char *pszSelectedImage,
										 const char *pszDisabledImage)
{
	THButton *pRet = new THButton();
	if (pRet && pRet->initFromNormalImage(
							 pszNormalImage,
							 pszSelectedImage,
							 pszDisabledImage,
							 NULL,
							 NULL))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

THButton *THButton::create(
										const char *pszNormalImage,
										const char *pszSelectedImage,
										const char *pszDisabledImage,
										CCObject *pTarget,
										SEL_MenuHandler pfnSelector,
										const char *pszTitle,
										const char *pszFontName,
										float fFontSize,
										const ccColor3B &tColor,
										const CCSize &tShadowOffset)
{
	THButton *pRet = new THButton();
	if(pRet && pRet->initFromNormalImage(
							pszNormalImage,
							pszSelectedImage,
							pszDisabledImage,
							pTarget,
							pfnSelector,
							pszTitle,
							pszFontName,
							fFontSize,
							tColor,
							tShadowOffset))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

enum
{
	kZIndexIcon,
	kZIndexLabel,
};

const char *DEFAULT_FONT_NAME = "Helvetica-Bold";
const float DEFAULT_FONT_SIZE = 18.0f;
const ccColor3B DEFAULT_FONT_COLOR = ccc3(255, 255, 255);
const ccColor4B DEFAULT_FONT_SHADOW_COLOR = ccc4(1, 1, 1, 90);
const CCSize DEFAULT_FONT_SHADOW_OFFSET = CCSizeMake(0, 1);

THButton::THButton()
{
	m_sTitle = NULL;
	m_pIcon = NULL;
	m_pTitleLabel = NULL;
}

THButton::~THButton()
{
//	m_pTitleLabel->release();
	this->removeAllChildrenWithCleanup(true);
	delete m_sTitle;
	m_sTitle = NULL;
}

bool THButton::initFromNormalImage(
					  const char *pszNormalImage,
					  const char *pszSelectedImage,
					  const char *pszDisabledImage,
					  CCObject* pTarget,
					  SEL_MenuHandler pfnSelector)
{
	return this->initFromNormalImage(
						pszNormalImage,
						pszSelectedImage,
						pszDisabledImage,
						pTarget,
						pfnSelector,
						"",
						DEFAULT_FONT_NAME,
						DEFAULT_FONT_SIZE,
						DEFAULT_FONT_COLOR,
						DEFAULT_FONT_SHADOW_OFFSET);
}

bool THButton::initFromNormalImage(
					  const char *pszNormalImage,
					  const char *pszSelectedImage,
					  const char *pszDisabledImage,
					  CCObject *pTarget,
					  SEL_MenuHandler pfnSelector,
					  const char *pszTitle,
					  const char *pszFontName,
					  float fFontSize,
					  const ccColor3B &tColor,
					  const CCSize &tShadowOffset)
{
	if(!CCMenuItemImage::initWithNormalImage(
								pszNormalImage,
								pszSelectedImage,
								pszDisabledImage,
								pTarget,
								pfnSelector))
	{
		return false;
	}
	
	// Initialize
	m_pTitleLabel = new THShadowLabel();
	m_pTitleLabel->initWithString(
								  pszTitle,
								  CCSizeMake(m_obContentSize.width, fFontSize),
								  kCCTextAlignmentCenter,
								  pszFontName,
								  fFontSize,
								  tShadowOffset,
								  DEFAULT_FONT_SHADOW_COLOR,
								  ccc4(tColor.r, tColor.g, tColor.b, 255));
	CCPoint p = CCPointMake(0, (m_obContentSize.height - fFontSize) / 2);
	m_pTitleLabel->setAnchorPoint(CCPointZero);
	m_pTitleLabel->setPosition(p);
	this->addChild(m_pTitleLabel, kZIndexLabel);
	m_pTitleLabel->release();
	
	return true;
}

const char *THButton::getTitleText()
{
	if(m_sTitle)
	{
		return m_sTitle->c_str();
	}
	
	return "";
}

void THButton::setTitleText(const char *pszTitle)
{
	if(m_sTitle)
	{
		delete m_sTitle;
		m_sTitle = NULL;
	}
	m_sTitle = new std::string(pszTitle);
	m_pTitleLabel->setString(m_sTitle->c_str());
}

ccColor3B THButton::getTitleColor()
{
	return m_pTitleLabel->getColor();
}

void THButton::setTtitlColor(const ccColor3B &tColor)
{
	m_pTitleLabel->setColor(tColor);
}


void THButton::setIcon(const char *pszIconFileName)
{
	if(m_pIcon)
	{
		if(m_pIcon->getParent())
		{
			m_pIcon->removeFromParentAndCleanup(true);
		}
		
		m_pIcon = NULL;
	}
	
	if(pszIconFileName != NULL && strcmp(pszIconFileName, "") != 0)
	{
		m_pIcon = new CCSprite();
		m_pIcon->initWithFile(pszIconFileName);
		if(m_pIcon)
		{
			m_pIcon->getTexture()->setAliasTexParameters();
			CCPoint p = CCPointMake(m_obContentSize.width, m_obContentSize.height / 2);
			p.x -= m_pIcon->getContentSize().width / 2.0f;
			m_pIcon->setPosition(p);
			this->addChild(m_pIcon, kZIndexIcon);
			m_pIcon->release();
		}
	}
}

void THButton::setOpacity(GLubyte cOpacity)
{
	CCMenuItemImage::setOpacity(cOpacity);
	
	if(m_pTitleLabel)
	{
		m_pTitleLabel->setOpacity(cOpacity);
	}
	if(m_pIcon)
	{
		m_pIcon->setOpacity(cOpacity);
	}
}
