

#pragma once

#include "cocos2d.h"  

namespace VideoTestTag
{
    enum {
        TagBG = 100,
        TagSkipBtn = 101,
        
    };
}

USING_NS_CC;

class VideoTest : public CCLayer
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
 
    CREATE_FUNC(VideoTest);
    
    void onVideoFinished();
    void onBtnTouch(CCObject* tag);
private:

    void playVideo();
 
};

 
