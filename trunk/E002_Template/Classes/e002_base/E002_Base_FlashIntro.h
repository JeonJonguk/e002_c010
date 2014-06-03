//
//  E002_Base_FlashIntro.h
//  E002_Template
//
//  Created by Jeong.YJ on 2014. 2. 24..
//
//

#ifndef E002_Template_E002_Base_FlashIntro_h
#define E002_Template_E002_Base_FlashIntro_h

#include "cocos2d.h"
#include "CJLayer.h"
#include "CJAnimationManager.h"
#include "E002_Base_Navigation.h"
#include "E002_Base_P000_Index.h"
#include "CJAnimationCharacter.h"

USING_NS_CC;
using namespace CocosDenshion;

class E002_Base_FlashIntro_Sound_Item
{
    CC_SYNTHESIZE(int, f, Frame);
    CC_SYNTHESIZE(std::string, ani, AniName);
    CC_SYNTHESIZE(std::string, snd, SndName);

    E002_Base_FlashIntro_Sound_Item(){};
    
    E002_Base_FlashIntro_Sound_Item(std::string aniName, int frame, std::string sndName)
    {
        ani = aniName;
        f = frame;
        snd = sndName;
    }
};

class E002_Base_FlashIntro : public CJLayer , public CJAnimationManager, public E002_Base_Navigation, public E002_Base_P000_Index_Delegate
{
private:
    std::vector<const char*> *mAnimationNames;
    std::vector<E002_Base_FlashIntro_Sound_Item*> *mNarrationNames;
    std::vector<E002_Base_FlashIntro_Sound_Item*> *mEffectNames;
    
    int mCurrentCut;
    CJSprite *mPlayBtn;
    CJAnimation *mCurrentAnimation;
    bool mIsTouch;

public:
    
    ~E002_Base_FlashIntro();
    E002_Base_FlashIntro();
    
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){};
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){};
    
    virtual void OnLastFrame(CJFlash::CJAnimation *pAnimation);
    
    virtual void onTouchedNavigationButtonAtIndex()
    {
        CJUtils::getInstance()->setUserDefaultIntegerForKey(NAVIGATION_GLOBAL_INDEX_KEY, eNavigationMenuIndex_intro);
    };
    
    virtual void onTouchedNavigationButtonAtInfo(){};
    virtual void onTouchedNavigationButtonAtClose(E002_Base_P000_Index* pIndex)
    {
        pIndex->hideIndex();
        pIndex->setVisible(false);
        this->removeChild(pIndex);
    };
    
    void setCutAnimationName(const char* animation, ...);
    void startAnimation();
    
    void createBtns();
    
    virtual void onFlashIntroCompletedCallback(){};
    
    CREATE_FUNC(E002_Base_FlashIntro);
    
    virtual void animationManagerParseComplete();
    
    void setNarrationOnFrame(std::string aniName, int frame, std::string sndPath);
    void setEffectOnFrame(std::string aniName, int frame, std::string sndPath);

    void setEnableTouch();
};

#endif
