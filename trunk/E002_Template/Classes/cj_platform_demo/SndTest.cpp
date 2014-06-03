

#include "SndTest.h" 
#include "CJUtils.h"
#include "CJMultimedia.h"

CCScene* SndTest::scene()
{
	CCScene *scene = CCScene::create();
    
	SndTest *layer = SndTest::create();
    
	scene->addChild(layer);
    
	return scene;
}

bool SndTest::init()
{
    CCLog("SndTest::init()");
     
      return true;
}

void SndTest::onEnter()
{
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    makeBtn();
    
    playBGM();
    
    isNarrPlaying = false;
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(SndTest::onNarrationFinished),
                                                                  CJNOTIFICATION_VOICE_FINISHCALL,
                                                                  NULL);
}

void SndTest::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CJNOTIFICATION_VOICE_FINISHCALL);
    CJMultimedia::getInstance()->unloadAllNarration();
}

void SndTest::makeBtn()
{
    CCSprite *btn = CCSprite::create(CJUtils::getInstance()->getFilePath("img", "touch_point.png").c_str());
    btn->setPosition(ccp(512, 512));
    addChild(btn,1,1);
    
}

bool SndTest::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    CCPoint tp = touch->getLocation();
    
//    playEffect();
    
    if(CJUtils::hitTestPoint(getChildByTag(1) , tp, false))
    {
        if(CJMultimedia::getInstance()->isNarrationPlaying())
            CJMultimedia::getInstance()->pauseNarration(CJUtils::getInstance()->getFilePath("img","narration3.mp3"));
        else
        {
            
            playNarration();
        }
    }
    
    return false;
}

void SndTest::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void SndTest::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void SndTest::playEffect()
{
    unsigned int id = CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getFilePath("snd","effect.mp3").c_str(), false);
}

void SndTest::playBGM()
{
    CJMultimedia::getInstance()->playBGM(CJUtils::getInstance()->getFilePath("snd","bgm.mp3"), false);
} 

void SndTest::playNarration()
{
    
//    CJMultimedia::getInstance()->preloadNarration(CJUtils::getInstance()->getFilePath("", "snd", "narration1.mp3"));
//    CJMultimedia::getInstance()->preloadNarration(CJUtils::getInstance()->getFilePath("", "snd", "narration2.mp3"));
//    CJMultimedia::getInstance()->preloadNarration(CJUtils::getInstance()->getFilePath("", "snd", "narration3.mp3"));
//    CJMultimedia::getInstance()->preloadNarration(CJUtils::getInstance()->getFilePath("", "snd", "narration4.mp3"));
    
//    CJMultimedia::getInstance()->playNarration("narration3.mp3");
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getFilePath("snd", "narration3.mp3").c_str());

//    CJMultimedia::getInstance()->playAllNarration();
}

void SndTest::onNarrationFinished(CCString* fileName)
{
    CCLog("snd Test >>  onNarrationFinished");
}