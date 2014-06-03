//
//  E002_Base_Reward.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 6. 24..
//
//

#ifndef SoundPhonics_Template_E002_Base_Reward_h
#define SoundPhonics_Template_E002_Base_Reward_h


#include "cocos2d.h"
#include "CJLayer.h"
#include "CJAnimationManager.h"
#include "E002_Base_Navigation.h"
#include "E002_Base_P000_Index.h"
#include "CJAnimationCharacter.h"
#include "E002_Base_ImageGuide.h"

using namespace cocos2d;

typedef enum{
    eGuidePageP130,
    eGuidePageP230,
    eGuidePageP330,
} eGuideRewardPageIndex;

class E002_Base_Reward : public CJLayer , public CJAnimationManager, public E002_Base_Navigation, public E002_Base_P000_Index_Delegate
{
public:
 
    CCDictionary*               m_psdDictionary;                // psd를 파싱할 딕셔너리
    CCArray*                    m_arrExamples;                  // 보기들을 담을 배열
    CCArray*                    m_arrShadows;                   // 그림자들을 담을 배열
    CCPointArray*               m_arrExamplesOriginPosition;    // 보기들이 되돌아갈 처음 포지션
    CJSprite*                   m_touchingExampleSp;
    int                         m_nExamplesTouchedIndex;
    bool                        _touchEnable;
    CCPoint                     mTouchedPointGab;
    bool                        mShowFirstGuide;
private:

    CCPoint                     _touchBeganPos;
    E002_Base_ImageGuide        *mGuide;
public:
    
    ~E002_Base_Reward();
    E002_Base_Reward();
    
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    virtual void onFirstNarration();
    virtual void onFirstNarrationEnd();
    virtual void onNarrationFinishedCallback(std::string fileName); /* for override */
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
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
    virtual void onTouchedNavigationButtonAtPrev(){};
    virtual void onTouchedNavigationButtonAtNext(){};
    virtual void onTouchedNavigationButtonAtClose(E002_Base_P000_Index* pIndex)
    {
        pIndex->hideIndex();
        pIndex->setVisible(false);
        this->removeChild(pIndex);
    }
    
    CREATE_FUNC(E002_Base_Reward);
    
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
    
public:
    

    void setTouchEnableBaseLayer(bool enable);
    void setTouchEnableBaseLayer(){_touchEnable = true;};
    void setTouchDisalbeBaseLayer(){_touchEnable = false;};
    
    
    //animation
    void addAnimationCharacter(CJAnimationCharacter *character, ...);
    void animationManagerParseComplete();
    virtual void OnLastFrame(CJAnimation* pAnimation);
    virtual void startFlashAnimation(){};

    //Guide
    bool getUserDefaultFirstGuide(eGuideRewardPageIndex page);
    void setUserDefaultFirstGuide(eGuideRewardPageIndex page);
    
    void showGuide(std::vector<E002_Base_ImageGuide_Item*> *items);
    void showGuide(E002_Base_ImageGuide_Item *item);
    void removeGuide();
    
    void addGuidePopupCompleteObserver();
    void removeGuidePopupCompleteObserver();
    
    virtual void completeFirstGuide(){};
    
};

#endif
