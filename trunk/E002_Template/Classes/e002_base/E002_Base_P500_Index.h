//
//  E002_Base_P500_Index.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#ifndef SoundPhonics_Template_E002_Base_P500_Index_h
#define SoundPhonics_Template_E002_Base_P500_Index_h


#include "cocos2d.h"
#include "CJLayer.h"
#include "E002_Base_Navigation.h"
#include "CJPopup.h"
#include "E002_Base_P000_Index.h"

enum eSingMenuIndex{
    eMenuIndexSingAndPlay = 10,
    eMenuIndexSingAndRecord = 11,
    eMenuIndexBeatTheDrums = 12,
};

using namespace cocos2d;

class E002_Base_P500_Index : public CJLayer, public E002_Base_Navigation, public E002_Base_P000_Index_Delegate
{
protected:
    CCDictionary*               m_psdDictionary;
    CCMenu*                     m_singMenu;
    
public:
    bool                        m_bIsGuide;
    bool                        m_bIsGuideSkiped;
    
private:
    std::string                 _sMenuUserDefaultKey;
    std::string                 _sGoodByeNarrationName;
    CJPopup*            _quitPopup;
    
public:
    ~E002_Base_P500_Index();
    E002_Base_P500_Index();

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    virtual void onNarrationFinishedCallback(std::string fileName);
    
    
    virtual void onTouchedNavigationButtonAtInfo();
    virtual void onTouchedNavigationButtonAtIndex()
    {
        CJUtils::getInstance()->setUserDefaultIntegerForKey(NAVIGATION_GLOBAL_INDEX_KEY, eNavigationMenuIndex_song);
    };
    
    virtual void onTouchedNavigationButtonAtClose(E002_Base_P000_Index* pIndex)
    {
        pIndex->hideIndex();
        pIndex->setVisible(false);
        this->removeChild(pIndex);
    }
    
    void checkLms();
    
    CREATE_FUNC(E002_Base_P500_Index);
    
    
    int getSingUserDefaultValue();
    void setSingUserDefaultValue(int pValue);
    void createSingMenu();
    void onTouchedMenu(CCNode* pSender);
    virtual void onReplaceSceneByMenuIndex(eSingMenuIndex pIndex);
    
    void showQuitPopup();
    void onTouchedQuitPopup(CCNode* pSender);
    void onQuitAnimation();
    void onQuit();
    void hideQuitAnimation();
    
    //animation
    int _nLightParticleIndex;
    void lightParticleSequence();
    void lightParticle(int pIndex);
    
    //Guide
public:

    void showFirstGuide();
     
private:
    void _onReplaceSceneByMenuIndexForDelay(CCNode* sender, int index);
    void lightAnimation();
    void lightAnimation2();
    void lightingColorAnimation(CCNode* node);
    void lightRotateAnimation(CCNode* node, float r1, float r2);
};


#endif
