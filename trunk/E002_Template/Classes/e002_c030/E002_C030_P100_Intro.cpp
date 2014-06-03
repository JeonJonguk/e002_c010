//
//  E002_C030_P100_Intro.cpp
//  E002_Template
//
//  Created by whitems on 13. 5. 31..
//
//

#include "E002_C030_P100_Intro.h"
#include "E002_C030_P000_Index.h"
#include "E002_Base_Define.h"
#include "E002_C030_P110.h"

#pragma mark - init

#define E002_C030_P100_INTRO_ANI1 "e002_c030_p100_intro_flash_p01_action"
#define E002_C030_P100_INTRO_ANI2 "e002_c030_p100_intro_flash_p02_action"
#define E002_C030_P100_INTRO_ANI3 "e002_c030_p100_intro_flash_p03_action"


bool E002_C030_P100_Intro::init()
{
    if (!E002_Base_FlashIntro::init()) {
        return false;
    }
    
    return true;
}

void E002_C030_P100_Intro::onEnter()
{
    E002_Base_FlashIntro::onEnter();
    onViewLoad();
}

void E002_C030_P100_Intro::onExit()
{
    E002_Base_FlashIntro::onExit();
}

#pragma mark - load view

void E002_C030_P100_Intro::onViewLoad()
{
    E002_Base_FlashIntro::onViewLoad();

    initWithColor(ccc4(25, 54, 88, 255));
    
    setAnimationFile("e002_c030_p100_flash_intro_sheets.json", "e002_c030_p100_flash_intro_animations.json", FLASH_INTRO_DATEPOOL_KEY);
    
    setCutAnimationName(E002_C030_P100_INTRO_ANI1,
                        E002_C030_P100_INTRO_ANI2,
                        E002_C030_P100_INTRO_ANI3,
                        NULL);
    
    setNarrationOnFrame(E002_C030_P100_INTRO_ANI1, 2, "e002_c030_p100_intro_snd_01_bb.mp3");
    setNarrationOnFrame(E002_C030_P100_INTRO_ANI1, 56, "e002_c030_p100_intro_snd_02_mk.mp3");
    setNarrationOnFrame(E002_C030_P100_INTRO_ANI1, 164, "e002_c030_p100_intro_snd_03_as.mp3");
    setNarrationOnFrame(E002_C030_P100_INTRO_ANI2, 269-248, "e002_c030_p100_intro_snd_04_as.mp3");
    setNarrationOnFrame(E002_C030_P100_INTRO_ANI3, 350-329, "e002_c030_p100_intro_snd_05_as.mp3");
    setNarrationOnFrame(E002_C030_P100_INTRO_ANI3, 482-329, "e002_c030_p100_intro_snd_06_as.mp3");
   
    setEffectOnFrame(E002_C030_P100_INTRO_ANI1, 45, "e002_c030_p000_intro_sfx_com_move.mp3");
    setEffectOnFrame(E002_C030_P100_INTRO_ANI1, 151, "e002_c030_p000_intro_sfx_com_move.mp3");
    setEffectOnFrame(E002_C030_P100_INTRO_ANI2, 252-248, "e002_c030_p000_intro_sfx_com_move.mp3");
    setEffectOnFrame(E002_C030_P100_INTRO_ANI2, 269-248, "e002_c030_p100_intro_sfx_surprise.mp3");
    setEffectOnFrame(E002_C030_P100_INTRO_ANI3, 331-329, "e002_c030_p000_intro_sfx_com_move.mp3");
    setEffectOnFrame(E002_C030_P100_INTRO_ANI3, 365-329, "e002_c030_p100_intro_sfx_alpharobot.mp3");
    setEffectOnFrame(E002_C030_P100_INTRO_ANI3, 372-329, "e002_c030_p100_intro_sfx_alpharobot.mp3");
    setEffectOnFrame(E002_C030_P100_INTRO_ANI3, 420-329, "e002_c030_p100_intro_sfx_alpharobot.mp3");
    setEffectOnFrame(E002_C030_P100_INTRO_ANI3, 426-329, "e002_c030_p100_intro_sfx_alpharobot.mp3");
    setEffectOnFrame(E002_C030_P100_INTRO_ANI3, 470-329, "e002_c030_p000_intro_sfx_com_move.mp3");

    
    animationManagerParseStart();
    
}

void E002_C030_P100_Intro::onViewLoaded()
{
    E002_Base_FlashIntro::onViewLoaded();
    
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_c030_snd_bgm_play01.mp3"), true);
}

void E002_C030_P100_Intro::onFlashIntroCompletedCallback()
{
    replaceSceneTransitionFadeOut(E002_C030_P110);
}

#pragma mark - navigation delegate

void E002_C030_P100_Intro::onTouchedNavigationButtonAtIndex()
{
    E002_Base_FlashIntro::onTouchedNavigationButtonAtIndex();
    
    E002_C030_P000_Index* _indexClass = E002_C030_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}
