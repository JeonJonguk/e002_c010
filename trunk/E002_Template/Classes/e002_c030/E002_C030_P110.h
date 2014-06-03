//
//  E001_C010_P110_Q1.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#ifndef SoundPhonics_Template_E002_C030_P110_h
#define SoundPhonics_Template_E002_C030_P110_h


#include "E002_Base_Question.h"
#include "E002_Base_ExampleItem.h"
#include "E002_C030_SoundManager.h"

using namespace cocos2d;

class E002_C030_P110 : public E002_Base_Question
{
private:
    
    std::vector<std::vector<E002_Base_ExampleItem*>*>        *mExamples;
    std::vector<std::vector<std::vector<std::string>*>*>     *mSeqImgs;
    std::vector<int> *mSelectTag;
    std::vector<int> *mCompleteTag;
    
    CJAnimationCharacter *mMeerKat;
    CJAnimationCharacter *mAnison;
    
    CCSprite *guideCharacter;
    CCSprite *feedbackCharacter;
    
    int mSelectedCount;
    int mCorrectedTag;
    int mSelectedTag;
    int mSuccessCount;
    int mFailCount;
    bool mPlayingGuideNarration;
    
    E002_C030_SoundManager *mSndManager;
    
    bool mCompleteQuestion;
    std::string mSuccessNarrationSnd;
    std::string mWrongNarrationSnd;
    std::string mFirstNarration;
    bool mReadyQuestion;
    void setReadyQuestion(CCNode* node, bool isReady);
    
public:
    
    ~E002_C030_P110();
    E002_C030_P110();

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
    
    CREATE_FUNC(E002_C030_P110);
    
    // feedback event
    void onSuccesses(CCNode *node, int tag);
    void onFails(CCNode *node, int tag);
    virtual void onComplete();
    virtual void onExamplesTouched(int index);
    void playEffect(CCNode *node, int index);
    
    void setQuestions();
    void nextQuestion();
    
    void resetExamples();
    void resetValue();
    void speakNarration(CCNode *node, const char* fileName);
    
    //sound
    virtual void playAppearanceExamplesSound(CCNode* sender, void* index);
    
    void createWall();
    void showFire();
    void showShakeFullScreen(CCNode *node, int count);
    
    void showSuccessCharacterMotion(CCNode *node, int index);
    void showWrongCharacterMotion(CCNode *node, int index);

    void showGuideCharacterLooping();
    void playExampleSuccessEffectSnd();
    
    void showWallParticle(CCNode *node, int index);
    virtual void completeToGetRewardItem();
    
    
    //Guide
    virtual void showGuide();
    virtual void removeGuide();
    virtual void completeToMoveHand(CCNode *node, int index);
    virtual void completeFirstGuide();
};

#endif
