//
//  E002_C030_P000_Lecture.cpp
//  E002_Template
//
//  Created by whitems on 13. 5. 31..
//
//

#include "E002_C030_P000_Lecture.h"
#include "E002_C030_P000_Index.h"
#include "E002_C030_P210.h"

#pragma mark - init


bool E002_C030_P000_Lecture::init()
{
    if (!E002_Base_VideoLayer::init()) {
        return false;
    }
    
    return true;
}

void E002_C030_P000_Lecture::onEnter()
{
    E002_Base_VideoLayer::onEnter();
    onViewLoad();
}

void E002_C030_P000_Lecture::onExit()
{
    E002_Base_VideoLayer::onExit();
}

#pragma mark - load view

void E002_C030_P000_Lecture::onViewLoad()
{
    E002_Base_VideoLayer::onViewLoad();
    
     setVideoPath("e002_c030_p000_prestory.mp4", kTagNoramlType);
}

void E002_C030_P000_Lecture::onViewLoaded()
{
    E002_Base_VideoLayer::onViewLoaded();
}


void E002_C030_P000_Lecture::onVideoFinishedCallback()
{
    replaceSceneTransitionFadeOut(E002_C030_P210);
}

void E002_C030_P000_Lecture::onIndexBtnTouch()
{ 
    replaceSceneTransitionFadeOut(E002_C030_P000_Index);
}

