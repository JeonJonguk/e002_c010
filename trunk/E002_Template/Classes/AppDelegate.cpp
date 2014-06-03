//
//  SoundPhonics_TemplateAppDelegate.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 3..
//  Copyright __MyCompanyName__ 2013�� All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CJMultimedia.h"


#include "CJUserDBManage.h"
#include "CJUserContent.h"
#include "CJLMSPKGInterface.h"

#include "CJUtils.h"
#include "CJMacros.h"
#include "E002_Base_FlashIntro.h"

#include "E002_C010_P110.h"
#include "E002_C010_P130.h"
#include "E002_C010_P210.h"
#include "E002_C010_P230.h"
#include "E002_C010_P310.h"
#include "E002_C010_P320.h"
#include "E002_C010_P330.h"
#include "E002_C010_P100_Intro.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    isBackgroundPlaying = false;
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(false);
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1024, 768, kResolutionShowAll);
    
    //temp
    CJUtils::getInstance()->setRootPath("");
    CJUtils::getInstance()->setContentID("e002_c010");
    CJUtils::getInstance()->setCommonResourcePath("e002_common");
    CJUtils::getInstance()->setLanguage("kr");
    
    std::string flashPath = CJUtils::getInstance()->getResourcePath();
    std::string flashCommonPath = CJUtils::getInstance()->getCommonResourcePath();
    CJFlash::CResourcePathDirector::sharedInstance()->setRootResourcePath(flashPath.append("flash"));
    CJFlash::CResourcePathDirector::sharedInstance()->setCommonResourcePath(flashCommonPath.append("flash"));
    CJUserDBManage::sharedInstance()->open(CC_TARGET_PLATFORM);
    CJUserContent::sharedInstance()->createTable();
    
    CJLMSPKGInterface::getInstance()->startPackage(19, "e002");
    CJLMSPKGInterface::getInstance()->startContent("c010");
    
    //lock test
    //    CJUtils::getInstance()->setUserDefaultIntegerForKey("e001_c010_completeIndex",6);
    
    
    
    //  run
    runSceneMacro(E002_C010_P100_Intro);
    //    runSceneMacro(E002_C010_P110);
    //    runSceneMacro(E002_C010_P130);
    //    runSceneMacro(E002_C010_P210);
    //    runSceneMacro(E002_C010_P230);
    //    runSceneMacro(E002_C010_P310);
    //    runSceneMacro(E002_C010_P320);
    //    runSceneMacro(E002_C010_P330);
    
    //  pDirector->runWithScene(p Scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    isBackgroundPlaying = SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
    CJMultimedia::getInstance()->pauseAllEffects();
    CJMultimedia::getInstance()->pauseBGM();
    CJMultimedia::getInstance()->pauseToPlayingNarration();
    CJMultimedia::getInstance()->pauseRecordedVoice();
    
    
    CCDirector::sharedDirector()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    if (isBackgroundPlaying) {
        CJMultimedia::getInstance()->resumeBGM();
    }
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    CJMultimedia::getInstance()->resumePausedNarration();
    CJMultimedia::getInstance()->resumeRecordedVoice();
    
    
    CCDirector::sharedDirector()->startAnimation();
}
