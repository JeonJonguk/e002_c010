//
//  E002_C030_ImageGuide.cpp
//  SoundPhonics_Template
//
//  Created by whitems on 13. 7. 5..
//
//

#include "E002_C030_P410_Intro.h"
#include "E002_C030_P410_WritePopup.h"
#include "E002_C030_P420_Diary.h"
#include "CJUtils.h"
#include "E002_C030_P400_Index.h"



#pragma mark - init
bool E002_C030_P410_Intro::init()
{
    if (E002_Base_P410_Intro::init()) {
        return true;
    }
    
    return true;
}

void E002_C030_P410_Intro::onEnter()
{
    E002_Base_P410_Intro::onEnter();
    onViewLoad();
}

void E002_C030_P410_Intro::onExit()
{
    E002_Base_P410_Intro::onExit();
}

void E002_C030_P410_Intro::onViewLoad()
{
    E002_Base_P410_Intro::onViewLoad();
    
    CJPsdParser::parseToPsdJSON("e002_c030_p410_intro.json", &m_psdDictionary);
    
    std::vector<float> *sentencesDelays = new std::vector<float>();
    
    if (getCurrentDiaryNumber() == DIARY_1)
    {
        sentencesDelays->push_back(0.0);
        sentencesDelays->push_back(0.3);
        sentencesDelays->push_back(0.6);
        sentencesDelays->push_back(1.0);
    }
    else if (getCurrentDiaryNumber() == DIARY_2)
    {
        sentencesDelays->push_back(0.0);
        sentencesDelays->push_back(0.2);
        sentencesDelays->push_back(0.4);
        sentencesDelays->push_back(0.6);
        sentencesDelays->push_back(0.9);
    }
    else if (getCurrentDiaryNumber() == DIARY_3)
    {
        sentencesDelays->push_back(0.0);
        sentencesDelays->push_back(0.4);
        sentencesDelays->push_back(0.8);
        sentencesDelays->push_back(1.1);
        sentencesDelays->push_back(1.4);
    }
    else if (getCurrentDiaryNumber() == DIARY_4)
    {
        sentencesDelays->push_back(0.0);
        sentencesDelays->push_back(0.4);
        sentencesDelays->push_back(0.6);
        sentencesDelays->push_back(0.8);
        sentencesDelays->push_back(1.6);
        sentencesDelays->push_back(1.8);
    }

    setSentencesDelays(sentencesDelays);
    
}

void E002_C030_P410_Intro::onViewLoaded()
{
    E002_Base_P410_Intro::onViewLoaded();
}

void E002_C030_P410_Intro::onTouchedBlank()
{
    E002_Base_P410_Intro::onTouchedBlank();
    
    E002_C030_P410_WritePopup *cPopup = new E002_C030_P410_WritePopup();
    cPopup->init();
    addChild(cPopup, kDepth10_guide, 323);
    
    cPopup->showPopup(this);
    cPopup->showWritePopup();
    
}

void E002_C030_P410_Intro::removeWritePopup()
{
     removeChildByTag(323);
}

void E002_C030_P410_Intro::replaceDrawScene()
{
    replaceSceneNoTransition(E002_C030_P420_Diary);
}

void E002_C030_P410_Intro::selectIndexBtn()
{
    replaceSceneTransitionFadeOut(E002_C030_P400_Index);
}
