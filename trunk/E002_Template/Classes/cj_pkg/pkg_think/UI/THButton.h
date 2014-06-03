//
//  THButton.h
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 24..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef PackageApp_THButton_h
#define PackageApp_THButton_h

#include "cocos2d.h"
#include "THShadowLabel.h"

USING_NS_CC;

class THButton : public CCMenuItemImage
{
public:
	
	// Static methods for create autorelease object
	static THButton* create(
										 const char *pszNormalImage,
										 const char *pszSelectedImage);
	
	static THButton* create(
										 const char *pszNormalImage,
										 const char *pszSelectedImage,
										 const char *pszDisabledImage);
	
	static THButton* create(
										 const char *pszNormalImage,
										 const char *pszSelectedImage,
										 CCObject* pTarget,
										 SEL_MenuHandler pfnSelector);
	
	static THButton* create(
										 const char *pszNormalImage,
										 const char *pszSelectedImage,
										 const char *pszDisabledImage,
										 CCObject* pTarget,
										 SEL_MenuHandler pfnSelector);
	
	static THButton* create(
										 const char *pszNormalImage,
										 const char *pszSelectedImage,
										 const char *pszDisabledImage,
										 CCObject* pTarget,
										 SEL_MenuHandler pfnSelector,
										 const char *pszTitle,
										 const char *pszFontName,
										 float fFontSize,
										 const ccColor3B &tColor,
										 const CCSize &tShadowOffset);
	
	// Constructor, Destructor
	THButton();
	virtual ~THButton();
	
	// Initializer
	bool initFromNormalImage(
				const char *pszNormalImage,
				const char *pszSelectedImage,
				const char *pszDisabledImage,
				CCObject* pTarget,
				SEL_MenuHandler pfnSelector);
	
	bool initFromNormalImage(
				const char *pszNormalImage,
				const char *pszSelectedImage,
				const char *pszDisabledImage,
				CCObject* pTarget,
				SEL_MenuHandler pfnSelector,
				const char *pszTitle,
				const char *pszFontName,
				float fFontSize,
				const ccColor3B &tColor,
				const CCSize &tShadowOffset);
	
	// Member methods
	const char *getTitleText();
	void setTitleText(const char *pszTitle);
	
	ccColor3B getTitleColor();
	void setTtitlColor(const ccColor3B &tColor);
	
	CCSize getTitleShadowOffset();
	void setTitleShadowOffset(const CCSize &tShaodwOffset);
	
	void setIcon(const char *iconFileName);
	
	virtual void setOpacity(GLubyte opacity);
	
	
protected:
	std::string *m_sTitle;
	THShadowLabel *m_pTitleLabel;
	CCSprite *m_pIcon;
	
};

#endif
