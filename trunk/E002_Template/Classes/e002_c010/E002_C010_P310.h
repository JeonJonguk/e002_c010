//
//  E001_C010_P110_Q1.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#ifndef SoundPhonics_Template_E002_C010_P310_h
#define SoundPhonics_Template_E002_C010_P310_h


#include "E002_Base_Question.h"
#include "SSExampleItem.h"
#include "SSQuestionItem.h"
#include "E002_C010_SoundManager.h"

using namespace cocos2d;

class E002_C010_P310 : public E002_Base_Question
{
private:
    
    E002_C010_SoundManager*                         mSndManager;
    std::vector<SSQuestionItem*>                    mQuestions;
    std::vector<std::vector<SSExampleItem*> >       mExamples;
    
    int                                             _selectedIndex;
    SSQuestionItem*                                 _currentQuestionItem;
    SSExampleItem*                                  _touchedExampleItem;
    int                                             _oldCurrentStageIndex;

    
    CCPoint                                         _touchGab;
    CCPoint                                         _touchGabCandy;
    
    std::string                                     mFirstNarration;
    
    
    CJSprite*                                       mShip;
    CJSprite*                                       mQueBg;
    CJSprite*                                       queBand_l;
    CJSprite*                                       queBand_r;
    CJSprite*                                       candy;
    float                                           fOriginDist_l;
    float                                           fOriginDist_r;
    
    bool                                            m_bIsQueBgTouched;
    CCPoint                                         pStick_l;
    CCPoint                                         pStick_r;
    
    CJSprite                                        *copyCandy;
    CCPoint                                         _copyCandyTargetPoint;
    
public:
    
    ~E002_C010_P310();
    E002_C010_P310();

    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool onTouchBegan(CCPoint tp);
    virtual void onTouchMoved(CCPoint tp);
	virtual void onTouchEnded(CCPoint tp);
    void runCopyCandy(CCPoint pt);
    void test();
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    void startFlashAnimation();
    virtual void onFirstNarration();
    virtual void onFirstNarrationEnd();
    virtual void onNarrationFinishedCallback(std::string fileName);
    virtual void OnLastFrame(CJAnimation* pAnimation);
    void flashSuccessFinishCallback(CJAnimation* pAnimation);
    void flashFailFinishCallback(CJAnimation* pAnimation);

    // Navigation DELEGATE functions.
    virtual void onTouchedNavigationButtonAtIndex();
    virtual void onTouchedNavigationButtonAtInfo();
    virtual void onTouchedNavigationButtonAtPrev();
    virtual void onTouchedNavigationButtonAtNext();
    virtual void onTouchedNavigationButtonAtReward();
    
    CREATE_FUNC(E002_C010_P310);
    
    
    
    // feedback event
    void onFishParticle();
    void onFishParticle2();

    void beforeSuccess();
    void onSuccesses(CCNode *node, int tag = 0);
    void onFails(CCNode *node, int tag = 0);
    void onComplete();
    void onEnd();
    
    void intoTarget(CJSprite* sp, CCPoint tp);
    void checkAnswer(CCNode *node);

    void setQuestions();
    void showQuestions();
    void setExamples();
    void showExamples();
    void showExamplesCallfunc_left();
    void showExamplesCallfunc_right();
    void resetValue();
    void setNextQuestions();
    
    void speakNarration(CCNode* node, std::string fileName);
    
    void start();
    void questionAppearStep1();
    void disappearAnimation();
    void checkSchedule();
    
    CJAnimation* _playAnimationAnison(std::string pAniKey, int count = -1);
    CJAnimation* _playAnimationChu(std::string pAniKey, int count = -1);
    void stopSpeakingAndLooping();
    
    
    void showGuide();
    void removeGuide();
    void completeToMoveHand(CCNode *node, int index);
    void completeFirstGuide();
    void guideScheduler();
    
    #pragma my util
    CJSprite* createSprite(std::string pStr);
    void _setPositionOutParent(CCNode* child, CCNode* newParent);
    void _safeRemoveFromParents(CCNode* pChild);
};

#endif
