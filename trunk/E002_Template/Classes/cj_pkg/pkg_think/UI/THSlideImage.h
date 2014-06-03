//
//  THSlideImage.h
//  PackageApp
//
//  Created by pureye4u BX on 12. 7. 5..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef PackageApp_THSlideImage_h
#define PackageApp_THSlideImage_h

#include "cocos2d.h"
#include "THMask.h"

class THSlideImage : public cocos2d::CCLayer
{
public:
	THSlideImage();
	~THSlideImage();
	
	virtual bool init();
	virtual bool initWithEnvImages(const char *pszBaseImage, const char *pszMaskImage, const char *pszEffectImage, float indexMargin = 15, int touchPriority = -1);
	virtual bool initWithEnvImages(const char *pszBaseImage, const char *pszMaskImage, const char *pszEffect1Image, const char *pszEffect2Image, float indexMargin = 15, int touchPriority = -1);
	virtual void addContentImage(const char *pszContentImage, const char *pszIndexDefaultImage, const char *pszIndexSelectedImage);
	virtual void setSlide(int index, bool withAnimation = true);
	
//	virtual void onEnter();
	virtual void onExit();
	
protected:
	int m_currentSlideIndex;
	int m_slideCount;
	float m_lastImagePositionX;
	float m_indexMarginX;
	float m_imageY;
	std::vector<float> m_imageX;
	std::vector<float> m_imageHoldX;
	cocos2d::CCSprite *m_maskImage;
	cocos2d::CCSprite *m_contentImageContainer;
	cocos2d::CCLayer *m_indexContainer;
	cocos2d::CCSize m_imageContainerSize;
	cocos2d::CCRect m_hitArea;
	THMask *m_mask;
	
	float m_distanceX;
	float m_beforeX;
	float m_nowX;
	float m_limitMinX;
	float m_limitMaxX;
	
	virtual int getImageHoldIndex(float x);
	
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
};

#endif
