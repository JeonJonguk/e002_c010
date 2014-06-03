//  CCScrollLayer.h
//  Museum
//
//  Created by GParvaneh on 29/12/2010.
//  Copyright 2010 All rights reserved.
//  Ported to C++ by Lior Tamam on 03/04/2011
//  Cleaned for Cocos2d-x V2.x by @HermanJakobi (01/12/12)
#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class CCScrollLayerDelegate
{
public:
    virtual void onScrollLayerMoveTransform(CCLayer* page, float offset, float scrollWidth);
    virtual void onScrollLayerSelected(CCLayer* page, int pageIndex, CCNode* container);
    virtual void onScrollLayerMoveCancel();
    
    virtual void onScrollLayerTouchMove(CCTouch* touch);
    virtual void onScrollLayerTouchBegan(CCTouch* touch);
    virtual void onScrollLayerMoveEnd();
};



class CCScrollLayer : public cocos2d::CCLayerColor
{
    
public:

    float                   beginTime;
    float                   endTime;
    
    
    int                     m_iState;
    float                   m_fMinimumTouchLengthToSlide;
    

    bool                    m_bSelected;
    
    CCLayer*                m_pContainer;
    CCArray*                m_layerArray;
    
private:
    // Holds the current height and width of the screen
    CCScrollLayerDelegate   *_delegate;
    bool                    _touchEnable;
    
	int scrollHeight;
	int scrollWidth;
	
	// Holds the height and width of the screen when the class was inited
	int startHeight;
	int startWidth;
	
	// Holds the current page being displayed
	int currentScreen;
	
	// A count of the total screens available
	int totalScreens;
	
	// The initial point the user starts their swipe
	float startSwipe;
    
    float _currentTime;
    
public:
    
    CCScrollLayer();
    ~CCScrollLayer();
    
	static CCScrollLayer* create(cocos2d::CCArray* layers, int widthOffset, int startIndex = 0);
	
    bool init(cocos2d::CCArray *layers,int widthOffset ,int startIndex);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
//    virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void onEnter();
	virtual void onExit();
    
    void setDelegate(CCScrollLayerDelegate* pDelegate);
    
    void registerWithTouchDispatcher();
    void claimTouch(cocos2d::CCTouch* pTouch);
    void cancelAndStoleTouch(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    
    void setTransform();
	void moveToPage(int page, float delay = 0.3);
    void selectedPage(int pageIndex);
    void moveToPageEnd();
    
    void tick(float dt);
    void setTouchActivate(CCNode *sender, bool enable);
    
    //get
    int getTotalScreens(){return totalScreens;}
    int getCurrentScreen(){return currentScreen;}
    
  
};