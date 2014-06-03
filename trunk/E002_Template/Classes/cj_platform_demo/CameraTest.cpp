

#include "CameraTest.h"
#include "CJUtils.h"
#include "CJMultimedia.h"

CCScene* CameraTest::scene()
{
	CCScene *scene = CCScene::create();
    
	CameraTest *layer = CameraTest::create();
    
	scene->addChild(layer);
    
	return scene;
}

bool CameraTest::init()
{
    CCLog("CameraTest::init()");
    
    CCLayerColor *colorLayer;
    colorLayer = CCLayerColor::create(ccc4(255, 255, 255, 255));
    
    addChild(colorLayer);
    
    CJUtils::getInstance()->setRootPath("e001_c000/");
    
    currentMode = CAMERA_MODE;
    isRecording = false;
    isCompleteRecording = true;
    
    return true;
}

void CameraTest::onEnter()
{
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    makeBtn();
     
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(CameraTest::onCameraFinished),
                                                                  CJNOTIFICATION_PICTURE_FINISHCALL,
                                                                  NULL);
 
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(CameraTest::onVideoRecordingFinished),
                                                                  CJNOTIFICATION_VIDEO_RECORDING_FINISHCALL,
                                                                  NULL);

    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(CameraTest::onFrameVideoFinished),
                                                                  CJNOTIFICATION_FRAME_VIDEOVIEW_FINISHCALL,
                                                                  NULL);

    }

void CameraTest::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CJNOTIFICATION_PICTURE_FINISHCALL);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CJNOTIFICATION_VIDEO_RECORDING_FINISHCALL);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CJNOTIFICATION_FRAME_VIDEOVIEW_FINISHCALL);

}

void CameraTest::makeBtn()
{
    CCSprite *camera = CCSprite::create(CJUtils::getInstance()->getFilePath("img", "camera_icon.png").c_str());
    camera->setPosition(ccp(312, 350));
    addChild(camera, 0 ,CameraTestTag::TagCameraBtn);
    
    CCSprite *video = CCSprite::create(CJUtils::getInstance()->getFilePath("img", "video_icon.png").c_str());
    video->setPosition(ccp(652, 350));
    addChild(video, 0, CameraTestTag::TagVideoBtn);

    CCSprite *touch = CCSprite::create(CJUtils::getInstance()->getFilePath("img", "touch_point.png").c_str());
    touch->setPosition(ccp(512, 100));
    touch->setVisible(false);
    addChild(touch, 0, CameraTestTag::TagStartBtn);
    
}

bool CameraTest::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    CCPoint tp = touch->getLocation();
    
    if(getChildByTag(CameraTestTag::TagCameraBtn) != NULL && CJUtils::getInstance()->hitTestPoint(getChildByTag(CameraTestTag::TagCameraBtn) , tp, false))
    {
        removeChildByTag(CameraTestTag::TagCameraBtn);
        removeChildByTag(CameraTestTag::TagVideoBtn);
        
        currentMode = CAMERA_MODE;
        
        getChildByTag(CameraTestTag::TagStartBtn)->setVisible(true);
        showCamera();
    }
    else if(getChildByTag(CameraTestTag::TagVideoBtn) != NULL && CJUtils::getInstance()->hitTestPoint(getChildByTag(CameraTestTag::TagVideoBtn) , tp, false))
    {
        removeChildByTag(CameraTestTag::TagCameraBtn);
        removeChildByTag(CameraTestTag::TagVideoBtn);
        
        currentMode = VIDEO_MODE;
        
        getChildByTag(CameraTestTag::TagStartBtn)->setVisible(true);
        showCamera();
    }
    else if(getChildByTag(CameraTestTag::TagStartBtn) != NULL && CJUtils::getInstance()->hitTestPoint(getChildByTag(CameraTestTag::TagStartBtn) , tp, false))
    {
        if (currentMode == CAMERA_MODE)
        {
            takePicture();
        }
        else
        {
            if(isRecording)
            {
                stopRecording();
            }
            else
            {
                isRecording = true;
                startRecording();
            }
        }
    }
    
    return false;
}

void CameraTest::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void CameraTest::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void CameraTest::showCamera()
{
    CJMultimedia::getInstance()->showCameraPreview("camera_frame.png", 0, 212, 50, 640, 480);
}

void CameraTest::takePicture()
{
    CJMultimedia::getInstance()->takePicture();
}

void CameraTest::startRecording()
{
//    CJMultimedia::getInstance()->startVideoRecording();
}

void CameraTest::stopRecording()
{
    CJMultimedia::getInstance()->stopVideoRecording();
}

void CameraTest::playFrameVideoview()
{
    CJMultimedia::getInstance()->playFrameVideo("camera_frame.png", recordedVideoFile, 212, 50, 640, 480);
}

void CameraTest::onCameraFinished(CCString* fileName)
{
    CCLog("camera Test >>  onCameraFinished %s", fileName->getCString());
}

void CameraTest::onVideoRecordingFinished(CCString* fileName)
{
    CCLog("camera Test >>  onVideoRecordingFinished %s", fileName->getCString());
    recordedVideoFile = fileName->getCString();
    
    CJMultimedia::getInstance()->removeCameraView();
    playFrameVideoview();
}

void CameraTest::onFrameVideoFinished()
{
    CCLog("camera Test >>  onFrameVideoFinished");
    CJMultimedia::getInstance()->removeFrameVideo();
    isCompleteRecording = true;
}