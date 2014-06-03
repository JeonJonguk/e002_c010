//
//  E002_Base_P410_Diary.h
//  SoundPhonics_Template
//
//  Created by Soonho Hong on 13. 7. 10..
//
//

#ifndef __SoundPhonics_Template__E002_C030_P420_Diary__
#define __SoundPhonics_Template__E002_C030_P420_Diary__

#include "cocos2d.h"
#include "CJLayer.h"
#include "CJAnimationManager.h"
#include "E002_Base_P420_Diary.h"

using namespace cocos2d;

class E002_C030_P420_Diary : public E002_Base_P420_Diary
{
    
public:
    ~E002_C030_P420_Diary();
    E002_C030_P420_Diary();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    CREATE_FUNC(E002_C030_P420_Diary);
    
private:
    
    virtual void selectIndexBtn();
    virtual void showCompletePopup();
    
};

#endif