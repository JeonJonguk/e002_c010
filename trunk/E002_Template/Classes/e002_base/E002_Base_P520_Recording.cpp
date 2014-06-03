//
//  E002_Base_P520_Recording.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#include "E002_Base_P520_Recording.h"

#define POS_TOPLEFT                                     CCPointMake(winHalfSize.width-463, winHalfSize.height+309)
#define POS_TOPRIGHT                                    CCPointMake(winHalfSize.width+463, winHalfSize.height+309)

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define OS_HEIGHT_GAP                                   0
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define OS_HEIGHT_GAP                                   0
#endif

#pragma mark - init

E002_Base_P520_Recording::E002_Base_P520_Recording()
{
    m_psdDictionary = new CCDictionary();
    
    m_vSubtitlesFileName.clear();
    m_vSubtitlesDelays.clear();

    m_subtitle = NULL;
    _nSubtitlesIndex = 0;
    m_musicFileName.clear();
    m_recordedVideoFile.clear();

    _bIsRecordingStarted = false;
    _hideCameraXposition = 900;
}

E002_Base_P520_Recording::~E002_Base_P520_Recording()
{
    CC_SAFE_DELETE(m_psdDictionary);
}



bool E002_Base_P520_Recording::init()
{
    if (!CJLayer::init()) {
        return false;
    }
    return true;
}


void E002_Base_P520_Recording::onEnter()
{
    CJLayer::onEnter();
    setAnimationParent(this);
}

void E002_Base_P520_Recording::onExit()
{
    CJMultimedia::getInstance()->setNarrationMainVolume(1.0);
    
    removeSoundObserver();
//    removeVideoObserver();
    
    stopRecordingVideo();
    removeVideoView();
    
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,CJNOTIFICATION_FRAME_VIDEOVIEW_FINISHCALL);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CJNOTIFICATION_VIDEO_RECORDING_FINISHCALL);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CJNOTIFICATION_CAMERA_ONPAUSE_RECORDING_CALL);
    CJMultimedia::getInstance()->stopBGM();
    CJLayer::onExit();
    
}


#pragma mark - touch

bool E002_Base_P520_Recording::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    return onTouchBegan(tp);
}

void E002_Base_P520_Recording::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    onTouchMoved(tp);
}

void E002_Base_P520_Recording::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint tp = pTouch->getLocation();
    onTouchEnded(tp);
}

#pragma mark - load view

void E002_Base_P520_Recording::onViewLoad()
{
    setMenuNavigation();
    
    
}

void E002_Base_P520_Recording::onViewLoaded()
{
    addSoundObserver();
//    addVideoObserver();
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(E002_Base_P520_Recording::onVideoFrameFinishedCallback),
                                                                  CJNOTIFICATION_FRAME_VIDEOVIEW_FINISHCALL,
                                                                  NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                 callfuncO_selector(E002_Base_P520_Recording::onVideoRecordingFinished),
                                                                 CJNOTIFICATION_VIDEO_RECORDING_FINISHCALL,
                                                                 NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(E002_Base_P520_Recording::onPauseVideoRecording),
                                                                  CJNOTIFICATION_CAMERA_ONPAUSE_RECORDING_CALL,
                                                                  NULL);
    
    
    CJMultimedia::getInstance()->showCameraPreview(mCameraFrameImg, 0, mCameraPositionX ,_hideCameraXposition, mCameraWidth, mCameraHeight);

    
}

void E002_Base_P520_Recording::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == m_musicFileName) {
        CJUtils::performSelector(this, callfunc_selector(E002_Base_P520_Recording::onComplete), 1.0f);
        
        
        //LMS
        std::string contendId = CJUtils::getInstance()->getContentID();
        std::string key = CJUtils::getStringMerge(contendId, "_p520_lms");
        
        int oldLms = CJUtils::getInstance()->getUserDefaultIntegerForKey(key);
        CJUtils::getInstance()->setUserDefaultIntegerForKey(key, oldLms + 1);
        
        CJLog(" == 520 LMS = %d",oldLms + 1);
        
        //movie file LMS
        CJUtils::saveLMSFile();

    }
}

void E002_Base_P520_Recording::onVideoRecordingFinished(CCString* fileName)
{
//    CCLog("camera Test >>  onVideoRecordingFinished %s", fileName->getCString());
//    m_recordedVideoFile = fileName->getCString();
}

void E002_Base_P520_Recording::onPauseVideoRecording()
{
    CJLog("E002_Base_P520_Recording::onPauseVideoRecording()");
//    CJUtils::performSelector(this, callfunc_selector(E002_Base_P520_Recording::onTouchedMenuAtSongMenu),0.5);
    onTouchedMenuAtSongMenu();
}


void E002_Base_P520_Recording::onVideoFrameFinishedCallback()
{
    removeVideoView();
    
}

