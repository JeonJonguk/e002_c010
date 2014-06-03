//
//  E001_C010_P110_Q1.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#ifndef SoundPhonics_Template_E002_C030_P310_h
#define SoundPhonics_Template_E002_C030_P310_h


#include "E002_Base_Question.h"
#include "E002_Base_ExampleItem.h"
#include "E002_C030_SoundManager.h"

#define ONE_QUETION_THEME 1
#define TWO_QUETION_THEME 2
#define THREE_QUETION_THEME 3

using namespace cocos2d;

class E002_C030_P310 : public E002_Base_Question
{
private:
    
    std::vector<std::vector<E002_Base_ExampleItem*>*>        *mExamples;
    std::vector<std::vector<std::vector<std::string>*>*>     *mQuestions;
    std::vector<CJSprite*>                                   *mTargets;
    std::vector<int>                                         *mCompleteTargetTags;
    std::string                                              mWrongSound;
    
    CJAnimationCharacter *mMeerKat;
    CJAnimationCharacter *mAnison;
    
    CCSprite *guideCharacter;
    CCSprite *feedbackCharacter;
    
    CCPoint mTouchedPointGab;
    CCPoint mTargetPoint;
    
    int mSelectedCount;
    int mSelectedTag;
    int mSuccessCount;
    int mExampleSelectIndex;
    int mCurrentQuestionTheme;
    int mFailCount;
    
    E002_C030_SoundManager *mSndManager;
    
    std::string mSuccessNarrationSnd;
    std::string mWrongNarrationSnd;
    std::string mFirstNarration;
    
    bool mReadyQuestion;
    void setReadyQuestion(CCNode* node, bool isReady);
    bool mPlayingGuideNarration;

public:
    
    ~E002_C030_P310();
    E002_C030_P310();

    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void startFlashAnimation();
    
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
    virtual void onTouchedNavigationButtonAtReward();
    virtual void onTouchedNavigationButtonAtClose();
    
    CREATE_FUNC(E002_C030_P310);
    
    // feedback event
    void onSuccesses(CCNode *node, int tag = 0);
    void onFails(CCNode *node, int tag = 0);
    virtual void onComplete();
    virtual void onExamplesTouched(int index);
    
    void intoTarget(CJSprite* sp, CCNode *target);
    void checkAnswer(CCNode *node, int targetTag);
    
    void setQuestions();
    void showQuestion(int index, CJSprite *queText, CJSprite *light, CJSprite *question, float delay);
    
    void showExamples();
    
    void resetValue();
    void speakNarration(CCNode* node, const char* fileName);
    
    //sound
    virtual void playAppearanceExamplesSound(CCNode* sender, void* index);
    void playQuestionSound(CCNode* node, void* index);
    void playWrongSound(int tag);
    void playEffect(CCNode *node, int index);
    
    void createQuestionBG();
    void createTarget();
    void showSuccessTexture(CCNode *node, int tag);
    void playWheel();
    void showSuccessText(CCNode *node, int tag);
    void removeTexture(int tag);
    
    void showSuccessCharacterMotion(CCNode *node, int index);
    void showWrongCharacterMotion(CCNode *node, int index);
    
    void showGuideCharacterLooping();
    
    virtual void completeToGetRewardItem();
    
    //Guide
    virtual void showGuide();
    virtual void removeGuide();
    virtual void completeToMoveHand(CCNode *node, int index);
    virtual void completeFirstGuide();
};

#endif
