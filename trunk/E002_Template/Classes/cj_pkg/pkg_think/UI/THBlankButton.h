//
//  THBlankButton.h
//  Kidstory
//
//  Created by pureMini on 13. 3. 8..
//
//

#ifndef __Kidstory__THBlankButton__
#define __Kidstory__THBlankButton__

#include "cocos2d.h"

USING_NS_CC;

class THBlankButton : public CCMenuItem
{
public:
	
	static THBlankButton* create(float fWidth, float fHeight, CCObject* target, SEL_MenuHandler selector);
	
	// Constructor, Destructor
//	THBlankButton();
//	virtual ~THBlankButton();
	
	// Initializer
	bool initWithSize(float fWidth, float fHeight, CCObject* target, SEL_MenuHandler selector);
	
    virtual void draw();
	
protected:
	
	float m_fButtonWidth;
	float m_fButtonHeight;
};

#endif /* defined(__Kidstory__THBlankButton__) */
