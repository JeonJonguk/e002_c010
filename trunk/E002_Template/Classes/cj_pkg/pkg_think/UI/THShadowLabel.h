//
//  THShadowLabel.h
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 12..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef PackageApp_THShadowLabel_h
#define PackageApp_THShadowLabel_h

#include "cocos2d.h"

class CC_DLL THShadowLabel : public cocos2d::CCSprite, cocos2d::CCLabelProtocol
{
public:
	THShadowLabel();
	virtual ~THShadowLabel();
	char *description();
	
 	static THShadowLabel *labelWithString(const char *label, const cocos2d::CCSize &dimensions, cocos2d::CCTextAlignment alignment, const char *fontName, float fontSize, const cocos2d::CCSize &shadowOffset);
	static THShadowLabel *labelWithString(const char *label, const char *fontName, float fontSize);
 	static THShadowLabel *labelWithString(const char *label, const cocos2d::CCSize &dimensions, cocos2d::CCTextAlignment alignment, const char *fontName, float fontSize, const cocos2d::CCSize &shadowOffset, const cocos2d::ccColor4B &shadowColor, const cocos2d::ccColor4B &fillColor);
	static THShadowLabel *labelWithString(const char *label, const char *fontName, float fontSize, const cocos2d::ccColor4B &shadowColor, const cocos2d::ccColor4B &fillColor);
	
 	virtual bool initWithString(const char *label, const cocos2d::CCSize &dimensions, cocos2d::CCTextAlignment alignment, const char *fontName, float fontSize, const cocos2d::CCSize &shadowOffset);
	virtual bool initWithString(const char *label, const char *fontName, float fontSize);
 	virtual bool initWithString(const char *label, const cocos2d::CCSize &dimensions, cocos2d::CCTextAlignment alignment, const char *fontName, float fontSize, const cocos2d::CCSize &shadowOffset, const cocos2d::ccColor4B &shadowColor, const cocos2d::ccColor4B &fillColor);
	virtual bool initWithString(const char *label, const char *fontName, float fontSize, const cocos2d::ccColor4B &shadowColor, const cocos2d::ccColor4B &fillColor);
	
	virtual cocos2d::ccColor4B getFillColor();
	virtual void setFillColor(cocos2d::ccColor4B &color);
	virtual cocos2d::ccColor4B getShadowColor();
	virtual void setShadowColor(cocos2d::ccColor4B &color);
	
	virtual void setString(const char *label);
	virtual const char *getString();
	virtual void setOpacity(GLubyte opacity);
	virtual void setAnchorPoint(const cocos2d::CCPoint& anchor);
	
	virtual cocos2d::CCLabelProtocol *convertToLabelProtocol() { return (CCLabelProtocol *)this; }
	
protected:
	cocos2d::CCSize m_tDimensions;
	cocos2d::CCTextAlignment m_eAlignment;
	std::string * m_pFontName;
	float m_fFontSize;
	std::string * m_pString;
	cocos2d::CCSize m_tShadowOffset;
	float m_fShadowBlur;
	cocos2d::ccColor4B m_tShadowColor;
	cocos2d::ccColor4B m_tFillColor;
	cocos2d::CCLabelTTF *m_shadowLabel;
	cocos2d::CCLabelTTF *m_fillLabel;
};

#endif
