//
//  E002_C030_P300_Ending.cpp
//  E002_Template
//
//  Created by whitems on 13. 5. 31..
//
//

#include "E002_C030_P300_Ending.h"
#include "E002_C030_P000_Index.h"
#include "E002_C030_CompletePopup.h"
#pragma mark - init


bool E002_C030_P300_Ending::init()
{
    if (!E002_Base_VideoLayer::init()) {
        return false;
    }
    
    return true;
}

void E002_C030_P300_Ending::onEnter()
{
    E002_Base_VideoLayer::onEnter();
    onViewLoad();
}

void E002_C030_P300_Ending::onExit()
{
    E002_Base_VideoLayer::onExit();
}

#pragma mark - load view

void E002_C030_P300_Ending::onViewLoad()
{
    E002_Base_VideoLayer::onViewLoad();
    
     setVideoPath("e002_c030_p300_ending.mp4");
}

void E002_C030_P300_Ending::onViewLoaded()
{
    E002_Base_VideoLayer::onViewLoaded();
}


void E002_C030_P300_Ending::onVideoFinishedCallback()
{
    CJUtils::performSelector(this, callfunc_selector(E002_C030_P300_Ending::showCompletePopup), 0.5);
}

void E002_C030_P300_Ending::onIndexBtnTouch()
{ 
    replaceSceneTransitionFadeOut(E002_C030_P000_Index);
}

void E002_C030_P300_Ending::showCompletePopup()
{
    E002_C030_CompletePopup *cPopup = new E002_C030_CompletePopup();
    cPopup->init(P300);
    addChild(cPopup, kDepth10_guide);
    
    cPopup->showPopup(this);
    cPopup->showCompletePopup();
}
