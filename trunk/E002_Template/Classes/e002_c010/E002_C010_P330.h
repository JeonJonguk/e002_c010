//
//  E001_C010_P110_Q1.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#ifndef SoundPhonics_Template_E002_C010_P330_h
#define SoundPhonics_Template_E002_C010_P330_h


#include "E002_Base_Reward.h"
#include "SSExampleItem.h"
#include "SSQuestionItem.h"
#include "E002_C010_SoundManager.h"

using namespace cocos2d;

class E002_C010_P330 : public E002_Base_Reward
{
private:
    
    E002_C010_SoundManager*                         mSndManager;
    std::string                                     mFirstNarration;
    
    int                                             m_nMaxStageCount;
    int                                             m_nCurrentStageIndex;
    
    CJSprite                                        *mBody;
    bool                                            bIsStep2;
    
public:
    
    ~E002_C010_P330();
    E002_C010_P330();

    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool onTouchBegan(CCPoint tp);
    virtual void onTouchMoved(CCPoint tp);
	virtual void onTouchEnded(CCPoint tp);
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    virtual void onFirstNarration();
    virtual void onFirstNarrationEnd();
    virtual void onNarrationFinishedCallback(std::string fileName);
    virtual void OnLastFrame(CJAnimation* pAnimation);

    // Navigation DELEGATE functions.
    virtual void onTouchedNavigationButtonAtIndex();
    virtual void onTouchedNavigationButtonAtInfo();
    virtual void onTouchedNavigationButtonAtPrev();
    virtual void onTouchedNavigationButtonAtNext();
    
    CREATE_FUNC(E002_C010_P330);
    
    
    
    // feedback event
    void onSuccesses(CCNode *node, int tag = 0);
    void onComplete();
    void onEnd();
    
    void intoTarget(CJSprite* sp, int tag);

    void setQuestions();
    void showQuestions();
    void showExamples();
    void resetValue();
    
    void start();
    void disappearAnimation();
    
    void step2();
    void openParachute();
    void bodyAfterOpenParachuteAnimation();
    
    void _doongDoong(CJSprite* balloon);
    void _eyesAnimation(CCPoint tp, bool bWithAction = false);
    void _eyesStop();
    void _mouseAnimation();
    void _mouseStop();
    void _eyebrowAnimation();
    void _bodyDownAnimation();
    void _whiteningAnimation();
    void cloudHorizontal(CJSprite* pCloud, int pVec);
    void cloudVertical(CJSprite* pCloud, int duration);
//    void birdHorizontal(CJSprite* sp, int duration);
    void birdVertical(CJSprite* sp, int duration);

    virtual void completeFirstGuide();
    void showCompletePopup();

    
    #pragma my util
    CJSprite* createSprite(std::string pStr);
    void _setPositionOutParent(CCNode* child, CCNode* newParent);
    void _safeRemoveFromParents(CCNode* pChild);
};

#endif
