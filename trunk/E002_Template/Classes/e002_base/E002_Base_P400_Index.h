//
//  E002_Base_P400_Index.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#ifndef SoundPhonics_Template_E002_Base_P400_Index_h
#define SoundPhonics_Template_E002_Base_P400_Index_h


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

class E002_Base_P400_Index : public CJLayer, public E002_Base_Navigation, public E002_Base_P000_Index_Delegate, public CJAnimationManager
{
protected:
    CCDictionary*               m_psdDictionary;
    std::vector<bool>          *m_completeDiary;
    
public:
    ~E002_Base_P400_Index();
    E002_Base_P400_Index();

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
        CJUtils::getInstance()->setUserDefaultIntegerForKey(NAVIGATION_GLOBAL_INDEX_KEY, eNavigationMenuIndex_diary);
    };
    
    virtual void onTouchedNavigationButtonAtClose(E002_Base_P000_Index* pIndex)
    {
        pIndex->hideIndex();
        pIndex->setVisible(false);
        this->removeChild(pIndex);
    }
    
    void animationManagerParseComplete();
    
    void showPictures();
    
    virtual void showCompletePopup(){};
    virtual void showDiaryIntro(){};
    
    std::string getContentID(std::string resource);
    
    CREATE_FUNC(E002_Base_P400_Index);
    
    
};

#endif
