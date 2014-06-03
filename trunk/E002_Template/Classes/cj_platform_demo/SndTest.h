

#pragma once

#include "cocos2d.h" 
#include "SimpleAudioEngine.h"

namespace SndTestTag
{
    enum {
        TagBG = 100,
        
    };
}

USING_NS_CC;     
using namespace CocosDenshion;

class SndTest : public CCLayer
{
public:
    cocos2d::CCSize winSize;
 
	virtual bool init();
     
	static cocos2d::CCScene* scene();
    
    CCDictionary *readPointXml;
    CCDictionary *readPopupXml;

    virtual void onEnter();
    virtual void onExit();

    void makeBtn();
    
    bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
 
    CREATE_FUNC(SndTest);
    
    bool isNarrPlaying;
    
    void onNarrationFinished(CCString* fileName);
private:

    void playNarration();
    void playEffect();
    void playBGM();
 
};

 
