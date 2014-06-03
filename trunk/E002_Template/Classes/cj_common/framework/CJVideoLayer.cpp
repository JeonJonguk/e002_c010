//
//  CJVideoLayer.cpp
//  E002_Template
//
//  Created by Jeong.YJ on 2014. 1. 9..
//
//

#include "CJVideoLayer.h"  
#include "E002_Base_Navigation.h"
#include "CJAnimationLibrary.h"
#include "CJMultimedia.h"

#pragma mark - init


CJVideoLayer::CJVideoLayer()
{  
}

CJVideoLayer::~CJVideoLayer()
{
}



bool CJVideoLayer::init()
{
    if (!CJLayer::init()) {
        return false;
    }
    
    mIntroVideoFileName = "";
    
    return true;
}

void CJVideoLayer::onEnter()
{
    CJLayer::onEnter();
}

void CJVideoLayer::onExit()
{
    removeVideoObserver();
    CJLayer::onExit();
}

#pragma mark - load view

void CJVideoLayer::onViewLoad()
{
    CJLayer::onViewLoad(); 
}


void CJVideoLayer::onViewLoaded()
{
    CJLayer::onViewLoaded();
    
    playVideo();
    addVideoObserver();
}

void CJVideoLayer::setVideoPath(std::string fileName)
{
    mIntroVideoFileName = fileName;
}

void CJVideoLayer::playVideo()
{
    if(mIntroVideoFileName == "")
    {
        CJLog("CJVideoLayer : please set video file name in onViewLoad.");
    }
    else
    {
        CJLog("%s", mIntroVideoFileName.c_str());
        CJMultimedia::getInstance()->playVideo(mIntroVideoFileName, true);
    }
}

void CJVideoLayer::addButtonVideo(std::string btnPath, int x, int y, int tag)
{
    CJLog("addButtonVideo");
    CJMultimedia::getInstance()->addButtonVideo(btnPath, x, y, tag);
}

void CJVideoLayer::onVideoFinishedCallback()
{
}

void CJVideoLayer::onVideoBtnTouchCallback(CCObject* tag)
{
}