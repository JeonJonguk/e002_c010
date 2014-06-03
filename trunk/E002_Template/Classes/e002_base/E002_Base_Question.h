//
//  E002_Base_Question.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#ifndef SoundPhonics_Template_E002_Base_Question_h
#define SoundPhonics_Template_E002_Base_Question_h


#include "cocos2d.h"
#include "CJLayer.h"
#include "CJAnimationManager.h"
#include "E002_Base_Navigation.h"
#include "E002_Base_P000_Index.h"
#include "CJAnimationCharacter.h"

using namespace cocos2d;

typedef enum{
    eGuidePageP110,
    eGuidePageP120,
    eGuidePageP210,
    eGuidePageP220,
    eGuidePageP310,
    eGuidePageP320,
    
} eGuidePageIndex;


class E002_Base_Question : public CJLayer , public CJAnimationManager, public E002_Base_Navigation, public E002_Base_P000_Index_Delegate
{
public:
    int                         m_nCurrentStageIndex;           // 스테이지 인덱스를 관리할 변수
    int                         m_nMaxStageCount;               // 스테이지 카운트
    CCDictionary*               m_psdDictionary;                // psd를 파싱할 딕셔너리
    CCArray*                    m_arrExamples;                  // 보기들을 담을 배열
    CCArray*                    m_arrShadows;                   // 그림자들을 담을 배열
    CCPointArray*               m_arrExamplesOriginPosition;    // 보기들이 되돌아갈 처음 포지션
    CJSprite*                   m_touchingExampleSp;
    int                         m_nExamplesTouchedIndex;

    bool                        m_bIsGuide;
    bool                        m_bIsGuideSkiped;
    
    bool                        m_bIsTapped;
    int                         m_currentGuideIndex;

    E002_Base_Question         *m_Guide;
    bool                        mShowFirstGuide;
private:
    bool                        _touchEnable;
    bool                        _bIsFirstSkip;                  // 처음 나레이션 스킵을 위한 플래그
    bool                        _bIsFirstNarrationStarted;
    int                         _exampleEffectId;



    unsigned int                _examplesSoundId;               // 재생한 보기 이펙트 사운드id
    std::string                 _answerSoundId;                 // 재생한 정답 나레이션 사운드 id
    CCString*                   _exampleNarrationString;
    CCAction*                   _exampleRepeatAction;
    
    CCPoint                     _touchBeganPos;
    std::vector<CJAnimationCharacter*> *_characters;
    std::vector<CCPoint> *mGuidehandPositions;
    CCPoint                     _guidePositon;
    
public:
    
    ~E002_Base_Question();
    E002_Base_Question();
    
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    virtual void onFirstNarration();
    virtual void onFirstNarrationEnd();
    virtual void onNarrationFinishedCallback(std::string fileName); /* for override */
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual bool onTouchBegan(CCPoint tp){return false;};
    virtual void onTouchMoved(CCPoint tp){};
	virtual void onTouchEnded(CCPoint tp){};
    
    
    // Navigation DELEGATE functions.
    virtual void onTouchedNavigationButtonAtIndex()
    {
//        _bIsFirstSkip = true;
        CJUtils::getInstance()->setUserDefaultIntegerForKey(NAVIGATION_GLOBAL_INDEX_KEY, eNavigationMenuIndex_page1);
    };
    virtual void onTouchedNavigationButtonAtInfo(){}; 
    virtual void onTouchedNavigationButtonAtPrev(){_bIsFirstSkip = true;};
    virtual void onTouchedNavigationButtonAtNext(){_bIsFirstSkip = true;};
    virtual void onTouchedNavigationButtonAtClose(E002_Base_P000_Index* pIndex)
    {
        pIndex->hideIndex();
        pIndex->setVisible(false);
        this->removeChild(pIndex);
    }
    virtual void onTouchedNavigationButtonAtReward(){};
    virtual void onTouchedNavigationButtonAtClose()
    {
        removeGuide();
    };

    CREATE_FUNC(E002_Base_Question);
    
