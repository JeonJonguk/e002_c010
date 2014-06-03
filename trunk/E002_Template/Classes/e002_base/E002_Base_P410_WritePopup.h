//
//  E002_Base_CompletePopup.h
//  SoundPhonics_Template2
//
//  Created by whitems on 13. 7. 5..
//
//

#ifndef SoundPhonics_Template_E002_Base_P410_WritePopup_h
#define SoundPhonics_Template_E002_Base_P410_WritePopup_h


#include "CJPopup.h"
#include "E002_Base_Define.h"

class E002_Base_P410_WritePopup : public CJPopup
{
private:

    CCDictionary*                              m_psdDictionary;
    CCDictionary*                              m_childPsdDictionary;
    
    int                                        mCurrentDiary;

public:
    
    ~E002_Base_P410_WritePopup();
    E002_Base_P410_WritePopup();
    
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    void setChildDictionary(CCDictionary *dictionary);
    
    //user function
    void showWritePopup();
    void setPopup();
    void setButtons();
    void playBtnEffect();
    
    void onTouchedCloseBtn();
    void onTouchedRewriteBtn();
    void _onTouchedOKBtn();
    
    virtual void onTouchedOKBtn();
    
    std::string getContentID(std::string resource);
    void onNarrationFinishedCallback(std::string fileName);
};

#endif
