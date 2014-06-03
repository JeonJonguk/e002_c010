//
//  E002_C030_CompletePopup.h
//  SoundPhonics_Template2
//
//  Created by whitems on 13. 7. 5..
//
//

#ifndef SoundPhonics_Template_E002_Base_P410_Intro_h
#define SoundPhonics_Template_E002_Base_P410_Intro_h


#include "CJLayer.h"
#include "E002_Base_Define.h"

class E002_Base_P410_Intro : public CJLayer
{
public:
    CCDictionary*                              m_psdDictionary;

private:

    int                                        mCurrentDiary;
    CCPoint                                    mTargetPoint;
    bool                                       mCompleteWrite;
    
    CJSprite                                  *mTouchingWordSp;
    CCPoint                                    mTouchedPointGab;
    CCPoint                                    mWordOriginalPosition;
    std::vector<float>                        *mSentencesDelays;

public:
    
    E002_Base_P410_Intro();
    ~E002_Base_P410_Intro();
    
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void createIndexBtn();
    virtual void selectIndexBtn(){};
    
    virtual void onTouchedBlank();
    
    std::string getContentID(std::string resource);
    void playBtnEffect();
    
    void addWriteCompleteObserver();
    void removeWriteCompleteObserver();
    
    void completeWriteCallback();
    void closeWriteCallback();
    void intoBlank();
    void showParticle();
    void changeWord();
    int getCurrentDiaryNumber();
    
    virtual void replaceDrawScene(){};
    virtual void onNarrationFinishedCallback(std::string fileName);
    virtual void removeWritePopup(){};
    
    void setSentencesDelays(std::vector<float> *sentencesDelays);
};

#endif
