//
//  E002_C030_ImageGuide.cpp
//  SoundPhonics_Template
//
//  Created by whitems on 13. 7. 5..
//
//

#include "E002_C030_CompletePopup.h"

#include "CJUtils.h"
#include "E002_C030_P100_Intro.h"
#include "E002_C030_P200_Intro.h"
#include "E002_C030_P300_Intro.h"
#include "E002_C030_P000_Index.h"


#pragma mark - init
bool E002_C030_CompletePopup::init(int pageNumber)
{
    if (E002_Base_CompletePopup::init(pageNumber)) {
        return true;
    }
    
    return true;
}

void E002_C030_CompletePopup::onEnter()
{
    E002_Base_CompletePopup::onEnter();
}

void E002_C030_CompletePopup::onExit()
{
    E002_Base_CompletePopup::onExit();
}

#pragma mark - callback touch

void E002_C030_CompletePopup::onTouchedReplayBtn()
{
    CCLog("onTouch Replay %d", mPageNumber);
    E002_Base_CompletePopup::onTouchedReplayBtn();
    
    switch (mPageNumber) {
        case P100:
            replaceSceneTransitionFadeOut(E002_C030_P100_Intro);
            break;
        case P200:
            replaceSceneTransitionFadeOut(E002_C030_P200_Intro);
            break;
        case P300:
            replaceSceneTransitionFadeOut(E002_C030_P300_Intro);
            break;
        default:
            break;
    }
}

void E002_C030_CompletePopup::onTouchedNextBtn()
{
    CCLog("onTouch Next");
    E002_Base_CompletePopup::onTouchedNextBtn();
    
    switch (mPageNumber) {
        case P100:
            replaceSceneTransitionFadeOut(E002_C030_P200_Intro);
            break;
        case P200:
            replaceSceneTransitionFadeOut(E002_C030_P300_Intro);
            break;
        case P300:
            //temp
            replaceSceneTransitionFadeOut(E002_C030_P000_Index);
            break;
        default:
            break;
    }
}



