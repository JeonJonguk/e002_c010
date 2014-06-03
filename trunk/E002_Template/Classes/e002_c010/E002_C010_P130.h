//
//  E001_C010_P110_Q1.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#ifndef SoundPhonics_Template_E002_C010_P130_h
#define SoundPhonics_Template_E002_C010_P130_h


#include "E002_Base_Reward.h"
#include "SSExampleItem.h"
#include "SSQuestionItem.h"
#include "E002_C010_SoundManager.h"

using namespace cocos2d;

class E002_C010_P130 : public E002_Base_Reward
{
private:
    
    E002_C010_SoundManager*                         mSndManager;
    std::string                                     mFirstNarration;
    CJSprite*                                       mDimm;
    
    CCRenderTexture                                 *m_target;
    CJSprite                                        *mask;
    CCArray                                         *arrMasks;
    
    int                                             m_nMaxStageCount;
    int                                             m_nCurrentStageIndex;
    
public:
    
    ~E002_C010_P130();
    E002_C010_P130();

    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool onTouchBegan(CCPoint tp);
    virtual void onTouchMoved(CCPoint tp);
	virtual void onTouchEnded(CCPoint tp);
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    virtual void startFlashAnimation();
    
    virtual void onFirstNarration();
    virtual void onFirstNarrationEnd();
    virtual void onNarrationFinishedCallback(std::string fileName);
    virtual void OnLastFrame(CJAnimation* pAnimation);

    // Navigation DELEGATE functions.
    virtual void onTouchedNavigationButtonAtIndex();
    virtual void onTouchedNavigationButtonAtInfo();
    virtual void onTouchedNavigationButtonAtPrev();
    virtual void onTouchedNavigationButtonAtNext();
    
    CREATE_FUNC(E002_C010_P130);
    
    
    
    // feedback event
    void onSuccesses(CCNode *node, int tag = 0);
    void onComplete();
    void completeFirework();
    void onEnd();
    
    void intoTarget(CJSprite* sp, CCPoint pt);

    void setQuestions();
    void showQuestions();
    void showExamples();
    void resetValue();
    
    void start();
    void disappearAnimation();

#pragma mark - mask
    void setBrush();
    void completeMasking(CJSprite* sp);
    void showMaskRenderingSchedule(float dt);
    void endMaskRenderingSchedule(CCNode* sender);
    
    CJAnimation* _playAnimationAnison(std::string pAniKey, int count = -1);
    CJAnimation* _playFirework(CCPoint pos, int tag);
    
    void ballBackAnimation(CCNode* sender);
    void ballAnimation(CCNode* sender);
    
    void runSequence(CJSprite* parent, std::string str, float delay);
    
    
    virtual void completeFirstGuide();
    void showCompletePopup();

    
    #pragma my util
    CJSprite* createSprite(std::string pStr);
    void _setPositionOutParent(CCNode* child, CCNode* newParent);
    void _safeRemoveFromParents(CCNode* pChild);
};

#endif
