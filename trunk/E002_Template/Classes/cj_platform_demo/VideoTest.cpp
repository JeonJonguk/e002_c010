

#include "VideoTest.h" 
#include "CJUtils.h"
#include "CJMultimedia.h"

CCScene* VideoTest::scene()
{
	CCScene *scene = CCScene::create();
    
	VideoTest *layer = VideoTest::create();
    
	scene->addChild(layer);
    
	return scene;
}

bool VideoTest::init()
{
    CCLog("VideoTest::init()");
     
      return true;
}

void VideoTest::onEnter()
{
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    makeBtn();
     
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(VideoTest::onVideoFinished),
                                                                  CJNOTIFICATION_VIDEO_FINISHCALL,
                                                                  NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(VideoTest::onBtnTouch),
                                                                  CJNOTIFICATION_VIDEO_BUTTONCALL,
                                                                  NULL);

    }

void VideoTest::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CJNOTIFICATION_VIDEO_FINISHCALL);
}

void VideoTest::makeBtn()
{
    CCSprite *btn = CCSprite::create(CJUtils::getInstance()->getFilePath("img", "touch_point.png").c_str());
    btn->setPosition(ccp(512, 512));
    addChild(btn,1,1);
    
}

bool VideoTest::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    CCPoint tp = touch->getLocation();
    
    if(CJUtils::getInstance()->hitTestPoint(getChildByTag(1) , tp, false))
    {
        playVideo();
//        CJMultimedia::getInstance()->addButtonVideo(CJUtils::getInstance()->getFilePath("img", "cjplatform_video_btn_skip.png"), 942, 39, VideoTestTag::TagSkipBtn);

    }
    
    return false;
}

void VideoTest::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void VideoTest::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void VideoTest::playVideo()
{
    CJMultimedia::getInstance()->playVideo(CJUtils::getInstance()->getFilePath( "mov", "readbook.mp4"), true);
}


void VideoTest::onVideoFinished()
{
    CCLog("video Test >>  onVideoFinished "); 
}

void VideoTest::onBtnTouch(CCObject* tag)
{
    CCLog("onBtn touch %d", tag);
    
    if((int)tag == VideoTestTag::TagSkipBtn)
    {
        CJMultimedia::getInstance()->stopVideo();
    }
}