#pragma mark - camera

void E002_Base_P520_Recording::setCameraSetting(std::string frameImg, int x, int y,  int width, int height)
{
    mCameraFrameImg = CJUtils::getInstance()->getFilePath("img", frameImg);
    mCameraPositionX = x;
    mCameraPositionY = y - OS_HEIGHT_GAP;
    mCameraWidth = width;
    mCameraHeight = height;
    
    
    
    
}

void E002_Base_P520_Recording::startRecordingVideo()
{
    if (!_bIsRecordingStarted)
    {
        
        std::string path = CJUtils::getLMSFileName(5, eFileType_Video);
        m_recordedVideoFile = "temp.mp4";
        CJLog("+ start recording file name = %s ",m_recordedVideoFile.c_str());
        
        CJMultimedia::getInstance()->moveToCameraView(mCameraPositionX, mCameraPositionY);
        CJMultimedia::getInstance()->startVideoRecording("temp.mp4");
        _bIsRecordingStarted = true;
        
    }
    else
    {
        CJLog(" already recording started. ");
    }
}

void E002_Base_P520_Recording::stopRecordingVideo()
{
    CJMultimedia::getInstance()->moveToCameraView(mCameraPositionX, _hideCameraXposition); //hide camera
    CJMultimedia::getInstance()->stopVideoRecording();  //recording stop
    CJMultimedia::getInstance()->removeCameraView();    //remove camera
    
}

void E002_Base_P520_Recording::playFrameVideoview()
{
    CJLog("+ play recorded file name = %s ",m_recordedVideoFile.c_str());
    CJMultimedia::getInstance()->playFrameVideo(mCameraFrameImg, m_recordedVideoFile, mCameraPositionX, mCameraPositionY, mCameraWidth, mCameraHeight);
}
void E002_Base_P520_Recording::removeVideoView()
{
    CJMultimedia::getInstance()->removeFrameVideo();
}

#pragma mark - function

void E002_Base_P520_Recording::startMusic(std::string pMusicFileName)
{
    
    m_musicFileName = pMusicFileName;
    playNarration(m_musicFileName);
    CJMultimedia::getInstance()->setNarrationMainVolume(1.0);
}

void E002_Base_P520_Recording::startRecordedVideo()
{
     playFrameVideoview();
}

void E002_Base_P520_Recording::setMenuNavigation()
{
    std::string _strResPrefix = CJUtils::getInstance()->getContentID();
    std::string strNormalImageName  = _strResPrefix;
    std::string strSelectImageName  = _strResPrefix;
    std::string strDisableImageName = _strResPrefix;
    
    std::string normal = strNormalImageName.append("_p510_img_btn_singmain_n.png");
    std::string select = strSelectImageName.append("_p510_img_btn_singmain_s.png");
    
    CJSprite* normalSp = CJSprite::createWithFullPath(strNormalImageName.c_str());
    CJSprite* selectedSp = CJSprite::createWithFullPath(strSelectImageName.c_str());
    
    // Make CCMenu item
    CCMenuItemSprite* menuItemSp = CCMenuItemSprite::create(normalSp,
                                                            selectedSp,
                                                            this,
                                                            menu_selector(E002_Base_P520_Recording::onTouchedMenuAtSongMenu));
    
    menu = CCMenu::create(menuItemSp,NULL);
    menu->setPosition(POS_TOPLEFT);
    addChild(menu, kDepth7_popup-1);
}



//subtitles

void E002_Base_P520_Recording::playSubtitles()
{
    CJLog("_nSubtitlesIndex = %d", _nSubtitlesIndex);
    
    float delay = 0;
    if (_nSubtitlesIndex == 0) {
        delay = m_vSubtitlesDelays[_nSubtitlesIndex];
    }else{
        delay = m_vSubtitlesDelays[_nSubtitlesIndex] - m_vSubtitlesDelays[_nSubtitlesIndex-1];
    }
    
    CCAction* subtitleLoopAction = CCSequence::create(CCDelayTime::create(delay),
                                                      CCCallFunc::create(this, callfunc_selector(E002_Base_P520_Recording::addSubtitles)),
                                                      NULL);
    this->runAction(subtitleLoopAction);
}



void E002_Base_P520_Recording::addSubtitles()
{

    if (m_subtitle != NULL)
    {
        m_subtitle->removeFromParent();
    }
    
    
    m_subtitle = CJPsdParser::getPsdSprite(m_vSubtitlesFileName[_nSubtitlesIndex], m_psdDictionary);
    addChild(m_subtitle, kDepth4_title);
    m_subtitle->runAction(CCSequence::create(CCEaseSineOut::create(CCScaleTo::create(0.1, 1.05)),
                                            CCEaseSineIn::create(CCScaleTo::create(0.1, 1.0)),
                                            NULL));
    
    if (_nSubtitlesIndex < m_vSubtitlesFileName.size()-1) {
        _nSubtitlesIndex++;
        playSubtitles();
    }else{
//        CJUtils::performSelector(this, callfunc_selector(E002_Base_P520_Recording::completeSubtitles),3.0);
//        completeSubtitles();
    }
}