    // 보기가 터치되었을때 호출되는 함수
    virtual void onExamplesTouched(int index); /* for override */
    virtual void onSuccesses(){};
    virtual void onFails(){};
    virtual void onComplete(){}; // after success.
    

    // set Examples
    void createExampleSprite(const char * fileName, ...);                               // 보기 스프라이트 생성
    void createExampleSpriteForPsd(const char * fileName, ...);                         // 보기 스프라이트를 psd 정보에서 생성
    void addChildExamples(int zorder = kDepth3_examples);                               // 화면에 보기 스프라이트 붙임
    void removeAllExamples();                                                           // 화면에서 모든 보기들을 삭제한다.
    void setExampleOriginPosition(std::vector<CCPoint>* originPositionVector);          // set original position (createExampleSprite need to this)
    virtual void examplesAppearanceAnimation(CCPoint point = ccp(0,-250));              // 에니메이션 등장 모션 (오버라이딩 가능)
    virtual void examplesAppearanceAnimationEnd();
    
    //set Exampels's shadows
    public:
    void createExampleShadowSprite(const char * fileName, ...);
    void createExampleShadowSpriteForPsd(const char * fileName, ...);
    void addChildShadows(int zorder);
    void examplesShadowAppearanceAnimation(CCNode* sender, void* nIndex);
    void showShadowAnimation(int index);
    void hideShadowAnimation(int index);
    void removeAllShadows();
    
    // sound & narration
    virtual void playAppearanceExamplesSound(CCNode* sender, void* index);              // 보기가 등장할때 나오는 사운드
    void playExamplesSound(std::string fileName, bool bLoop = false);
    void stopExamplesSound();
    void playAnswerSound(std::string fileName, bool bLoop = false);
    void stopAnswerSound();
    // narration repeate action
    void playExampleNarrationRepeat(std::string fileName);
    void stopExampleNarrationRepeat();
    private:
    void _playExampleNarrationRepeat(CCNode* sender, void* path);
    
public:
    
    //Guide
    virtual void showGuide();
    virtual void removeGuide();
    
    void setTouchEnableBaseLayer(bool enable);
    void setTouchEnableBaseLayer(){_touchEnable = true;};
    void setTouchDisalbeBaseLayer(){_touchEnable = false;};
    
    void setFirstSkip(bool bSkip){_bIsFirstSkip = bSkip;};
    bool isFirstSkiped(){return _bIsFirstSkip;};
    
    
    //animation
    void addAnimationCharacter(CJAnimationCharacter *character, ...);
    void animationManagerParseComplete();
    virtual void startFlashAnimation(){};
    virtual void OnLastFrame(CJAnimation* pAnimation);
    
    void completeLetsPlay1();
    void completeLetsPlay2();
    void completeLetsPlay3();

    void showLetPlay1RewardItem(CCNode *node, int currentIndex);
    void showLetPlay1RewardPopup(CCNode *node, int currentIndex);
    void showLetPlay2RewardItem(CCNode *node, int currentIndex);
    void showLetPlay2RewardPopup(CCNode *node, int currentIndex);
    void showLetPlay3RewardItem(CCNode *node, int currentIndex);
    void showLetPlay3RewardPopup(CCNode *node, int currentIndex);
    
    virtual void completeToGetRewardItem();
    void completeRewardPopup();
    
    void addRewardPopupCompleteObserver();
    void removeRewardPopupCompleteObserver();
    
    
    //Guide
    bool getUserDefaultFirstGuide(eGuidePageIndex page);
    void setUserDefaultFirstGuide(eGuidePageIndex page);
    
    void setDatapool(std::multimap<std::string, CJFlash::CJAnimationDataPool*> data);
    void setGuide(bool isGuide);
    void removeTouchDelegateForGuide();
    void createGuideDim(int zOrder);
    void setGuideHandPosition(std::vector<CCPoint> *guideHandPositions);
    void showHand(CCNode *node, int index);
    virtual void completeToMoveHand(CCNode *node, int index){};
    void hideHand();
    
    virtual void completeFirstGuide(){};
};

#endif
