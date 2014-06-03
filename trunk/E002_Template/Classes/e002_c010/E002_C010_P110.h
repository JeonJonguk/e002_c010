//
//  E001_C010_P110_Q1.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#ifndef SoundPhonics_Template_E002_C010_P110_h
#define SoundPhonics_Template_E002_C010_P110_h


#include "E002_Base_Question.h"
#include "SSExampleItem.h"
#include "SSQuestionItem.h"
#include "E002_C010_SoundManager.h"

using namespace cocos2d;

class E002_C010_P110 : public E002_Base_Question
{
private:
    
    E002_C010_SoundManager*                         mSndManager;
    std::vector<SSQuestionItem*>                    mQuestions;
    int                                             _successCount;
    SSQuestionItem*                                 _currentQuestionItem;

    
    std::string                                     mFirstNarration;
    std::string                                     mFirstNarration2;
    
    CCArray*                                        _arrBuildings;

    CCParallaxNode*                                 parallaxLayer;
    CJSprite*                                       layer1;
    CJSprite*                                       layer2;
    CJSprite*                                       layer3; //flash layer
    CJSprite*                                       layer4;

//    int                                             nForLayer2Position = 0;
//    int                                             nForLayer1Position = 0;
    
    CJAnimation*                                    _lastFireworkAni;
    CJSprite*                                       mDimm;
    CJSprite*                                       magicE;
public:
    
    ~E002_C010_P110();
    E002_C010_P110();

    
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
    void flashSuccessFinishCallback(CJAnimation* pAnimation);
    void flashFailFinishCallback(CJAnimation* pAnimation);

    // Navigation DELEGATE functions.
    virtual void onTouchedNavigationButtonAtIndex();
    virtual void onTouchedNavigationButtonAtInfo();
    virtual void onTouchedNavigationButtonAtPrev();
    virtual void onTouchedNavigationButtonAtNext();
    virtual void onTouchedNavigationButtonAtReward();
    CREATE_FUNC(E002_C010_P110);
    
    
    
    // feedback event
    void onSuccesses(CCNode *node, int tag = 0);
    void onHalfSuccess(CCNode *node, int tag = 0);
    void onFails(CCNode *node, int tag = 0);
    void onComplete();
    void onEnd();
    
    void intoTarget(CJSprite* sp, CCPoint pt);
    void shootTheGun();
    void changeQuestionText(CCNode* sender, void* pData);
    void checkAnswer(CCNode *node);

    void setQuestions();
    void setSideQuestion();
    void showQuestions();
    void showExamples();
    void resetValue();
    void speakNarration(CCNode* node, std::string fileName);
    
    void start();
    void questionAppearStep1();
    void questionAppearStep2();
    void disappearAnimation();
    void checkSchedule();

    CJAnimation* _playAnimationAnison(std::string pAniKey, int count = -1);
    CJAnimation* _playAnimationGrumbie(std::string pAniKey, int count = -1);
    void stopSpeakingAndLooping();
    
    void playFirework();
    CJAnimation* _playFirework1();
    CJAnimation* _playFirework2();
    void lightingColorAnimation(CCNode* node);
    
    
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
