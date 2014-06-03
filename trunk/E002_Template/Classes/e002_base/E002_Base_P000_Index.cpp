//
//  E002_Base_P000_Index.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#include "E002_Base_P000_Index.h"
#include "CJPsdParser.h"

enum {
    kTagMenuParentsBG = 100,
    kTagEarth = 101,
    kTagCharacter = 102,
    kTagObject = 103,
    kTagCircleBlur = 104,
    kTagMenus = 105,
    kTagTitle = 106,
    
    kTagMenuLetsStart = 110,
    kTagMenuLetsPlay1 = 111,
    kTagMenuPower = 112,
    kTagMenuLetsPlay2 = 113,
    kTagMenuLetsPlay3 = 114,
    kTagMenuDiary = 115,
    kTagMenuSong = 116,
};

#define MENU_MAX_COUNT     7

#pragma mark - init


E002_Base_P000_Index::E002_Base_P000_Index()
{
    _sTitleNarrationFileName = "";
    
    arrMenu = new CCArray();
    arrTitle = new CCArray();
    arrLockImages = new CCArray();
    m_nSelectedIndex = 0;
    _sBgmFileName.clear();
    m_psdDictionary = new CCDictionary();
    
    //for popup
    _parentClass = NULL;
    _this = NULL;
    _touchDispatchers.clear();
    _bIsFromIndexButton = false;
    _indexDelegate = NULL;
    
    _bIsGoPackage= false;
}

E002_Base_P000_Index::~E002_Base_P000_Index()
{
    _sTitleNarrationFileName.clear();
    CC_SAFE_DELETE(arrMenu);
    CC_SAFE_DELETE(arrTitle);
    CC_SAFE_DELETE(arrLockImages);
    
    
    
    _touchDispatchers.clear();
}



bool E002_Base_P000_Index::init()
{
    if (!CJLayer::init()) {
        return false;
    }
    
    currentPositionIndex = 0;
 
    return true;
}


void E002_Base_P000_Index::onEnter()
{
    CJLayer::onEnter();
    addSoundObserver();
    
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    _sStageLockUserDefaultKey = CJUtils::getStringMerge(CJUtils::getInstance()->getContentID(),"_completeIndex");
}

void E002_Base_P000_Index::onExit()
{
    
    
    removeSoundObserver();
//    CJUtils::getInstance()->setUserDefaultIntegerForKey(NAVIGATION_GLOBAL_INDEX_KEY,2);

    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CJMultimedia::getInstance()->stopNarration(getCommonFilePath("snd",_sBgmFileName));
    CJUtils::stopAllAnimations(this);
    CJUtils::removeAllchildren(this);
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CJUtils::getInstance()->setPopupStatus(false);
    
    CCLayerColor::onExit();
    

    
}

void E002_Base_P000_Index::onViewLoad()
{
    CJLayer::onViewLoad();
    
    setAnimationParent(this);
    
    CJPsdParser::parseToPsdJSON(getContentID("_p000_index.json"), &m_psdDictionary);
 
    createDim();
    
    createEarth();
    createMenu();
    createObject(NULL, currentPositionIndex);
    createTitle(NULL, currentPositionIndex);
    
}

void E002_Base_P000_Index::onViewLoaded()
{
    CJLayer::onViewLoaded();
    
    E002_Base_Navigation::initWithNavigationType(this, "", eNavigationType_Index);
    E002_Base_Navigation::showNavigation();
    
    if (_bIsFromIndexButton)
    {
        createCloseButton();
    }
    else
    {
        setDefaultBackground();
    }
    
    //_sBgmFileName = "e001_common_snd_bgm_01.mp3";
    //playCommonNarration(_sBgmFileName, true);

}

void E002_Base_P000_Index::setDefaultBackground()
{
    CJSprite *defaultBG = CJSprite::createWithFullPath(getContentID("_p000_index_bg.jpg").c_str());
    defaultBG->setPosition(winCenter);
    addChild(defaultBG, kDepth0_background-1);
}


#pragma mark - touch

bool E002_Base_P000_Index::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return false;
}

void E002_Base_P000_Index::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void E002_Base_P000_Index::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

#pragma mark - load view

 void E002_Base_P000_Index::speakTitleNarration(CCNode* sender, void* index)
{
    int idx = (int)index;
    _sTitleNarrationFileName = CJUtils::getStringFormatInteger("e001_common_snd_%02d.mp3", idx+1);
    CJLog("_sTitleNarrationFileName = %s" ,_sTitleNarrationFileName.c_str());
    CJMultimedia::getInstance()->playNarration(getCommonFilePath("snd", _sTitleNarrationFileName));
    CJLog("getCommonFilePath = %s", getCommonFilePath("snd", _sTitleNarrationFileName).c_str());
}

