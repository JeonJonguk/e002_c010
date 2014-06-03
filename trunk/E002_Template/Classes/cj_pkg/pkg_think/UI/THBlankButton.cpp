//
//  THBlankButton.cpp
//  Kidstory
//
//  Created by pureMini on 13. 3. 8..
//
//

#include "THBlankButton.h"


THBlankButton * THBlankButton::create(float fWidth, float fHeight, CCObject* target, SEL_MenuHandler selector)
{
	THBlankButton *pRet = new THBlankButton();
	if (pRet && pRet->initWithSize(fWidth, fHeight, target, selector))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool THBlankButton::initWithSize(float fWidth, float fHeight, CCObject* target, SEL_MenuHandler selector)
{
    CCMenuItem::initWithTarget(target, selector);
	
	m_fButtonWidth = fWidth;
	m_fButtonHeight = fHeight;
	
    this->setContentSize(CCSizeMake(fWidth, fHeight));
	
    return true;
}

void THBlankButton::draw()
{
	CCMenuItem::draw();
	
	CCPoint p[4];
	p[0] = CCPointMake(0, m_fButtonHeight);
	p[1] = CCPointMake(m_fButtonWidth, m_fButtonHeight);
	p[2] = CCPointMake(m_fButtonWidth, 0);
	p[3] = CCPointMake(0, 0);
	
	ccColor4F c = ccc4f(1.0, 0.0, 0.0, 0.2);
	
	ccDrawSolidPoly(p, 4, c);
}