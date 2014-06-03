//
//  E002_C030_CompletePopup.h
//  SoundPhonics_Template2
//
//  Created by whitems on 13. 7. 5..
//
//

#ifndef SoundPhonics_Template_E002_C030_CompletePopup_h
#define SoundPhonics_Template_E002_C030_CompletePopup_h


#include "E002_Base_CompletePopup.h"
#include "E002_Base_Define.h"

class E002_C030_CompletePopup : public E002_Base_CompletePopup
{
private:

    CCDictionary*                              m_psdDictionary;
    
public:
    
    ~E002_C030_CompletePopup(){};
    E002_C030_CompletePopup(){};
    
    
    virtual bool init(int pageNumber);
    virtual void onEnter();
    virtual void onExit();
    
    //user function
    virtual void onTouchedNextBtn();
    virtual void onTouchedReplayBtn();
};

#endif
