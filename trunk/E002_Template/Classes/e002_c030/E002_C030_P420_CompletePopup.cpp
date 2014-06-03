//
//  E002_C030_ImageGuide.cpp
//  SoundPhonics_Template
//
//  Created by whitems on 13. 7. 5..
//
//

#include "E002_C030_P420_CompletePopup.h"

#include "CJUtils.h"
#include "E002_C030_P100_Intro.h"
#include "E002_C030_P200_Intro.h"
#include "E002_C030_P300_Intro.h"
#include "E002_C030_P400_Index.h"
#include "E002_C030_P410_Intro.h"


#pragma mark - init
bool E002_C030_P420_CompletePopup::init(bool fromIndex)
{
    if (E002_Base_P420_CompletePopup::init(fromIndex)) {
        return true;
    }
    
    return true;
}

void E002_C030_P420_CompletePopup::onEnter()
{
    E002_Base_P420_CompletePopup::onEnter();
}

void E002_C030_P420_CompletePopup::onExit()
{
    E002_Base_P420_CompletePopup::onExit();
}

#pragma mark - callback touch

void E002_C030_P420_CompletePopup::onTouchedReworkBtn()
{
    E002_Base_P420_CompletePopup::onTouchedReworkBtn();
    
    replaceSceneTransitionFadeOut(E002_C030_P410_Intro);
}

void E002_C030_P420_CompletePopup::onTouchedFinishBtn()
{

    E002_Base_P420_CompletePopup::onTouchedFinishBtn();
    
    replaceSceneTransitionFadeOut(E002_C030_P400_Index);
 
}



