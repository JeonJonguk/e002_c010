//
//  E002_C030_P000_Intro.cpp
//  E002_Template
//
//  Created by whitems on 13. 5. 31..
//
//

#include "E002_C030_P000_PreStory.h"
#include "E002_C030_P100_Intro.h"
#include "E002_C030_P000_Index.h"

#pragma mark - init


bool E002_C030_P000_PreStory::init()
{
    if (!E002_Base_VideoLayer::init()) {
        return false;
    }
    
    return true;
}

void E002_C030_P000_PreStory::onEnter()
{
    E002_Base_VideoLayer::onEnter();
    onViewLoad();
}

void E002_C030_P000_PreStory::onExit()
{
    E002_Base_VideoLayer::onExit();
}

#pragma mark - load view

void E002_C030_P000_PreStory::onViewLoad()
{
    E002_Base_VideoLayer::onViewLoad();
    
     setVideoPath("e002_c030_p000_prestory.mp4");
}

void E002_C030_P000_PreStory::onViewLoaded()
{
    E002_Base_VideoLayer::onViewLoaded();
}


void E002_C030_P000_PreStory::onVideoFinishedCallback()
{
    replaceSceneTransitionFadeOut(E002_C030_P100_Intro);
}

void E002_C030_P000_PreStory::onIndexBtnTouch()
{ 
    replaceSceneTransitionFadeOut(E002_C030_P000_Index);
}

