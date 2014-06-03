//
//  E002_C030_P200_Intro.cpp
//  E002_Template
//
//  Created by whitems on 13. 5. 31..
//
//

#include "E002_C030_P200_Intro.h"
#include "E002_C030_P000_Index.h"
#include "E002_Base_Define.h"
#include "E002_C030_P210.h"

#pragma mark - init

#define E002_C030_P200_INTRO_ANI1 "e002_c030_200_intro_flash_p01_action"
#define E002_C030_P200_INTRO_ANI2 "e002_c030_200_intro_flash_p02_action"
#define E002_C030_P200_INTRO_ANI3 "e002_c030_200_intro_flash_p03_action"

bool E002_C030_P200_Intro::init()
{
    if (!E002_Base_FlashIntro::init()) {
        return false;
    }
    
    return true;
}

void E002_C030_P200_Intro::onEnter()
{
    E002_Base_FlashIntro::onEnter();
    onViewLoad();
}

void E002_C030_P200_Intro::onExit()
{
    E002_Base_FlashIntro::onExit();
}

#pragma mark - load view

void E002_C030_P200_Intro::onViewLoad()
{
    E002_Base_FlashIntro::onViewLoad();

    initWithColor(ccc4(58, 31, 11, 255));
    
    setAnimationFile("e002_c030_p200_flash_intro_sheets.json", "e002_c030_p200_flash_intro_animations.json", FLASH_INTRO_DATEPOOL_KEY);
    
    setCutAnimationName(E002_C030_P200_INTRO_ANI1,
                        E002_C030_P200_INTRO_ANI2,
                        E002_C030_P200_INTRO_ANI3,
                        NULL);
    
    setNarrationOnFrame(E002_C030_P200_INTRO_ANI1, 2, "e002_c030_p200_intro_snd_01_bb.mp3");
    setNarrationOnFrame(E002_C030_P200_INTRO_ANI1, 75, "e002_c030_p200_intro_snd_02_as.mp3");
    setNarrationOnFrame(E002_C030_P200_INTRO_ANI1, 161, "e002_c030_p200_intro_snd_03_mk.mp3");
    setNarrationOnFrame(E002_C030_P200_INTRO_ANI2, 265-243, "e002_c030_p200_intro_snd_04_ar.mp3");
    setNarrationOnFrame(E002_C030_P200_INTRO_ANI2, 395-243, "e002_c030_p200_intro_snd_05_as.mp3");
    setNarrationOnFrame(E002_C030_P200_INTRO_ANI3, 509-488, "e002_c030_p200_intro_snd_06_bb.mp3");
    
    setEffectOnFrame(E002_C030_P200_INTRO_ANI1, 60, "e002_c030_p000_intro_sfx_com_move.mp3");
    setEffectOnFrame(E002_C030_P200_INTRO_ANI1, 151, "e002_c030_p000_intro_sfx_com_move.mp3");
    setEffectOnFrame(E002_C030_P200_INTRO_ANI2, 246-243, "e002_c030_p000_intro_sfx_com_move.mp3");
    setEffectOnFrame(E002_C030_P200_INTRO_ANI2, 265-243, "e002_c030_p100_intro_sfx_alpharobot.mp3");
    setEffectOnFrame(E002_C030_P200_INTRO_ANI2, 271-243, "e002_c030_p100_intro_sfx_alpharobot.mp3");
    setEffectOnFrame(E002_C030_P200_INTRO_ANI2, 386-243, "e002_c030_p000_intro_sfx_com_move.mp3");
    setEffectOnFrame(E002_C030_P200_INTRO_ANI3, 489-488, "e002_c030_p000_intro_sfx_com_move.mp3");

    animationManagerParseStart();
    
}

void E002_C030_P200_Intro::onViewLoaded()
{
    E002_Base_FlashIntro::onViewLoaded();
    
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_c030_snd_bgm_play02.mp3"), true);
}


void E002_C030_P200_Intro::onFlashIntroCompletedCallback()
{
    replaceSceneTransitionFadeOut(E002_C030_P210);
}

#pragma mark - navigation delegate

void E002_C030_P200_Intro::onTouchedNavigationButtonAtIndex()
{
    E002_Base_FlashIntro::onTouchedNavigationButtonAtIndex();
    
    E002_C030_P000_Index* _indexClass = E002_C030_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}
