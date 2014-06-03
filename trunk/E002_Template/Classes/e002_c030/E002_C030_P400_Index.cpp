//
//  E002_C030_P400_Index.cpp
//  SoundPhonics_Template
//
//  Created by whitems on 13. 5. 8..
//
//

#include "E002_C030_P400_Index.h"
#include "E002_C030_P420_CompletePopup.h"
#include "E002_C030_P410_Intro.h"
#include "E002_C030_P000_Index.h"


bool E002_C030_P400_Index::init()
{
    if (!E002_Base_P400_Index::init()) {
        return false;
    }

    return true;
}

void E002_C030_P400_Index::onEnter()
{
    E002_Base_P400_Index::onEnter();
    onViewLoad();
}

void E002_C030_P400_Index::onExit()
{
    E002_Base_P400_Index::onExit();
}


void E002_C030_P400_Index::onViewLoad()
{
    E002_Base_P400_Index::onViewLoad();
}

void E002_C030_P400_Index::onViewLoaded()
{
    E002_Base_P400_Index::onViewLoaded();
}

void E002_C030_P400_Index::showCompletePopup()
{
    E002_C030_P420_CompletePopup *cPopup = new E002_C030_P420_CompletePopup();
    cPopup->init(true);
    addChild(cPopup, kDepth10_guide);
    
    cPopup->showPopup(this);
    cPopup->showCompletePopup();
    cPopup->setFlashDataPool(getAllDatapool());
}

void E002_C030_P400_Index::showDiaryIntro()
{
    replaceSceneTransitionFadeOut(E002_C030_P410_Intro);
}

void E002_C030_P400_Index::onTouchedNavigationButtonAtIndex()
{
    E002_Base_P400_Index::onTouchedNavigationButtonAtIndex();
    
    E002_C030_P000_Index* _indexClass = E002_C030_P000_Index::create();
    _indexClass->init();
    _indexClass->setIndexDelegate(this);
    _indexClass->showIndex(this, _indexClass);
    addChild(_indexClass, kDepth11_Index);
}