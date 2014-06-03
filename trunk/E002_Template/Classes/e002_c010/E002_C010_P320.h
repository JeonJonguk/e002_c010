//
//  E001_C010_P110_Q1.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#ifndef SoundPhonics_Template_E002_C010_P320_h
#define SoundPhonics_Template_E002_C010_P320_h


#include "E002_Base_Question.h"
#include "SSExampleItem.h"
#include "SSQuestionItem.h"
#include "E002_C010_SoundManager.h"

using namespace cocos2d;

class E002_C010_P320 : public E002_Base_Question
{
private:
    
    E002_C010_SoundManager*                         mSndManager;
    std::vector<std::vector<SSQuestionItem*> >      mQuestions;
    std::vector<std::vector<SSExampleItem*> >       mExamples;
    
    int                                             _oldCurrentStageIndex;
    int                                             _selectedExampleIndex;
    int                                             _selectedQuestionIndex;
    SSExampleItem*                                  _touchedExampleItem;

    
    std::string                                     mFirstNarration;
    std::string                                     mFirstNarration2;
    
    CCParallaxNode*                                 parallaxLayer;
    CJSprite*                                       layer1;
    CJSprite*                                       layer2;
    CJSprite*                                       layer3;
    CJSprite*                                       layer4;
    
    CJSprite*                                       basket_l;
    CJSprite*                                       basket_r;
    
    CCArray*                                        arrBalloons;
    
    int                                             _leftSuccessCount;
    int                                             _rightSuccessCount;
    int                                             _nTempQuestionIndex;
    int                                             _nTempExampleIndex;

public:
    
    ~E002_C010_P320();
    E002_C010_P320();

    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool onTouchBegan(CCPoint tp);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    
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
    
    CREATE_FUNC(E002_C010_P320);
    
    
    
    // feedback event
    void onSuccesses(CCNode *node, int tag = 0);
    void onFails(CCNode *node, int tag = 0);
    void onComplete();
    void onEnd();
    
    void intoTarget(CJSprite* sp, CCPoint tp);
    void checkAnswer(CCNode *node, int tag);
    void reorderBalloon(CJSprite* balloon);
    
    void setQuestions();
    void showQuestions();
    void setExamles();
    void showExamples();
    void resetValue();
    void setNextQuestions();
    void speakNarration(CCNode* node, std::string fileName);
    
    void start();
    void disappearAnimation();
    void checkSchedule();
    
    CJAnimation* _playAnimationAnison(std::string pAniKey, int count = -1);
    CJAnimation* _playAnimationChu(std::string pAniKey, int count = -1);
    void stopSpeakingAndLooping();
    
    void _doongDoong(CJSprite* balloon);
    CCAction* _doongDoong();
    void onUpParticle();
    
    void showGuide();
    void removeGuide();
    void completeToMoveHand(CCNode *node, int index);
    void completeFirstGuide();

    
    #pragma my util
    CJSprite* createSprite(std::string pStr);
    void _setPositionOutParent(CCNode* child, CCNode* newParent);
    void _safeRemoveFromParents(CCNode* pChild);
};

#endif
