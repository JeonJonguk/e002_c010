//
//  E002_C030_P510_Song.cpp
//  E002_Template
//
//  Created by whitems on 13. 5. 31..
//
//

#include "E002_C030_P510_Song.h"

#pragma mark - init


bool E002_C030_P510_Song::init()
{
    if (!E002_Base_VideoLayer::init()) {
        return false;
    }
    
    return true;
}

void E002_C030_P510_Song::onEnter()
{
    E002_Base_VideoLayer::onEnter();
    onViewLoad();
}

void E002_C030_P510_Song::onExit()
{
    E002_Base_VideoLayer::onExit();
}

#pragma mark - load view

void E002_C030_P510_Song::onViewLoad()
{
    E002_Base_VideoLayer::onViewLoad();
    
     setVideoPath("e001_c010_p000_intro.mp4", kTagSongType);
}

void E002_C030_P510_Song::onViewLoaded()
{
    E002_Base_VideoLayer::onViewLoaded();
}


void E002_C030_P510_Song::onVideoFinishedCallback()
{
    //replaceSceneTransitionFadeOut(E001_C010_P000_Chant);
}

void E002_C030_P510_Song::onIndexBtnTouch()
{ 
    //replaceSceneTransitionFadeOut(E001_C010_P000_Index);
}