void E002_Base_P520_Recording::completeSubtitles()
{
    if (m_subtitle != NULL) {
//        m_subtitle->runAction(CCSequence::create(
//                                                 CCFadeOut::create(0.3),
//                                                 CCCallFuncN::create(this, callfuncN_selector(E002_Base_P520_Recording::removeChild)),
//                                                 NULL));
        
        m_subtitle->removeFromParent();
        m_subtitle = NULL;
    }
    
    
}

void E002_Base_P520_Recording::onComplete()
{
    CJMultimedia::getInstance()->setNarrationMainVolume(1.0);
    
    completeSubtitles();
    setSingUserDefaultValue(2);
    _nSubtitlesIndex = 0;
    
    
       
}


#pragma mark - userDefault

void E002_Base_P520_Recording::setSingUserDefaultValue(int pValue)
{
    std::string contendId = CJUtils::getInstance()->getContentID();
    std::string key = CJUtils::getStringMerge(contendId, "_p500_singMenuCompleteIndex");
    if (CJUtils::getInstance()->getUserDefaultIntegerForKey(key) < pValue) {
        CJUtils::getInstance()->setUserDefaultIntegerForKey(key, pValue);
        
    }
    
}


#pragma mark - speaker & light animation

void E002_Base_P520_Recording::speakerAnimation(CCNode* node)
{
    CCActionInterval* scaleA1 = CCScaleTo::create(0.15f, 1.05f);
    CCActionInterval* scaleE1 = CCEaseSineIn::create(scaleA1);
    
    CCActionInterval* scaleA2 = CCScaleTo::create(0.15f, 1.0f);
    CCActionInterval* scaleE2 = CCEaseSineOut::create(scaleA2);
    
    CCActionInterval* scaleA3 = CCScaleTo::create(0.15f, 1.1f);
    CCActionInterval* scaleE3 = CCEaseSineIn::create(scaleA3);
    
    CCActionInterval* scaleA4 = CCScaleTo::create(0.15f, 1.0f);
    CCActionInterval* scaleE4 = CCEaseSineOut::create(scaleA4);
    
    CCActionInterval* seq = CCSequence::create(
                                               scaleE1,
                                               scaleE2,
                                               scaleE3,
                                               scaleE4,
                                               NULL);
    
    CCRepeatForever *repeatForever = CCRepeatForever::create( seq );
    
    node->runAction(repeatForever);
}


void E002_Base_P520_Recording::lightingColorAnimation(CCNode* node)
{
    CCActionInterval* tintA1 = CCTintTo::create(0.2f, 255, 216, 0);
    CCActionInterval* tintE1 = CCEaseSineInOut::create(tintA1);
    
    CCActionInterval* tintA2 = CCTintTo::create(0.2f, 246, 115, 120);
    CCActionInterval* tintE2 = CCEaseSineInOut::create(tintA2);
    
    CCActionInterval* tintA3 = CCTintTo::create(0.2f, 13, 184, 150);
    CCActionInterval* tintE3 = CCEaseSineInOut::create(tintA3);
    
    CCActionInterval* tintA4 = CCTintTo::create(0.2f, 188, 143, 202);
    CCActionInterval* tintE4 = CCEaseSineInOut::create(tintA4);
    
    
    CCActionInterval* seq = CCSequence::create(
                                               tintE1,
                                               tintE2,
                                               tintE3,
                                               tintE4,
                                               NULL);
    
    CCRepeatForever *repeatForever = CCRepeatForever::create( seq );
    
    node->runAction(repeatForever);
}

void E002_Base_P520_Recording::lightRotateAnimation(CCNode* node, float r1, float r2)
{
    CCActionInterval* rotA1 = CCRotateTo::create(0.3f, r1);
    CCActionInterval* rotE1 = CCEaseSineOut::create(rotA1);
    
    CCActionInterval* rotA2 = CCRotateTo::create(0.3f, r2);
    CCActionInterval* rotE2 = CCEaseSineOut::create(rotA2);
    
    
    CCActionInterval* seq = CCSequence::create(
                                               rotE1,
                                               CCDelayTime::create(0.5f),
                                               rotE2,
                                               CCDelayTime::create(0.5f),
                                               NULL);
    
    
    CCRepeatForever *repeatForever = CCRepeatForever::create( seq );
    
    node->runAction(repeatForever);
}


void E002_Base_P520_Recording::onTouchedMenuAtSongMenu()
{
    stopRecordingVideo();
    removeVideoView();
}