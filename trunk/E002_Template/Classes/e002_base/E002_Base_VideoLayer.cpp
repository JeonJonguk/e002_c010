//
//  E001_Base_P000_Intro.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#include "E002_Base_VideoLayer.h"

#pragma mark - init


E002_Base_VideoLayer::E002_Base_VideoLayer()
{
}

E002_Base_VideoLayer::~E002_Base_VideoLayer()
{
}



bool E002_Base_VideoLayer::init()
{
    if (!CJVideoLayer::init()) {
        return false;
    }
    
    mVideoType = kTagNoramlType;
    
    return true;
}

void E002_Base_VideoLayer::onEnter()
{
    CJMultimedia::getInstance()->stopBGM();
    CJVideoLayer::onEnter();
}

void E002_Base_VideoLayer::onExit()
{
    CJVideoLayer::onExit();
}

#pragma mark - load view

void E002_Base_VideoLayer::onViewLoad()
{
    CJVideoLayer::onViewLoad();
    //CJUtils::getInstance()->setUserDefaultIntegerForKey(NAVIGATION_GLOBAL_INDEX_KEY, 0);
}

void E002_Base_VideoLayer::setVideoPath(std::string fileName, int type)
{
    CJVideoLayer::setVideoPath(getFilePath("mov", fileName));
    
    if(type == kTagSongType)
    {
        mVideoType = kTagSongType;
    }
}

void E002_Base_VideoLayer::onViewLoaded()
{
    CJVideoLayer::onViewLoaded();
    
    if(mVideoType == kTagNoramlType)
    {
        addButtonVideo(getCommonFilePath("img", "e001_common_video_btn_index.png"), 0, 0, kTagIndexBtn);
        addButtonVideo(getCommonFilePath("img", "e001_common_video_btn_skip.png"), 1024 - 102, 0, kTagSkipBtn);
    }
    else if(mVideoType == kTagSongType)
    {
        addButtonVideo(getCommonFilePath("img", "e001_common_video_btn_index.png"), 0, 0, kTagIndexBtn);
    }
}


void E002_Base_VideoLayer::onVideoFinishedCallback()
{
}

void E002_Base_VideoLayer::onVideoBtnTouchCallback(CCObject* tag)
{
    if((int)tag == kTagIndexBtn)
    { 
        CJMultimedia::getInstance()->stopVideo();
        onIndexBtnTouch();
    }
    else if((int)tag == kTagSkipBtn)
    {
        CJMultimedia::getInstance()->stopVideo();
        onVideoFinishedCallback();
    }
}

void E002_Base_VideoLayer::onIndexBtnTouch()
{
}