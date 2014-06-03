//
//  E002_C030_CompletePopup.h
//  SoundPhonics_Template2
//
//  Created by whitems on 13. 7. 5..
//
//

#ifndef SoundPhonics_Template_E002_C030_P410_Write_h
#define SoundPhonics_Template_E002_C030_P410_Write_h


#include "E002_Base_P410_WritePopup.h"
#include "E002_Base_Define.h"

class E002_C030_P410_WritePopup : public E002_Base_P410_WritePopup
{
private:

    CCDictionary*                              m_psdDictionary;
    
public:
    
    ~E002_C030_P410_WritePopup();
    E002_C030_P410_WritePopup();
    
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
};

#endif
