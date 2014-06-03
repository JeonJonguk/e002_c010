//
//  E002_C010_P200_Intro.cpp
//  E002_Template
//
//  Created by whitems on 13. 5. 31..
//
//

#include "E002_C010_P200_Intro.h"
#include "E002_C010_P000_Index.h"
#include "E002_Base_Define.h"
#include "E002_C010_P210.h"

#pragma mark - init

#define E002_C010_P200_INTRO_ANI1 "e002_c010_p200_intro_flash_p01_action"
#define E002_C010_P200_INTRO_ANI2 "e002_c010_p200_intro_flash_p02_action"
#define E002_C010_P200_INTRO_ANI3 "e002_c010_p200_intro_flash_p03_action"

bool E002_C010_P200_Intro::init()
{
    if (!E002_Base_FlashIntro::init()) {
        return false;
    }
    
    return true;
}

void E002_C010_P200_Intro::onEnter()
{
    E002_Base_FlashIntro::onEnter();
    onViewLoad();
}

void E002_C010_P200_Intro::onExit()
{
    E002_Base_FlashIntro::onExit();
}

#pragma mark - load view

void E002_C010_P200_Intro::onViewLoad()
{
    E002_Base_FlashIntro::onViewLoad();

    initWithColor(ccc4(58, 31, 11, 255));
    
    setAnimationFile("e002_c010_p200_intro_flash_sheets.json", "e002_c010_p200_intro_flash_animations.json", FLASH_INTRO_DATEPOOL_KEY);
    
    setCutAnimationName(E002_C010_P200_INTRO_ANI1,
                        E002_C010_P200_INTRO_ANI2,
                        E002_C010_P200_INTRO_ANI3,
                        NULL);
    
//    e002_c010_p200_intro_sfx_01.mp3
//    e002_c010_p200_intro_sfx_02.mp3
//    e002_c010_p200_intro_sfx_03.mp3
//    e002_c010_p200_intro_sfx_horse_01.mp3
//    e002_c010_p200_intro_sfx_horse_02.mp3
//    e002_c010_p200_intro_sfx_people.mp3
//    e002_c010_p200_intro_snd_01_ch.mp3
//    e002_c010_p200_intro_snd_02_ar.mp3
//    e002_c010_p200_intro_snd_03_bb.mp3
//    e002_c010_p200_intro_snd_04_as.mp3
//    e002_c010_p200_intro_snd_05_bb.mp3
    
    setNarrationOnFrame(E002_C010_P200_INTRO_ANI1, 1, "e002_c010_p200_intro_snd_01_ch.mp3");
    setNarrationOnFrame(E002_C010_P200_INTRO_ANI1, 62, "e002_c010_p200_intro_sfx_02.mp3");
    setNarrationOnFrame(E002_C010_P200_INTRO_ANI1, 140, "e002_c010_p200_intro_snd_02_ar.mp3");
    
    setNarrationOnFrame(E002_C010_P200_INTRO_ANI2, 289 -264, "e002_c010_p200_intro_sfx_02.mp3");
    setNarrationOnFrame(E002_C010_P200_INTRO_ANI2, 384 -264, "e002_c010_p200_intro_snd_03_bb.mp3");
    
    setNarrationOnFrame(E002_C010_P200_INTRO_ANI3, 538 -514, "e002_c010_p200_intro_snd_04_as.mp3");
    setNarrationOnFrame(E002_C010_P200_INTRO_ANI3, 740 -514, "e002_c010_p200_intro_snd_05_bb.mp3");
    setNarrationOnFrame(E002_C010_P200_INTRO_ANI3, 829 -514, "e002_c010_p200_intro_sfx_03.mp3");
    
    
    animationManagerParseStart();
    
}

void E002_C010_P200_Intro::onViewLoaded()
{
    E002_Base_FlashIntro::onViewLoaded();
    
    
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_c010_snd_bgm_02.mp3"), true);
}


void E002_C010_P200_Intro::onFlashIntroCompletedCallback()
{
    replaceSceneTransitionFadeOut(E002_C010_P210);
}

#pragma mark - navigation delegate

void E002_C010_P200_Intro::onTouchedNavigationButtonAtIndex()
{
    E002_Base_FlashIntro::onTouchedNavigationButtonAtIndex();
    
    E002_C010_P000_Index* _indexClass = E002_C010_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}
