//
//  E002_Base_P000_Index.h
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#ifndef SoundPhonics_Template_E002_Base_P000_Index_h
#define SoundPhonics_Template_E002_Base_P000_Index_h


#include "cocos2d.h"
#include "CJLayer.h"
#include "CCScrollLayer.h"
#include "CJAnimationManager.h"
#include "E002_Base_Navigation.h"
#include "CJLMSContentInterface.h"

using namespace cocos2d;

class E002_Base_P000_Index;

class E002_Base_P000_Index_Delegate 
{
public:
    virtual void onTouchedNavigationButtonAtClose(E002_Base_P000_Index* pIndex){};
};


class E002_Base_P000_Index : public CJLayer , public CJAnimationManager, public E002_Base_Navigation{
public:
    int             m_nSelectedIndex;
    CCArray*        arrMenu;
    CCArray*        arrTitle;
    CCArray*        arrLockImages;
    
    unsigned int    currentPositionIndex;
    CCDictionary*               m_psdDictionary;
    
private:
    std::string     _sTitleNarrationFileName;
    std::string     _sStageLockUserDefaultKey;

    std::string     _sBgmFileName;
    
    bool            _bIsGoPackage;
    void            speakTitleNarration(CCNode* sender, void* index);
    
public:
    ~E002_Base_P000_Index();
    E002_Base_P000_Index();

    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onViewLoad();
    virtual void onViewLoaded();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
     
    CREATE_FUNC(E002_Base_P000_Index);
    
    
    
    
#pragma mark - navigation delegate
    virtual void onTouchedNavigationButtonAtPackage()
    {
        _bIsGoPackage = true;
        pauseSchedulerAndActions();
        CJLMSContentInterface::getInstance()->showPackage();
    }

    virtual void goToSelectedPage(CCNode* sender, void* index);
    
    
#pragma mark - callback
    virtual void OnLastFrame(CJAnimation* pAnimation);
    virtual void onNarrationFinishedCallback(std::string fileName);
    
#pragma mark - index popup metho
private:
    CJLayer                                     *_parentClass;
    E002_Base_P000_Index                        *_this;
    std::vector<CCTouchDelegate *>              _touchDispatchers;
    bool                                        _bIsFromIndexButton;
    
    
    
    void _setAllNodeTouchEnable(CCNode *pNode, bool bIsTouchable);
    CCNode* _findSuperNode(CCNode *pNode);
    void _setMenuEnable(CCNode *pNode, bool bIsTouchable);
    void _setDispatcherEnable(bool bIsTouchable);
    
    void createMenu();
    void createEarth();
    void createObject(CCNode *node, int index);
    
    void showEarth();
    void showObject();
    void showCharacter();
    void createTitle(CCNode* node, int index);
    void changeTitle(CCNode* node, int index);
    void changeObject();
    void completeRotate();
    
    void selectMenuCallback(CCNode* node);
    void createDim();
    
    void playAnimationFromSelectMenu(); 
public:
    void createCloseButton();
    void showIndex(CJLayer *pParent, E002_Base_P000_Index* pIndex);
    void hideIndex();
    void closeHandler(CCObject* sender);

#pragma mark - close menu
private:
    E002_Base_P000_Index_Delegate* _indexDelegate;
public:
    void setIndexDelegate(E002_Base_P000_Index_Delegate* pDelegate){_indexDelegate = pDelegate;}

    std::string getContentID(std::string resource);
    void setDefaultBackground();
    
};


#endif
