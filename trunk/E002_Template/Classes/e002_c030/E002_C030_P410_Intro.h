//
//  E002_C030_CompletePopup.h
//  SoundPhonics_Template2
//
//  Created by whitems on 13. 7. 5..
//
//

#ifndef SoundPhonics_Template_E002_C030_P410_Intro_h
#define SoundPhonics_Template_E002_C030_P410_Intro_h


#include "E002_Base_P410_Intro.h"
#include "E002_Base_Define.h"

class E002_C030_P410_Intro : public E002_Base_P410_Intro
{
private:

public:
    
    ~E002_C030_P410_Intro(){};
    E002_C030_P410_Intro(){};
    
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    virtual void onTouchedBlank();
    
    CREATE_FUNC(E002_C030_P410_Intro);
    
    virtual void replaceDrawScene();
    virtual void selectIndexBtn();
    virtual void removeWritePopup();

};

#endif
