//
//  E002_C010_P300_Intro.cpp
//  E002_Template
//
//  Created by whitems on 13. 5. 31..
//
//

#include "E002_C010_P300_Intro.h"
#include "E002_C010_P000_Index.h"
#include "E002_Base_Define.h"
#include "E002_C010_P310.h"

#pragma mark - init

#define E002_C010_P300_INTRO_ANI1 "e002_c010_p300_intro_flash_p01_action"
#define E002_C010_P300_INTRO_ANI2 "e002_c010_p300_intro_flash_p02_action"
#define E002_C010_P300_INTRO_ANI3 "e002_c010_p300_intro_flash_p03_action"


bool E002_C010_P300_Intro::init()
{
    if (!E002_Base_FlashIntro::init()) {
        return false;
    }
    
    return true;
}

void E002_C010_P300_Intro::onEnter()
{
    E002_Base_FlashIntro::onEnter();
    onViewLoad();
}

void E002_C010_P300_Intro::onExit()
{
    E002_Base_FlashIntro::onExit();
}

#pragma mark - load view

void E002_C010_P300_Intro::onViewLoad()
{
    E002_Base_FlashIntro::onViewLoad();

    initWithColor(ccc4(25, 54, 88, 255));
    
    setAnimationFile("e002_c010_p300_intro_flash_sheets.json", "e002_c010_p300_intro_flash_animations.json", FLASH_INTRO_DATEPOOL_KEY);
    
    setCutAnimationName(E002_C010_P300_INTRO_ANI1,
                        E002_C010_P300_INTRO_ANI2,
                        E002_C010_P300_INTRO_ANI3,
                        NULL);
    
    
//    e002_c010_p300_intro_snd_01_ch.mp3
//    e002_c010_p300_intro_snd_02_ar.mp3
//    e002_c010_p300_intro_snd_03_as.mp3
//    e002_c010_p300_intro_snd_04_ab.mp3
//    e002_c010_p300_intro_snd_05_ch.mp3
//    e002_c010_p300_intro_snd_06_as.mp3
//    e002_c010_p300_intro_snd_07_ch.mp3
//    e002_c010_p300_sfx_01.mp3
//    e002_c010_p300_sfx_02.wav
//    e002_c010_p300_sfx_03.mp3
//    e002_c010_p300_sfx_04.mp3
//    e002_c010_p300_sfx_river.mp3
//    e002_c010_p300_sfx_river2.mp3
    
    setNarrationOnFrame(E002_C010_P300_INTRO_ANI1, 1, "e002_c010_p300_intro_snd_01_ch.mp3");
    setNarrationOnFrame(E002_C010_P300_INTRO_ANI1, 148, "e002_c010_p300_intro_snd_02_ar.mp3");

    setNarrationOnFrame(E002_C010_P300_INTRO_ANI2, 293 -268, "e002_c010_p300_intro_snd_04_ab.mp3");
    setNarrationOnFrame(E002_C010_P300_INTRO_ANI2, 294 -268, "e002_c010_p300_sfx_01.mp3");
//    setNarrationOnFrame(E002_C010_P300_INTRO_ANI2, 300 -268, "e002_c010_p300_sfx_02.wav");
//    setNarrationOnFrame(E002_C010_P300_INTRO_ANI2, 347 -268, "e002_c010_p300_sfx_02.wav");
//    setNarrationOnFrame(E002_C010_P300_INTRO_ANI2, 381 -268, "e002_c010_p300_sfx_02.wav");
//    setNarrationOnFrame(E002_C010_P300_INTRO_ANI2, 394 -268, "e002_c010_p300_sfx_02.wav");
//    setNarrationOnFrame(E002_C010_P300_INTRO_ANI2, 407 -268, "e002_c010_p300_sfx_02.wav");
//    setNarrationOnFrame(E002_C010_P300_INTRO_ANI2, 439 -268, "e002_c010_p300_sfx_02.wav");
//    setNarrationOnFrame(E002_C010_P300_INTRO_ANI2, 444 -268, "e002_c010_p300_sfx_02.wav");
    
    setNarrationOnFrame(E002_C010_P300_INTRO_ANI3, 519 -498, "e002_c010_p300_intro_snd_06_as.mp3");
    setNarrationOnFrame(E002_C010_P300_INTRO_ANI3, 638 -498, "e002_c010_p300_intro_snd_07_ch.mp3");

    animationManagerParseStart();
    
}

void E002_C010_P300_Intro::onViewLoaded()
{
    E002_Base_FlashIntro::onViewLoaded();
    
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_c010_snd_bgm_03.mp3"), true);
}


void E002_C010_P300_Intro::onFlashIntroCompletedCallback()
{ 
    replaceSceneTransitionFadeOut(E002_C010_P310);
}

#pragma mark - navigation delegate

void E002_C010_P300_Intro::onTouchedNavigationButtonAtIndex()
{
    E002_Base_FlashIntro::onTouchedNavigationButtonAtIndex();
    
    E002_C010_P000_Index* _indexClass = E002_C010_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}
