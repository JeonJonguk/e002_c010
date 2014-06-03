//
//  E002_C010_P000_Index.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 8..
//
//

#ifndef SoundPhonics_Template_E002_C010_P000_Index_h
#define SoundPhonics_Template_E002_C010_P000_Index_h

#include "cocos2d.h"
#include "CJLayer.h"
#include "CJAnimationManager.h"
#include "CCScrollLayer.h"
#include "E002_Base_P000_Index.h"

using namespace cocos2d;

class E002_C010_P000_Index : public E002_Base_P000_Index
{


public:

    ~E002_C010_P000_Index(){};
    E002_C010_P000_Index(){};

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    CREATE_FUNC(E002_C010_P000_Index);

#pragma mark - navigation delegate
    virtual void onTouchedNavigationButtonAtPackage();
 
//    void speakTitleNarration(CCNode* sender, void* index);
    void goToSelectedPage(CCNode* sender, void* index);

};

#endif
