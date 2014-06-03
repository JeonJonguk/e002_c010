//
//  E002_C030_P420_Diary.cpp
//  SoundPhonics_Template
//
//  Created by Soonho Hong on 13. 7. 10..
//
//

#include "E002_C030_P420_Diary.h"
#include "E002_Base_DrawLayer.h"
#include "CJLMSContentInterface.h"
#include "CJMenu.h"
#include "E002_C030_P400_Index.h"
#include "E002_C030_P420_CompletePopup.h"

  #pragma mark - init

E002_C030_P420_Diary::E002_C030_P420_Diary()
{
}

E002_C030_P420_Diary::~E002_C030_P420_Diary()
{
}   


bool E002_C030_P420_Diary::init()
{
	if (!E002_Base_P420_Diary::init()) {
		return false;
	}
	return true;
}


void E002_C030_P420_Diary::onEnter()
{
	E002_Base_P420_Diary::onEnter();
    onViewLoad();
}


void E002_C030_P420_Diary::onExit()
{
	E002_Base_P420_Diary::onExit();
}

#pragma mark - load view

void E002_C030_P420_Diary::onViewLoad()
{
	E002_Base_P420_Diary::onViewLoad();
    
    useCharacter(ANISON, CHU, BOOMBOOM, GRUMBIE, ALPHAROBOT, NULL);
}

void E002_C030_P420_Diary::onViewLoaded()
{
	E002_Base_P420_Diary::onViewLoaded();
}


void E002_C030_P420_Diary::selectIndexBtn()
{
    replaceSceneTransitionFadeOut(E002_C030_P400_Index);
}

void E002_C030_P420_Diary::showCompletePopup()
{
    E002_C030_P420_CompletePopup *cPopup = new E002_C030_P420_CompletePopup();
    cPopup->init(false);
    addChild(cPopup, kDepth10_guide);
    
    cPopup->showPopup(this);
    cPopup->showCompletePopup();
    
    sendPopupObject(cPopup);
}