void E002_Base_P000_Index::goToSelectedPage(CCNode* sender, void* index)
{
    /* override me */
    CCLog("goToSelectedPage");
}

#pragma mark - menu 

void E002_Base_P000_Index::createMenu()
{
    CJSprite *parentMenu = CJPsdParser::getPsdSprite(getContentID("_p000_index_bg_000"), m_psdDictionary);
    
    CCArray* temp = CCArray::create();
    
    for (int i = kTagMenuLetsStart; i <= kTagMenuSong; i++)
    {
        std::string sKey, nKey, dKey;
        
        if(i - kTagMenuLetsStart == currentPositionIndex)
        {
            sKey = "_n";
            nKey = "_s";
        }
        else
        {
            sKey = "_s";
            nKey = "_n";
        }
		
        dKey = "_d";
        
		CCSprite* nSprite = CCSprite::create(getFilePath("img", getContentID(CJUtils::getStringFormatInteger("_p000_index_btn%02d", i-kTagMenuLetsStart).append(nKey).append(".png"))).c_str());
        CCSprite* sSprite = CCSprite::create(getFilePath("img",getContentID(CJUtils::getStringFormatInteger("_p000_index_btn%02d", i-kTagMenuLetsStart).append(sKey).append(".png"))).c_str());
        CCSprite* dSprite = CCSprite::create(getFilePath("img",getContentID(CJUtils::getStringFormatInteger("_p000_index_btn%02d", i-kTagMenuLetsStart).append(dKey).append(".png"))).c_str());

		CCMenuItemSprite* menuItem = CCMenuItemSprite::create(nSprite,
                                                              sSprite,
                                                              dSprite,
                                                              this,
                                                              menu_selector(E002_Base_P000_Index::selectMenuCallback));
        
        menuItem->setPosition(CJPsdParser::getPsdPosition(getContentID(CJUtils::getStringFormatInteger("_p000_index_btn%02d", i-kTagMenuLetsStart).append(nKey)),
                                                                                                                  m_psdDictionary));
                                                         
        menuItem->setTag(i);
        temp->addObject(menuItem);
    }
 
    CCMenu *menu = CCMenu::createWithArray(temp);
    menu->setPosition(CCPointZero);

    parentMenu->addChildIgnoreParent(menu, kDepth8_menu, kTagMenus);
    
    addChild(parentMenu, kDepth8_menu, kTagMenuParentsBG);
    
    parentMenu->setPosition(ccp(parentMenu->getPositionX(), parentMenu->getPositionY() - 300));
    parentMenu->runAction(CCEaseSineInOut::create(CCMoveBy::create(0.3f, ccp(0, 300))));
}

void E002_Base_P000_Index::selectMenuCallback(CCNode* sender)
{
    CCMenuItemSprite *selectMenu = (CCMenuItemSprite*)getChildByTag(kTagMenuParentsBG)->getChildByTag(kTagMenus)->getChildByTag(sender->getTag());
  
    for (int i = kTagMenuLetsStart; i <= kTagMenuSong; i++)
    {
        if(sender->getTag() == i)
        {
            CCSprite* sSprite = CCSprite::create(getFilePath("img", getContentID(CJUtils::getStringFormatInteger("_p000_index_btn%02d", i-kTagMenuLetsStart).append("_s").append(".png"))).c_str());
            
            selectMenu->setNormalImage(sSprite);
        }
        else
        {
            CCSprite* nSprite = CCSprite::create(getFilePath("img", getContentID(CJUtils::getStringFormatInteger("_p000_index_btn%02d", i-kTagMenuLetsStart).append("_n").append(".png"))).c_str());
            
            CCMenuItemSprite *deSelectMenu = (CCMenuItemSprite*)getChildByTag(kTagMenuParentsBG)->getChildByTag(kTagMenus)->getChildByTag(i);
            
            deSelectMenu->setNormalImage(nSprite);
        }
    }
    
    currentPositionIndex = sender->getTag() - kTagMenuLetsStart;
    playAnimationFromSelectMenu();
}

void E002_Base_P000_Index::createEarth()
{
    CJSprite *earth = CJPsdParser::getPsdSprite(getContentID("_p000_index_img_earth_normal"), m_psdDictionary);
    addChild(earth, kDepth0_backImage, kTagEarth);
}

void E002_Base_P000_Index::showCharacter()
{
    CJSprite *character = CJPsdParser::getPsdSprite("e002_proto_ch1", m_psdDictionary);
    ((CJSprite*)getChildByTag(kTagEarth))->addChildIgnoreParent(character, kDepth1_actors + 1, kTagCharacter);
}

