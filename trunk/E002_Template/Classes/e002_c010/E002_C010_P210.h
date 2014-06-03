//
//  E001_C010_P110_Q1.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#ifndef SoundPhonics_Template_E002_C010_P210_h
#define SoundPhonics_Template_E002_C010_P210_h


#include "E002_Base_Question.h"
#include "SSExampleItem.h"
#include "SSQuestionItem.h"
#include "E002_C010_SoundManager.h"

using namespace cocos2d;

class E002_C010_P210 : public E002_Base_Question
{
private:
    
    E002_C010_SoundManager*                         mSndManager;
    std::vector<std::vector<SSExampleItem*> >       mExamples;
    std::vector<std::vector<SSQuestionItem*> >      mQuestions;
    
    
    SSExampleItem*  _touchedExampleItem;
    SSQuestionItem* _currentQuestionItem;
    int             _oldCurrentStageIndex;
    
    CCPoint         _targetPoint;
    
    CCArray*        _arrSideObjects_l;
    CCArray*        _arrSideObjects_r;
    CCPoint         _lastPosition_l;
    CCPoint         _lastPosition_r;
    
    //flash
    CJAnimationCharacter *mAnison;
    CJAnimationCharacter *mBoomBoom;
    
    CJSprite* stick_l;
    CJSprite* stick_r;
    CJSprite* e;
    CJSprite* exampleDummy;
    
    std::string     mFirstNarration;
    std::string     mFirstNarration2;
    int             _successCount;
    CCPoint         mTouchedPointGab;
    
public:
    
    ~E002_C010_P210();
    E002_C010_P210();

    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool onTouchBegan(CCPoint tp);
    virtual void onTouchMoved(CCPoint tp);
	virtual void onTouchEnded(CCPoint tp);
    
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
    
    CREATE_FUNC(E002_C010_P210);
    
    
    
    // feedback event
    void onSuccesses(CCNode *node, int tag = 0);
    void onSuccesses_callfunc();
    void onFails(CCNode *node, int tag = 0);
    void onHalfSuccess(CCNode *node, int tag = 0);
    virtual void onComplete();
    virtual void onExamplesTouched(int index);
    void onEnd();
    
    void intoTarget(CJSprite* sp, CCPoint pt);
    void checkAnswer(CCNode *node);
    void showSuccessText();
    void showFailText();
    void _throwLope();
    void _chagneDummy(CCNode *seder, void* data);
    
    void start();
    void setQuestions();
    void showQuestions();
    void showHalfQuestions();
    void setExamples();
    void showExamples();
    void showGuideQuestions();
    
    void resetValue();
    void speakNarration(CCNode* node, std::string fileName);
    
    //sound
    virtual void playAppearanceExamplesSound(CCNode* sender, void* index);
    void playQuestionSound(CCNode* node, void* index);
    
    void showSuccessCharacterMotion(CCNode *node, int index);
    void showWrongCharacterMotion(CCNode *node, int index);

    void runSchedule();
    void stopSchedule();
    void makeSideObjects();
    void sideObjectScheduler();
    
    void questionAppearStep1();
    void questionAppearStep2();
    void exampleAppearStep1();
    void exampleAppearStep2(CCNode* sender);
    void exampleAppearEnd();
    void disappearAnimation();
    void setNextQuestions();
    void showReward();
    
    #pragma mark - flash animation
    void playAnimationRun();
    void stopSpeakingAndLooping();
    
    #pragma mark - this util
    CCPoint getVectorLeftDown(float speed);
    CCPoint getVectorLeftUp(float speed);
    CCPoint getVectorRightDown(float speed);
    CCPoint getVectorRightUp(float speed);
    
    #pragma my util
    CJSprite* createSprite(std::string pStr);
    void _setPositionOutParent(CCNode* child, CCNode* newParent);
    void _safeRemoveFromParents(CCNode* pChild);
    
    
    void showGuide();
    void removeGuide();
    void completeToMoveHand(CCNode *node, int index);
    void completeFirstGuide();
};


class MoveObject: public CJSprite
{
public:
    CJSprite*   shadow;
    CCPoint     pVec;
    bool        bIsUpVec;
    float       fSpeed;
    int         zorder;
    
    
    ~MoveObject(){};
    MoveObject()
    {
        shadow      = NULL;
        pVec        = CCPoint(0, 0);
        bIsUpVec    = true;
        fSpeed      = 0.0f;
        zorder      = 0;
    }
    
    static MoveObject* createWithFullPath(const char *pszFileName)
    {
        MoveObject *pobSprite = new MoveObject();
        
        if (pobSprite && pobSprite->initWithFile(CJUtils::getInstance()->getFilePath("img",pszFileName).c_str()))
        {
            pobSprite->autorelease();
            return pobSprite;
        }
        CC_SAFE_DELETE(pobSprite);
        return NULL;
    }
    
    
    
};

#endif
