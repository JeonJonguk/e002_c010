//
//  E002_C010_P100_Intro.cpp
//  E002_Template
//
//  Created by whitems on 13. 5. 31..
//
//

#include "E002_C010_P100_Intro.h"
#include "E002_C010_P000_Index.h"
#include "E002_Base_Define.h"
#include "E002_C010_P110.h"

#pragma mark - init

#define E002_C010_P100_INTRO_ANI1 "e002_c010_p100_intro_flash_p01_action"
#define E002_C010_P100_INTRO_ANI2 "e002_c010_p100_intro_flash_p02_action"
//#define E002_C010_P100_INTRO_ANI3 "e002_c010_p100_intro_flash_p03_action"


bool E002_C010_P100_Intro::init()
{
    if (!E002_Base_FlashIntro::init()) {
        return false;
    }
    
    return true;
}

void E002_C010_P100_Intro::onEnter()
{
    E002_Base_FlashIntro::onEnter();
    onViewLoad();
}

void E002_C010_P100_Intro::onExit()
{
    E002_Base_FlashIntro::onExit();
}

#pragma mark - load view

void E002_C010_P100_Intro::onViewLoad()
{
    E002_Base_FlashIntro::onViewLoad();

    initWithColor(ccc4(25, 54, 88, 255));
    
    setAnimationFile("e002_c010_p100_intro_flash_sheets.json", "e002_c010_p100_intro_flash_animations.json", FLASH_INTRO_DATEPOOL_KEY);
    
    setCutAnimationName(E002_C010_P100_INTRO_ANI1,
                        E002_C010_P100_INTRO_ANI2,
                        NULL);
    
//    e002_c010_p100_intro_sfx_01.mp3
//    e002_c010_p100_intro_sfx_02.mp3
//    e002_c010_p100_intro_sfx_03.mp3
//    e002_c010_p100_intro_snd_01_ch.mp3
//    e002_c010_p100_intro_snd_02_gb.mp3
//    e002_c010_p100_intro_snd_03_as.mp3
//    e002_c010_p100_intro_snd_04_gb.mp3
//    e002_c010_p100_intro_snd_05_as.mp3
//    e002_c010_p100_intro_snd_06_gb.mp3
    
    
    setNarrationOnFrame(E002_C010_P100_INTRO_ANI1, 1, "e002_c010_p100_intro_snd_01_ch.mp3");
    setNarrationOnFrame(E002_C010_P100_INTRO_ANI1, 20, "e002_c010_p100_intro_sfx_01.mp3");
    setNarrationOnFrame(E002_C010_P100_INTRO_ANI1, 80, "e002_c010_p100_intro_sfx_02.mp3");
    setNarrationOnFrame(E002_C010_P100_INTRO_ANI1, 96, "e002_c010_p100_intro_sfx_02.mp3");
    setNarrationOnFrame(E002_C010_P100_INTRO_ANI1, 111, "e002_c010_p100_intro_sfx_02.mp3");
    setNarrationOnFrame(E002_C010_P100_INTRO_ANI1, 126, "e002_c010_p100_intro_sfx_02.mp3");
    setNarrationOnFrame(E002_C010_P100_INTRO_ANI1, 186, "e002_c010_p100_intro_snd_02_gb.mp3");

    setNarrationOnFrame(E002_C010_P100_INTRO_ANI2, 315 -289, "e002_c010_p100_intro_snd_03_as.mp3");
    setNarrationOnFrame(E002_C010_P100_INTRO_ANI2, 402 -289, "e002_c010_p100_intro_snd_05_as.mp3");
    setNarrationOnFrame(E002_C010_P100_INTRO_ANI2, 478 -289, "e002_c010_p100_intro_sfx_03.mp3");
    setNarrationOnFrame(E002_C010_P100_INTRO_ANI2, 530 -289, "e002_c010_p100_intro_snd_04_gb.mp3");
    setNarrationOnFrame(E002_C010_P100_INTRO_ANI2, 605 -289, "e002_c010_p100_intro_snd_06_gb.mp3");


    
    animationManagerParseStart();
    
}

void E002_C010_P100_Intro::onViewLoaded()
{
    E002_Base_FlashIntro::onViewLoaded();
    
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_c010_snd_bgm_01.mp3"), true);
}

void E002_C010_P100_Intro::onFlashIntroCompletedCallback()
{
    replaceSceneTransitionFadeOut(E002_C010_P110);
}

#pragma mark - navigation delegate

void E002_C010_P100_Intro::onTouchedNavigationButtonAtIndex()
{
    E002_Base_FlashIntro::onTouchedNavigationButtonAtIndex();
    
    E002_C010_P000_Index* _indexClass = E002_C010_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}