void E002_Base_P000_Index::createObject(CCNode *node, int index)
{
    CJSprite *object = CJPsdParser::getPsdSprite(getContentID(CJUtils::getStringFormatInteger("_p000_index_object%02d", index)), m_psdDictionary);
   ((CJSprite*)getChildByTag(kTagEarth))->addChildIgnoreParent(object, kDepth1_actors, kTagObject);
}

void E002_Base_P000_Index::createTitle(CCNode *node, int index)
{
    CJSprite *title = CJPsdParser::getPsdSprite(getContentID(CJUtils::getStringFormatInteger("_p000_index_text%02d", index)), m_psdDictionary);
    addChild(title, kDepth4_title, kTagTitle);
}

void E002_Base_P000_Index::changeTitle(CCNode *node, int index)
{
    CJSprite *title = CJPsdParser::getPsdSprite(getContentID(CJUtils::getStringFormatInteger("_p000_index_text%02d", index)), m_psdDictionary);
    addChild(title, kDepth4_title, kTagTitle);
    title->setOpacity(0);
    title->runAction(CCFadeIn::create(0.3f));
}

void E002_Base_P000_Index::playAnimationFromSelectMenu()
{
    removeChildByTag(kTagTitle);

    CJSprite *earth = (CJSprite*)getChildByTag(kTagEarth);
    
    earth->setTexture(CCTextureCache::sharedTextureCache()->addImage(getFilePath("img", getContentID("_p000_index_img_earth_rotate.png")).c_str()));
    earth->runAction(CCSequence::create(CCEaseSineIn::create(CCRotateBy::create(0.15f, -180)),
                                        CCCallFunc::create(this, callfunc_selector(E002_Base_P000_Index::changeObject)),
                                        CCEaseSineIn::create(CCRotateBy::create(0.15f, -180)),
                                        CCCallFunc::create(this, callfunc_selector(E002_Base_P000_Index::completeRotate)),
                                        CCDelayTime::create(0.1f),
                                        CCCallFuncND::create(this, callfuncND_selector(E002_Base_P000_Index::changeTitle), (void*)currentPositionIndex),
                                        CCDelayTime::create(0.5f),
                                         CCCallFuncND::create(this, callfuncND_selector(E002_Base_P000_Index::goToSelectedPage), (void*)currentPositionIndex),
                                        NULL));
    
}

void E002_Base_P000_Index::changeObject()
{
    CJSprite *earth = (CJSprite*)getChildByTag(kTagEarth);
    //earth->removeChildByTag(kTagCharacter);
    earth->removeChildByTag(kTagObject);
    
//    CJSprite *character = CJPsdParser::getPsdSprite("e002_proto_ch2", m_psdDictionary);
//    ((CJSprite*)getChildByTag(kTagEarth))->addChildIgnoreParent(character, kDepth1_actors + 1, kTagCharacter);
    
    CJSprite *object = CJPsdParser::getPsdSprite(getContentID(CJUtils::getStringFormatInteger("_p000_index_object%02d", currentPositionIndex)), m_psdDictionary);
    ((CJSprite*)getChildByTag(kTagEarth))->addChildIgnoreParent(object, kDepth1_actors, kTagObject);

}

void E002_Base_P000_Index::completeRotate()
{
    CJSprite *earth = (CJSprite*)getChildByTag(kTagEarth);
    
    earth->setTexture(CCTextureCache::sharedTextureCache()->addImage(getFilePath("img",getContentID("_p000_index_img_earth_normal.png")).c_str()));
}
                     
 
                     
#pragma mark - callback function

void E002_Base_P000_Index::OnLastFrame(CJAnimation* pAnimation)
{
 
    if (_bIsGoPackage) {
        return;
    }

}

void E002_Base_P000_Index::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == _sTitleNarrationFileName) {
        goToSelectedPage(NULL, (void*)m_nSelectedIndex);
        removeSoundObserver();
    }
}

#pragma mark - index popup method
void E002_Base_P000_Index::createCloseButton()
{
 
    
    CCMenuItemImage* close = CCMenuItemImage::create(getCommonFilePath("img","e002_common_btn_close_n.png").c_str(),
                                                     getCommonFilePath("img","e002_common_btn_close_s.png").c_str(),
                                                     this,
                                                     menu_selector(E002_Base_P000_Index::closeHandler));

    
    CCMenu* menu = CCMenu::create(close, NULL);
    menu->setPosition(CCPointMake(winSize.width - 49, winSize.height- (49 + 24)));
    addChild(menu,500);
}


void E002_Base_P000_Index::showIndex(CJLayer *pParent, E002_Base_P000_Index* pIndex)
{

    _parentClass = pParent;
    _this = pIndex;
    
    
    
    _bIsFromIndexButton = true;

    CJUtils::getInstance()->pauseAllAnimations(_parentClass);
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    CJMultimedia::getInstance()->pauseBGM();
    CJMultimedia::getInstance()->pauseAllNarration();
    

    _setAllNodeTouchEnable(_parentClass, false);
        _this->setVisible(true);
    

    
    
    
    
}

