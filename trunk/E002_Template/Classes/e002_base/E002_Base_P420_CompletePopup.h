//
//  E002_Base_CompletePopup.h
//  SoundPhonics_Template2
//
//  Created by whitems on 13. 7. 5..
//
//

#ifndef SoundPhonics_Template_E002_Base_P420_CompletePopup_h
#define SoundPhonics_Template_E002_Base_P420_CompletePopup_h


#include "CJPopup.h"
#include "E002_Base_Define.h"
#include "CJAnimationManager.h"
#include "E002_Base_DiaryAnimationInfo.h"

class E002_Base_P420_CompletePopup : public CJPopup, CJAnimationManager
{
private:

    CCDictionary*                              m_psdDictionary;
    int                                        mCurrentDiary;
    std::vector<E002_Base_DiaryAnimationInfo*>            *mShowingAnimation;
    bool                                       m_isFromIndex;
public:
    
    ~E002_Base_P420_CompletePopup();
    E002_Base_P420_CompletePopup();
    
    
    virtual bool init(bool fromIndex);
    virtual void onEnter();
    virtual void onExit();
    
    //user function
    void showCompletePopup();
    
    void playBtnEffect();
    void setPopup();
    void setButtions();
    void showPicture();
    void setFlashDataPool(STL_MULTIMAP_DATAPOOL datapool);
    void showCharacters();
    void resizeScalePicture();
    
    void _onTouchedReworkBtn();
    void _onTouchedFinishBtn();
    
    virtual void onTouchedReworkBtn();
    virtual void onTouchedFinishBtn();
    
    virtual void onNarrationFinishedCallback(std::string fileName);

    

};

#endif
