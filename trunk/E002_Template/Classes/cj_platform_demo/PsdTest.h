

#pragma once

#include "cocos2d.h" 
#include "SimpleAudioEngine.h"

#include "CJAnimationManager.h"

namespace PsdTestTag
{
    enum {
        TagBG = 100,
        
    };
}

USING_NS_CC;     
using namespace CocosDenshion;

class PsdTest : public CCLayer, CJAnimationManager
{
public:
    
    CCDictionary* m_psdDictionary;
    
    cocos2d::CCSize winSize;

    CJAnimation* ani;
 
	virtual bool init();
     
	static cocos2d::CCScene* scene();


    virtual void onEnter();
    virtual void onExit();

    
    bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
 
    CREATE_FUNC(PsdTest);
    
private:

 
};

 
