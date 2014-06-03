

#include "VoiceRecordingTest.h" 
#include "CJUtils.h"
#include "CJMultimedia.h"

CCScene* VoiceRecordingTest::scene()
{
	CCScene *scene = CCScene::create();
    
	VoiceRecordingTest *layer = VoiceRecordingTest::create();
    
	scene->addChild(layer);
    
	return scene;
}

bool VoiceRecordingTest::init()
{
    CCLog("VoiceRecordingTest::init()");
    
    CJUtils::getInstance()->setRootPath("e001_c000/");
     
    return true;
}

void VoiceRecordingTest::onEnter()
{
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    makeBtn();
    
 
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(VoiceRecordingTest::onPlayingFinished),
                                                                  CJNOTIFICATION_RECORDED_VOICE_FINISHCALL,
                                                                  NULL);
}

void VoiceRecordingTest::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CJNOTIFICATION_RECORDED_VOICE_FINISHCALL);
}

void VoiceRecordingTest::makeBtn()
{
    CCSprite *recBtn = CCSprite::create(CJUtils::getInstance()->getFilePath("img", "rec_btn.png").c_str());
    recBtn->setPosition(ccp(512, 512));
    addChild(recBtn,1,VoiceRecordingTag::TagRecBtn);
    
    CCSprite *stopBtn = CCSprite::create(CJUtils::getInstance()->getFilePath("img", "stop_btn.png").c_str());
    stopBtn->setPosition(ccp(512, 512));
    stopBtn->setVisible(false);
    addChild(stopBtn,1,VoiceRecordingTag::TagStopBtn);
}

bool VoiceRecordingTest::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    CCPoint tp = touch->getLocation();
    
    if(getChildByTag(VoiceRecordingTag::TagRecBtn) != NULL && CJUtils::getInstance()->hitTestPoint(getChildByTag(VoiceRecordingTag::TagRecBtn) , tp, false))
    {
        removeChild(getChildByTag(VoiceRecordingTag::TagRecBtn));
        CJMultimedia::getInstance()->startVoiceRecording();
        getChildByTag(VoiceRecordingTag::TagStopBtn)->setVisible(true);
    }
    else if(getChildByTag(VoiceRecordingTag::TagStopBtn) != NULL && CJUtils::getInstance()->hitTestPoint(getChildByTag(VoiceRecordingTag::TagStopBtn) , tp, false))
    {
        removeChild(getChildByTag(VoiceRecordingTag::TagStopBtn));
        CJMultimedia::getInstance()->stopVoiceRecording(); 
    }
    
    return false;
}

void VoiceRecordingTest::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void VoiceRecordingTest::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void VoiceRecordingTest::onPlayingFinished()
{ 
    CCLog("Recorded Play Finish");
}
