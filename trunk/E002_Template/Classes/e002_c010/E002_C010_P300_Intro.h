//
//  E001_Base_P100_Intro.h
//  E002_Template
//
//  Created by whitems on 14. 1. 14..
//
//

#ifndef E002_C010_P300_Intro_h
#define E002_C010_P300_Intro_h


#include "cocos2d.h"
#include "E002_Base_FlashIntro.h"

using namespace cocos2d;

class E002_C010_P300_Intro : public E002_Base_FlashIntro {

    
public:
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    CREATE_FUNC(E002_C010_P300_Intro);
    
    virtual void onTouchedNavigationButtonAtIndex();
    virtual void onFlashIntroCompletedCallback();
};
#endif
