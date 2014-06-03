//
//  E002_C010_P000_Index.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 8..
//
//

#include "E002_C010_P000_Index.h"
//#include "E002_C010_P110.h"
//#include "E002_C010_P210.h"
//#include "E002_C010_P310.h"
#include "E002_C010_P320.h"

#include "E002_C010_P100_Intro.h"
#include "E002_C010_P200_Intro.h"
#include "E002_C010_P300_Intro.h"

bool E002_C010_P000_Index::init()
{
    if (!E002_Base_P000_Index::init()) {
        return false;
    }

    return true;
}

void E002_C010_P000_Index::onEnter()
{
    E002_Base_P000_Index::onEnter();
    onViewLoad();
}

void E002_C010_P000_Index::onExit()
{
    E002_Base_P000_Index::onExit();
}


void E002_C010_P000_Index::onViewLoad()
{
    E002_Base_P000_Index::onViewLoad();
}

void E002_C010_P000_Index::onViewLoaded()
{
    E002_Base_P000_Index::onViewLoaded();
    
    //play bgm
    CJMultimedia::getInstance()->playBGM(getFilePath("snd","e002_C010_snd_bgm_main.mp3"), true);
    
}

#pragma mark - navigation delegate
void E002_C010_P000_Index::onTouchedNavigationButtonAtPackage()
{
    E002_Base_P000_Index::onTouchedNavigationButtonAtPackage();
   // replaceSceneTransitionFadeOut(E001_C010_P000_Cover);
    CJLog("go to package page.");
}


void E002_C010_P000_Index::goToSelectedPage(CCNode* sender, void* index)
{
    int pageNum = (int)index;
    CJLog("selected index = %d", pageNum);
    
    
    switch (pageNum) {
        case 0:
//            replaceSceneTransitionFadeOut(E002_C010_P000_PreStory);
            break;
        case 1:
             replaceSceneTransitionFadeOut(E002_C010_P100_Intro);
            break;
        case 2:
//            replaceSceneTransitionFadeOut(E002_C010_P000_Lecture);
            break;
        case 3:
            replaceSceneTransitionFadeOut(E002_C010_P200_Intro);
            break;
        case 4:
            replaceSceneTransitionFadeOut(E002_C010_P300_Intro);
            break;
        case 5:
            replaceSceneTransitionFadeOut(E002_C010_P320);
            break;
        case 6:
//            replaceSceneTransitionFadeOut(E001_C010_P500_Gate);
            break;
        default:
            break;
    }
}
