//
//  E002_Base_CompletePopup.h
//  SoundPhonics_Template2
//
//  Created by whitems on 13. 7. 5..
//
//

#ifndef SoundPhonics_Template_E002_Base_CompletePopup_h
#define SoundPhonics_Template_E002_Base_CompletePopup_h


#include "CJPopup.h"
#include "E002_Base_Define.h"

class E002_Base_CompletePopup : public CJPopup
{
private:

    CCDictionary*                              m_psdDictionary;
    
public:
    int                                        mPageNumber;
    
    ~E002_Base_CompletePopup();
    E002_Base_CompletePopup();
    
    
    virtual bool init(int pageNumber);
    virtual void onEnter();
    virtual void onExit();
    
    //user function
    void showCompletePopup();
    
    void playBtnEffect();
    void setPopup();
    void setButtions();
    
    virtual void onTouchedNextBtn();
    virtual void onTouchedReplayBtn();
};

#endif