void E002_Base_P000_Index::hideIndex()
{
    
CCLOG("hideIndex");
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CJUtils::getInstance()->stopAllAnimations(_this);
    _setAllNodeTouchEnable(_parentClass, true);
    _this->setVisible(false);
    
    
    CJUtils::getInstance()->resumeAllAnimations(_parentClass);
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    CJMultimedia::getInstance()->resumeAllNarration();
    CJMultimedia::getInstance()->resumeBGM();
    
    
    if (CJUtils::getInstance()->getUserDefaultIntegerForKey(NAVIGATION_GLOBAL_INDEX_KEY) == eNavigationMenuIndex_page3) {
        CJLog("hideIndex::eNavigationMenuIndex_page3");
    }
 
}


void E002_Base_P000_Index::closeHandler(CCObject* sender)
{
    CCLOG("CLOSE HANDLER");
    CCMenuItem* menu = (CCMenuItem*)sender;
    menu->setEnabled(false);
    
    E002_Base_P000_Index* index = (E002_Base_P000_Index*)menu->getParent()->getParent();
    _indexDelegate->onTouchedNavigationButtonAtClose(index);
}

void E002_Base_P000_Index::_setAllNodeTouchEnable(cocos2d::CCNode *pNode, bool bIsTouchable)
{
    CCLOG("_setAllNodeTouchEnable");
    CCNode *superNode = this->_findSuperNode(pNode);
    
    this->_setMenuEnable(superNode, bIsTouchable);
    this->_setDispatcherEnable(bIsTouchable);
}

CCNode* E002_Base_P000_Index::_findSuperNode(CCNode *pNode)
{
    CCLOG("_findSuperNode");
    CCNode *superNode = pNode;
    while(true)
    {
        if(superNode->getParent() != NULL)
        {
            superNode = superNode->getParent();
        }
        else
        {
            return superNode;
        }
    }
}

void E002_Base_P000_Index::_setMenuEnable(cocos2d::CCNode *pNode, bool bIsTouchable)
{
    CCLOG("_setMenuEnable");
    for(int childIdx=0; childIdx<pNode->getChildren()->count(); childIdx++)
    {
        CCNode *child = (CCNode *)pNode->getChildren()->objectAtIndex(childIdx);
        
        // is This popup instance?
        if(dynamic_cast<E002_Base_P000_Index *>(child))
        {
            continue ;
        }
        
        // is CCMenu instance?
        if(dynamic_cast<CCMenu *>(child))
        {
            CCMenu *menu = (CCMenu *)child;
            menu->setTouchEnabled(bIsTouchable);
            
            continue ;
        }
        
        // is CCLayer instance?
        if(dynamic_cast<CCLayer *>(child))
        {
            // is added touch dispatcher item?
            if(CCDirector::sharedDirector()->getTouchDispatcher()->findHandler((CCLayer *)child) != NULL)
            {
                // add touch dispatcher item.
                _touchDispatchers.push_back((CCLayer *)child);
            }
        }
        
        if(child->getChildrenCount() > 0)
        {
            this->_setMenuEnable(child, bIsTouchable);
        }
    }
}

void E002_Base_P000_Index::_setDispatcherEnable(bool bIsTouchable)
{
    CCLOG("_setDispatcherEnable");
    // added touch dispatcher item iteration
    for(int dispathcherIdx=0; dispathcherIdx<_touchDispatchers.size(); dispathcherIdx++)
    {
        // is touch enable true?
        if(bIsTouchable == true)
        {
            // add touch dispatcher item by added touch dispatcher item instance.
            if(CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(_touchDispatchers[dispathcherIdx]) == NULL){
                CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(_touchDispatchers[dispathcherIdx], 0, true);
            }
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        }
        // is touch enable false?
        else
        {
            // remove touch dispatcher item by added touch dispatcher item instance.
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(_touchDispatchers[dispathcherIdx]);
            
            if(CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(this) == NULL){
                CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
            }
        }
    }
    CCLOG("END _setDispatcherEnable");
}

std::string E002_Base_P000_Index::getContentID(std::string resource)
{
    return CJUtils::getInstance()->getContentID().append(resource);
}
 
void E002_Base_P000_Index::createDim()
{
    CCSprite* dim = CCSprite::create();
    dim->setTextureRect(CCRectMake(0, 0, winSize.width, winSize.height));
    dim->setColor(ccBLACK);
    dim->setContentSize(CCSizeMake(winSize.width, winSize.height));
    dim->setPosition(ccp(winSize.width/2, winSize.height/2));
    dim->setOpacity(190);
    dim->setZOrder(kDepth0_background);
    
	addChild(dim);
    
}