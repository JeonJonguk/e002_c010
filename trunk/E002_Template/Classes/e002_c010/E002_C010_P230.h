//
//  E001_C010_P110_Q1.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#ifndef SoundPhonics_Template_E002_C010_P230_h
#define SoundPhonics_Template_E002_C010_P230_h


#include "E002_Base_Reward.h"
#include "SSQuestionItem.h"
#include "E002_C010_SoundManager.h"

using namespace cocos2d;

class E002_C010_P230 : public E002_Base_Reward
{
private:

    int                                             m_nMaxStageCount;
    int                                             m_nCurrentStageIndex;

    
    E002_C010_SoundManager*                         mSndManager;
    std::vector<SSQuestionItem*>                    mQuestions;
    int                                             _successCount;
    SSQuestionItem*                                 _currentQuestionItem;
    
    std::string                                     mFirstNarration;
    
    CCArray*                                        _arrBuildings;

    CCParallaxNode*                                 parallaxLayer;
    CJSprite*                                       layer1;
    CJSprite*                                       layer2;
    CJSprite*                                       layer3; //flash layer
    CJSprite*                                       layer4;
    float                                           ratio1;
    float                                           ratio2;
    float                                           ratio3;
    float                                           ratio4;
    float                                           totalDist;

    int                                             nForLayer1Position;
    int                                             nForLayer2Position;
    int                                             nForLayer4Position;
    
    CJAnimation*                                    mAnison;
    CJAnimation*                                    mBoom;
    CJAnimation*                                    mRobot;
    
    bool                                            bIsJumping;
    bool                                            bIsKoong;
    CJSprite                                        *mBoomParent;
    
    CCParticleSystemQuad*                           cloudParticle;
    CCParticleSystemQuad*                           starParticle;
    
public:
    
    ~E002_C010_P230();
    E002_C010_P230();

    
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
    
    CREATE_FUNC(E002_C010_P230);
    
    
    
    // feedback event
    void onSuccesses(CCNode *node, int tag = 0);
    void onFails(CCNode *node, int tag = 0);
    void onComplete();
    void onEnd();


    void setQuestions();
    void runStart();
    void resetValue();
    void speakNarration(CCNode* node, std::string fileName);
    
    void start();
    void checkStageSchedule();
    void checkSchedule();
    

    CJAnimation* _playAnimationAnison(std::string pAniKey, int count = -1);
    CJAnimation* _playAnimationBoomBoom(std::string pAniKey, int count = -1);
    CJAnimation* _playAnimationRobot(std::string pAniKey, int count = -1);

    virtual void completeFirstGuide();
    void showCompletePopup();
    
#pragma my util
    CJSprite* createSprite(std::string pStr);
    void _setPositionOutParent(CCNode* child, CCNode* newParent);
    void _safeRemoveFromParents(CCNode* pChild);
};


class hurdle
{
    
};


#endif
