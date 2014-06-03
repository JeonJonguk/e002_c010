//
//  E002_C030_P000_Index.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 8..
//
//

#ifndef SoundPhonics_Template_E002_C030_P400_Index_h
#define SoundPhonics_Template_E002_C030_P400_Index_h

#include "cocos2d.h"
#include "CJLayer.h"
#include "CJAnimationManager.h"
#include "CCScrollLayer.h"
#include "E002_Base_P400_Index.h"


class E002_C030_P400_Index : public E002_Base_P400_Index
{


public:

    ~E002_C030_P400_Index(){};
    E002_C030_P400_Index(){};

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    CREATE_FUNC(E002_C030_P400_Index);
 
    virtual void showCompletePopup();
    virtual void showDiaryIntro();
    
    void onTouchedNavigationButtonAtIndex();

};

#endif
