//
//  E002_C030_CompletePopup.h
//  SoundPhonics_Template2
//
//  Created by whitems on 13. 7. 5..
//
//

#ifndef SoundPhonics_Template_E002_C030_CompletePopup_h
#define SoundPhonics_Template_E002_C030_CompletePopup_h


#include "E002_Base_P420_CompletePopup.h"
#include "E002_Base_Define.h"

class E002_C030_P420_CompletePopup : public E002_Base_P420_CompletePopup
{
private:

    CCDictionary*                              m_psdDictionary;
    
public:
    
    ~E002_C030_P420_CompletePopup(){};
    E002_C030_P420_CompletePopup(){};
    
    
    virtual bool init(bool fromIndex);
    virtual void onEnter();
    virtual void onExit();
    
    //user function
    virtual void onTouchedReworkBtn();
    virtual void onTouchedFinishBtn();
};

#endif
