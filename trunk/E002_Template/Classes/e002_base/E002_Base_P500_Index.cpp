//
//  E002_Base_P500_Index.cpp
//  SoundPhonics_Template
//
//  Created by smallsnail on 13. 5. 31..
//
//

#include "E002_Base_P500_Index.h"
//#include "E001_C010_P000_Info.h"

enum {
    kTagTitle,
    kTagStage,
    kTagLight00,
    kTagLight01,

    kTagQuitPinky,
    kTagQuitCru,
    kTagQuitBuba,
    
    kTagQuitMenu,
};

#pragma mark - init

E002_Base_P500_Index::E002_Base_P500_Index()
{
    m_psdDictionary = new CCDictionary();
    _sMenuUserDefaultKey.clear();
    _nLightParticleIndex = 0;
}

E002_Base_P500_Index::~E002_Base_P500_Index()
{
    CC_SAFE_DELETE(m_psdDictionary);
}



bool E002_Base_P500_Index::init()
{
    if (!CJLayer::init()) {
        return false;
    }
    
    std::string contendId = CJUtils::getInstance()->getContentID();
    _sMenuUserDefaultKey = CJUtils::getStringMerge(contendId, "_p500_singMenuCompleteIndex");


    return true;
}


void E002_Base_P500_Index::onEnter()
{
    CJLayer::onEnter();
}

void E002_Base_P500_Index::onExit()
{
    CJMultimedia::getInstance()->stopBGM();
    removeSoundObserver();
    CJLayer::onExit();
}


#pragma mark - touch

bool E002_Base_P500_Index::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
    return false;
}

void E002_Base_P500_Index::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void E002_Base_P500_Index::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

#pragma mark - load view

void E002_Base_P500_Index::onViewLoad()
{
    CJLayer::onViewLoad();
    
    CJSprite* bg = CJSprite::createWithCommonPath("e001_common_sing_img_bg.jpg");
    setBackground(bg);
    
    CJPsdParser::parseToPsdXML("e001_common_sing.xml", &m_psdDictionary, true);
    
    
    CJSprite* stage = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_stage", m_psdDictionary);
    addChild(stage, kDepth0_backImage, kTagStage);

    CJSprite* light00 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_light_00", m_psdDictionary);
    addChild(light00, kDepth0_backImage, kTagLight00);
    light00->setOpacity(0);
    
    CJSprite* light01 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_light_01", m_psdDictionary);
    addChild(light01, kDepth0_backImage, kTagLight01);
    light01->setOpacity(0);
    
    CJSprite* title = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_title", m_psdDictionary);
    addChild(title, kDepth4_title, kTagTitle);
    
    title->m_originPosition = title->getPosition();
    title->setPosition(ccpAdd(title->getPosition(), ccp(0,350)));
    title->setRotation(-20.0f);
    
    createSingMenu();

    //bottom light
    CJSprite* bl_l1_00 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_light00_00", m_psdDictionary);
    addChild(bl_l1_00, kDepth0_backImage);
    CJSprite* bl_l1_01 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_light00_01", m_psdDictionary);
    addChild(bl_l1_01, kDepth0_backImage);
    lightRotateAnimation(bl_l1_00, 30, -10);
    
    CJSprite* bl_l2_00 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_light02_00", m_psdDictionary);
    addChild(bl_l2_00, kDepth0_backImage);
    CJSprite* bl_l2_01 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_light02_01", m_psdDictionary);
    addChild(bl_l2_01, kDepth0_backImage);
    lightRotateAnimation(bl_l2_00, -10, 30);
    
    CJSprite* bl_r1_00 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_light01_00", m_psdDictionary);
    addChild(bl_r1_00, kDepth0_backImage);
    CJSprite* bl_r1_01 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_light01_01", m_psdDictionary);
    addChild(bl_r1_01, kDepth0_backImage);
    lightRotateAnimation(bl_r1_00, 10, -30);
    
    CJSprite* bl_r2_00 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_light03_00", m_psdDictionary);
    addChild(bl_r2_00, kDepth0_backImage);
    CJSprite* bl_r2_01 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_light03_01", m_psdDictionary);
    addChild(bl_r2_01, kDepth0_backImage);
    lightRotateAnimation(bl_r2_00, -30, 10);
    
    CJSprite* bl_l1_light = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_lighting00", m_psdDictionary);
    bl_l1_00->addChildIgnoreParent(bl_l1_light, kDepth0_backImage);
    CJSprite* bl_l2_light = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_lighting02", m_psdDictionary);
    bl_l2_00->addChildIgnoreParent(bl_l2_light, kDepth0_backImage);
    CJSprite* bl_r1_light = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_lighting01", m_psdDictionary);
    bl_r1_00->addChildIgnoreParent(bl_r1_light, kDepth0_backImage);
    CJSprite* bl_r2_light = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_lighting03", m_psdDictionary);
    bl_r2_00->addChildIgnoreParent(bl_r2_light, kDepth0_backImage);
    
    lightingColorAnimation(bl_l1_light);
    lightingColorAnimation(bl_l2_light);
    lightingColorAnimation(bl_r1_light);
    lightingColorAnimation(bl_r2_light);
    
    /*========================== chapter.1 ==========================*/
    CJSprite* cha1 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_cha_00_00", m_psdDictionary);
    addChild(cha1, kDepth1_actors-1);

    cha1->runAction(CJUtils::getSeqAction(-1,
                                          0.3,
                                          getCommonFilePath("img","e001_common_sing_img_cha_00_00.png").c_str(),
                                          getCommonFilePath("img","e001_common_sing_img_cha_00_00.png").c_str(),
                                          getCommonFilePath("img","e001_common_sing_img_cha_00_00.png").c_str(),
                                          getCommonFilePath("img","e001_common_sing_img_cha_00_01.png").c_str(),
                                          NULL));
    
    
    /*========================== chapter.2 ==========================*/
    if ( getSingUserDefaultValue() >= 1 )
    {
        
        CJSprite* cha2 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_cha_01_00", m_psdDictionary);
        addChild(cha2, kDepth1_actors+1);
        
        // pinky
        cha2->runAction(CJUtils::getSeqAction(-1,
                                              0.4,
                                              getCommonFilePath("img","e001_common_sing_img_cha_01_00.png").c_str(),
                                              getCommonFilePath("img","e001_common_sing_img_cha_01_00.png").c_str(),
                                              getCommonFilePath("img","e001_common_sing_img_cha_01_01.png").c_str(),
                                              NULL));
        cha2->runAction(CCRepeatForever::create( CCSequence::create(CCDelayTime::create(0.8),
                                                                    CCJumpBy::create(0.4, CCPointZero, 30, 1),
                                                                    NULL)));
        
        
        
        CJSprite* note1 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_note_00", m_psdDictionary);
        addChild(note1, kDepth3_examples);
        CJSprite* note2 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_note_01", m_psdDictionary);
        addChild(note2, kDepth3_examples);
        
        note1->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCSpawn::create(CCMoveBy::create(0.3, ccp(0, -15)),
                                                                                                            CCRotateTo::create(0.3, 15),
                                                                                                            NULL)),
                                                                    CCEaseSineInOut::create(CCSpawn::create(CCMoveBy::create(0.3, ccp(0, +15)),
                                                                                                            CCRotateTo::create(0.3, -15),
                                                                                                            NULL)),
                                                                    NULL)));
        
        note2->runAction(CCRepeatForever::create(CCSequence::create(CCEaseSineInOut::create(CCSpawn::create(CCMoveBy::create(0.35, ccp(0, 15)),
                                                                                                            CCRotateTo::create(0.35, -15),
                                                                                                            NULL)),
                                                                    CCEaseSineInOut::create(CCSpawn::create(CCMoveBy::create(0.35, ccp(0, -15)),
                                                                                                            CCRotateTo::create(0.35, +15),
                                                                                                            NULL)),
                                                                    NULL)));

    }
    

    /*========================== chapter.3 ==========================*/
    
    if ( getSingUserDefaultValue() >= 2 )
    {
        
        CJSprite* cha3 = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_cha_02_00", m_psdDictionary);
        addChild(cha3, kDepth1_actors+1);
        cha3->setAnchorPointWithoutPosition(ccp(0.5,0));
        
        CJSprite* ufo = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_drum", m_psdDictionary);
        cha3->addChildIgnoreParent(ufo);
        
        CJSprite* drumEffect = CJPsdParser::getPsdCommonSprite("e001_common_sing_img_drum_efx", m_psdDictionary);
        cha3->addChildIgnoreParent(drumEffect);
        drumEffect->setOpacity(0);
        
        
        // buba
        cha3->runAction(CJUtils::getSeqAction(-1,
                                              0.4,
                                              getCommonFilePath("img","e001_common_sing_img_cha_02_00.png").c_str(),
                                              getCommonFilePath("img","e001_common_sing_img_cha_02_01.png").c_str(),
                                              NULL));
        cha3->runAction(CCRepeatForever::create( CCSequence::create( CCRotateTo::create(0.4, 5),
                                                                    CCRotateTo::create(0.4, -5),
                                                                    NULL)));
        
        drumEffect->runAction(CCRepeatForever::create( CCSequence::create(CCFadeOut::create(0),
                                                                          CCDelayTime::create(0.4),
                                                                          CCFadeIn::create(0),
                                                                          CCDelayTime::create(0.4),
                                                                          NULL)));
    }
    
    
    //lms check
    checkLms();
}

void E002_Base_P500_Index::onViewLoaded()
{
    CJLayer::onViewLoaded();
    E002_Base_Navigation::initWithNavigationType(this, "",
                                                 eNavigationType_Menu);
    E002_Base_Navigation::showNavigation();

    
    CJMultimedia::getInstance()->playBGM(getCommonFilePath("snd","e001_common_snd_bgm_03.mp3"), true);
    
    
    CJSprite* title = (CJSprite*)getChildByTag(kTagTitle);
        
    title->runAction(CCSequence::create(CCEaseSineInOut::create(CCMoveTo::create(0.3, ccpAdd(title->m_originPosition, ccp(0,-60)))),
                                        CCEaseSineInOut::create(CCSpawn::create(CCRotateTo::create(0.3, 0),
                                                                                CCMoveTo::create(0.3, ccpAdd(title->m_originPosition, ccp(0,+60))),
                                                                                NULL)),
                                        CCEaseSineInOut::create(CCSpawn::create(CCRotateTo::create(0.3, 10),
                                                                                CCMoveTo::create(0.3, ccpAdd(title->m_originPosition, ccp(0,-30))),
                                                                                NULL)),
                                        CCEaseSineInOut::create(CCSpawn::create(CCRotateTo::create(0.3, 0),
                                                                                CCMoveTo::create(0.3, title->m_originPosition),
                                                                                NULL)),
                                        
                                        CCCallFunc::create(this, callfunc_selector(E002_Base_P500_Index::lightParticleSequence)),
                                        NULL));
    
    lightAnimation();
    lightAnimation2();
    
    
    int value = getSingUserDefaultValue();
    if (value == 3) {
        m_singMenu->setTouchEnabled(false);
        CJUtils::getInstance()->setUserDefaultIntegerForKey(_sMenuUserDefaultKey, 4);
        CJUtils::performSelector(this, callfunc_selector(E002_Base_P500_Index::onQuit),0.3);
   }
}



void E002_Base_P500_Index::createSingMenu()
{
    CJSprite* menuSp1_n = CJSprite::createWithCommonPath("e001_common_sing_img_menu_00_n.png");
    CJSprite* menuSp1_s = CJSprite::createWithCommonPath("e001_common_sing_img_menu_00_s.png");
    
    CJSprite* menuSp2_n = CJSprite::createWithCommonPath("e001_common_sing_img_menu_01_n.png");
    CJSprite* menuSp2_s = CJSprite::createWithCommonPath("e001_common_sing_img_menu_01_s.png");
    CJSprite* menuSp2_d = CJSprite::createWithCommonPath("e001_common_sing_img_menu_01_d.png");
    
    CJSprite* menuSp3_n = CJSprite::createWithCommonPath("e001_common_sing_img_menu_02_n.png");
    CJSprite* menuSp3_s = CJSprite::createWithCommonPath("e001_common_sing_img_menu_02_s.png");
    CJSprite* menuSp3_d = CJSprite::createWithCommonPath("e001_common_sing_img_menu_02_d.png");
    
    CCMenuItemSprite* singPlay = CCMenuItemSprite::create(menuSp1_n,
                                                          menuSp1_s,
                                                          this,
                                                          menu_selector(E002_Base_P500_Index::onTouchedMenu));
    singPlay->setTag(eMenuIndexSingAndPlay);
    singPlay->setPosition(CJPsdParser::getPsdPosition("e001_common_sing_img_menu_00_n", m_psdDictionary));
    
    CCMenuItemSprite* singRecord = CCMenuItemSprite::create(menuSp2_n,
                                                            menuSp2_s,
                                                            menuSp2_d,
                                                            this,
                                                            menu_selector(E002_Base_P500_Index::onTouchedMenu));
    singRecord->setTag(eMenuIndexSingAndRecord);
    singRecord->setPosition(CJPsdParser::getPsdPosition("e001_common_sing_img_menu_01_n", m_psdDictionary));
    
    CCMenuItemSprite* drums = CCMenuItemSprite::create(menuSp3_n,
                                                       menuSp3_s,
                                                       menuSp3_d,
                                                       this,
                                                       menu_selector(E002_Base_P500_Index::onTouchedMenu));
    drums->setTag(eMenuIndexBeatTheDrums);
    drums->setPosition(CJPsdParser::getPsdPosition("e001_common_sing_img_menu_02_n", m_psdDictionary));
    
    CCArray* temp = CCArray::create(singPlay,singRecord,drums,NULL);
    m_singMenu = CCMenu::createWithArray(temp);
    m_singMenu->setPosition(CCPointZero);
    m_singMenu->setTouchEnabled(true);
    addChild(m_singMenu, kDepth1_actors);

    if (getSingUserDefaultValue() == 0) {
        singRecord->setEnabled(false);
        drums->setEnabled(false);
    }else if (getSingUserDefaultValue() == 1)
    {
        drums->setEnabled(false);
    }
}


void E002_Base_P500_Index::onTouchedMenu(CCNode* pSender)
{
    E002_Base_Navigation::setEnableNavigation(false);
    
    m_singMenu->setTouchEnabled(false);
    eSingMenuIndex index = (eSingMenuIndex)pSender->getTag();
    
    switch (index) {
        case eMenuIndexSingAndPlay:
            playCommonNarration("e001_common_snd_08.mp3");
            break;
        case eMenuIndexSingAndRecord:
            playCommonNarration("e001_common_snd_09.mp3");
            break;
        case eMenuIndexBeatTheDrums:
            playCommonNarration("e001_common_snd_10.mp3");
            break;
            
        default:
            break;
    }

    CJUtils::performSelector(this, callfuncND_selector(E002_Base_P500_Index::_onReplaceSceneByMenuIndexForDelay),(void*)index ,1.0);
}

void E002_Base_P500_Index::_onReplaceSceneByMenuIndexForDelay(CCNode* sender, int index)
{
    eSingMenuIndex eIndex = (eSingMenuIndex)index;
    onReplaceSceneByMenuIndex(eIndex);
}

void E002_Base_P500_Index::onReplaceSceneByMenuIndex(eSingMenuIndex pIndex)
{
    /* override me */
}


#pragma mark - ending popup

void E002_Base_P500_Index::showQuitPopup()
{
        
    CJSprite* menuSp1_n = CJSprite::createWithCommonPath("e001_common_sing_btn_continue_n.png");
    CJSprite* menuSp1_s = CJSprite::createWithCommonPath("e001_common_sing_btn_continue_s.png");
    
    CJSprite* menuSp2_n = CJSprite::createWithCommonPath("e001_common_sing_btn_quit_n.png");
    CJSprite* menuSp2_s = CJSprite::createWithCommonPath("e001_common_sing_btn_quit_s.png");
    
    CCMenuItemSprite* item1 = CCMenuItemSprite::create(menuSp1_n,
                                                       menuSp1_s,
                                                       this,
                                                       menu_selector(E002_Base_P500_Index::onTouchedQuitPopup));
    item1->setTag(0);
    item1->setPosition(CJPsdParser::getPsdPosition("e001_common_sing_btn_continue_n", m_psdDictionary));
    
    CCMenuItemSprite* item2 = CCMenuItemSprite::create(menuSp2_n,
                                                       menuSp2_s,
                                                       this,
                                                       menu_selector(E002_Base_P500_Index::onTouchedQuitPopup));
    item2->setTag(1);
    item2->setPosition(CJPsdParser::getPsdPosition("e001_common_sing_btn_quit_n", m_psdDictionary));
    
    
    
    CCMenu* menu = CCMenu::create(item1, item2, NULL);
    menu->setPosition(CCPointZero);
    _quitPopup->addChild(menu, kDepth2_questions, kTagQuitMenu);
    
    playNarration("");
    
    //lms ??
    
}

void E002_Base_P500_Index::onTouchedQuitPopup(CCNode* pSender)
{
    if (pSender->getTag() == 0) // continue
    {
        playCommonEffect("e001_common_snd_41.mp3");
        _quitPopup->runAction(CCSequence::create(CCDelayTime::create(1.1),
                                                 CCCallFunc::create(_quitPopup, callfunc_selector(CJPopup::hidePopup)),
                                                 CCCallFunc::create(_quitPopup, callfunc_selector(CJPopup::removeFromParent)),
                                                 NULL));
        
        
    }else{                      // end
        playCommonEffect("e001_common_snd_40.mp3");
        ((CCMenu*)_quitPopup->getChildByTag(kTagQuitMenu))->runAction(CCSequence::create(CCDelayTime::create(0.3),
                                                                                         CCFadeOut::create(0.3),NULL));
        runAction(CCSequence::create(CCDelayTime::create(0.8),
                                                 CCCallFunc::create(this, callfunc_selector(E002_Base_P500_Index::onQuit)),
                                                 NULL));
        
        
    }
    ((CCMenu*)_quitPopup->getChildByTag(kTagQuitMenu))->setEnabled(false);
}

void E002_Base_P500_Index::onQuitAnimation()
{
//    CJMultimedia::getInstance()->stopBGM();
    addSoundObserver();
    
    _quitPopup = CJPopup::create();
    addChild(_quitPopup, kDepth9_navigations+10);
    _quitPopup->showPopup(this);

    
    CJSprite* cru = CJPsdParser::getPsdCommonSprite("e001_common_sing_ending_00_00", m_psdDictionary);
    CJSprite* pinky = CJPsdParser::getPsdCommonSprite("e001_common_sing_ending_01_00", m_psdDictionary);
    CJSprite* pinky_arm = CJPsdParser::getPsdCommonSprite("e001_common_sing_ending_01_arm", m_psdDictionary);
    CJSprite* buba = CJPsdParser::getPsdCommonSprite("e001_common_sing_ending_02_00", m_psdDictionary);
    CJSprite* buba_arm = CJPsdParser::getPsdCommonSprite("e001_common_sing_ending_02_arm", m_psdDictionary);
    _quitPopup->addChild(pinky,kTagQuitPinky,kTagQuitPinky);
    _quitPopup->addChild(cru,kTagQuitCru,kTagQuitCru);
    pinky->addChildIgnoreParent(pinky_arm,-1);
    _quitPopup->addChild(buba,kTagQuitBuba,kTagQuitBuba);
    buba->addChildIgnoreParent(buba_arm,-1);


    pinky->setPosition(ccp(pinky->getPosition().x, pinky->getPosition().y - pinky->getContentSize().height));
    buba->setPosition(ccp(buba->getPosition().x + buba->getContentSize().width+170, buba->getPosition().y));
    cru->setPosition(ccp(cru->getPosition().x - cru->getContentSize().width, cru->getPosition().y - cru->getContentSize().height));
    
    pinky->m_secondPosition = pinky->getPosition();
    buba->m_secondPosition = buba->getPosition();
    cru->m_secondPosition = cru->getPosition();
    
    
    cru->runAction(CJUtils::getSeqAction(-1, 0.3,
                                         getCommonFilePath("img","e001_common_sing_ending_00_00.png").c_str(),
                                         getCommonFilePath("img","e001_common_sing_ending_00_01.png").c_str(),
                                         NULL));
    
    pinky->runAction(CJUtils::getSeqAction(-1, 0.3,
                                           getCommonFilePath("img","e001_common_sing_ending_01_00.png").c_str(),
                                           getCommonFilePath("img","e001_common_sing_ending_01_01.png").c_str(),
                                           NULL));
    
    buba->runAction(CJUtils::getSeqAction(-1, 0.3,
                                          getCommonFilePath("img","e001_common_sing_ending_02_00.png").c_str(),
                                          getCommonFilePath("img","e001_common_sing_ending_02_01.png").c_str(),
                                          NULL));
    
    
    pinky_arm->setAnchorPointWithoutPosition(ccp(0,0.2));
    pinky_arm->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCRotateBy::create(0.3, 20),1.5),
                                                                   CCEaseInOut::create(CCRotateBy::create(0.3, -20),1.5),
                                                                   NULL)));
    
    buba_arm->setAnchorPointWithoutPosition(ccp(1,0.2));
    buba_arm->runAction(CCRepeatForever::create(CCSequence::create(CCEaseInOut::create(CCRotateBy::create(0.3, -10),1.5),
                                                                   CCEaseInOut::create(CCRotateBy::create(0.3, 10),1.5),
                                                                   NULL)));
    
    pinky->runAction(CCSequence::create(CCDelayTime::create(0.2),
                                        CCEaseSineOut::create(CCMoveTo::create(0.3, ccpAdd(pinky->m_originPosition,ccp(0,10)))),
                                        CCEaseSineIn::create(CCMoveTo::create(0.1, pinky->m_originPosition)),
                                        NULL));
    buba->runAction(CCSequence::create(CCDelayTime::create(0.6),
                                       CCEaseSineOut::create(CCMoveTo::create(0.35, ccpAdd(buba->m_originPosition,ccp(-20,0)))),
                                       CCEaseSineIn::create(CCMoveTo::create(0.1, buba->m_originPosition)),
                                       NULL));
    cru->runAction(CCSequence::create(CCDelayTime::create(1.0),
                                      CCEaseSineOut::create(CCMoveTo::create(0.3, ccpAdd(cru->m_originPosition,ccp(10,10)))),
                                      CCEaseSineIn::create(CCMoveTo::create(0.1, cru->m_originPosition)),
                                      NULL));
    

    std::string _id = CJUtils::getInstance()->getContentID();
    _sGoodByeNarrationName = CJUtils::getStringMerge(_id, "_popup.mp3");
    CJMultimedia::getInstance()->playNarrationWithDelay(this, getCommonFilePath("snd",_sGoodByeNarrationName),1.0);
    
    
}

void E002_Base_P500_Index::hideQuitAnimation()
{
    
    CJSprite* pinky = (CJSprite*)_quitPopup->getChildByTag(kTagQuitPinky);
    CJSprite* cru = (CJSprite*)_quitPopup->getChildByTag(kTagQuitCru);
    CJSprite* buba = (CJSprite*)_quitPopup->getChildByTag(kTagQuitBuba);
    pinky->stopAllActions();
    cru->stopAllActions();
    buba->stopAllActions();
    
    pinky->runAction(CCSequence::create(CCDelayTime::create(0.0),
                                        CCEaseBackIn::create(CCMoveTo::create(0.2, pinky->m_secondPosition)),
                                        CCCallFunc::create(pinky, callfunc_selector(CJSprite::removeFromParent)),
                                        NULL));
    
    cru->runAction(CCSequence::create(CCDelayTime::create(0.2),
                                      CCEaseBackIn::create(CCMoveTo::create(0.2, cru->m_secondPosition)),
                                      CCCallFunc::create(cru, callfunc_selector(CJSprite::removeFromParent)),
                                      NULL));
    
    buba->runAction(CCSequence::create(CCDelayTime::create(0.4),
                                       CCEaseBackIn::create(CCMoveTo::create(0.2, buba->m_secondPosition)),
                                       CCCallFunc::create(buba, callfunc_selector(CJSprite::removeFromParent)),
                                       NULL));
    
    CJUtils::performSelector(this, callfunc_selector(E002_Base_P500_Index::showQuitPopup),0.7);
    
    
}

void E002_Base_P500_Index::onQuit()
{
    //temp
//    exit(0);
    //go to package main menu.
//    CJLMSContentInterface::getInstance()->showPackage();
   // replaceSceneTransitionFadeOut(E001_C010_P000_Info);
}




#pragma mark - animations

void E002_Base_P500_Index::lightAnimation()
{
    CJSprite* light = (CJSprite*)getChildByTag(kTagLight00);

    float opacity = CJUtils::randomFloat(0.7 * 255.0, 1.0 * 255.0);
    float delay = CJUtils::randomFloat(0.1, 0.4);
    float delay2 = CJUtils::randomFloat(0.1, 1.0);

    light->runAction(CCSequence::create(CCDelayTime::create(delay),     
                                        CCFadeTo::create(0, opacity),   //on
                                        CCDelayTime::create(delay2),
                                        CCFadeTo::create(0, 0),         //off
                                        CCCallFuncN::create(this, callfuncN_selector(E002_Base_P500_Index::lightAnimation)),
                                        NULL));
    
}

void E002_Base_P500_Index::lightAnimation2()
{
    CJSprite* light2 = (CJSprite*)getChildByTag(kTagLight01);
    
    float opacity = CJUtils::randomFloat(0.7 * 255.0, 1.0 * 255.0);
    float delay = CJUtils::randomFloat(0.1, 0.4);
    float delay2 = CJUtils::randomFloat(0.1, 1.0);
    
    light2->runAction(CCSequence::create(
                                        CCFadeTo::create(0, opacity),   //on
                                        CCDelayTime::create(delay2),
                                        CCFadeTo::create(0, 0),         //off
                                        CCDelayTime::create(delay),
                                        CCCallFuncN::create(this, callfuncN_selector(E002_Base_P500_Index::lightAnimation2)),
                                        NULL));
    
}

void E002_Base_P500_Index::lightingColorAnimation(CCNode* node)
{
    CCActionInterval* tintA1 = CCTintTo::create(0.2f, 255, 216, 0);
    CCActionInterval* tintE1 = CCEaseSineInOut::create(tintA1);
    
    CCActionInterval* tintA2 = CCTintTo::create(0.2f, 246, 115, 120);
    CCActionInterval* tintE2 = CCEaseSineInOut::create(tintA2);
    
    CCActionInterval* tintA3 = CCTintTo::create(0.2f, 13, 184, 150);
    CCActionInterval* tintE3 = CCEaseSineInOut::create(tintA3);
    
    CCActionInterval* tintA4 = CCTintTo::create(0.2f, 188, 143, 202);
    CCActionInterval* tintE4 = CCEaseSineInOut::create(tintA4);
    
    
    CCActionInterval* seq = CCSequence::create(
                                               tintE1,
                                               tintE2,
                                               tintE3,
                                               tintE4,
                                               NULL);
    
    CCRepeatForever *repeatForever = CCRepeatForever::create( seq );
    
    node->runAction(repeatForever);
}

void E002_Base_P500_Index::lightRotateAnimation(CCNode* node, float r1, float r2)
{
    CCActionInterval* rotA1 = CCRotateTo::create(0.3f, r1);
    CCActionInterval* rotE1 = CCEaseSineOut::create(rotA1);
    
    CCActionInterval* rotA2 = CCRotateTo::create(0.3f, r2);
    CCActionInterval* rotE2 = CCEaseSineOut::create(rotA2);
    
    
    CCActionInterval* seq = CCSequence::create(
                                               rotE1,
                                               CCDelayTime::create(0.5f),
                                               rotE2,
                                               CCDelayTime::create(0.5f),
                                               NULL);
    
    
    CCRepeatForever *repeatForever = CCRepeatForever::create( seq );
    
    node->runAction(repeatForever);
}


void E002_Base_P500_Index::lightParticleSequence()
{
    float delay = CJUtils::randomFloat(0.1, 0.9);
    lightParticle(_nLightParticleIndex);
    this->runAction(CCSequence::create(CCDelayTime::create(delay),
                                       CCCallFunc::create(this, callfunc_selector(E002_Base_P500_Index::lightParticleSequence)),
                                       NULL));
    _nLightParticleIndex++;
}

void E002_Base_P500_Index::lightParticle(int pIndex)
{
    //(252,622), (795,527),(364,431), (595, 677), (838, 640)
    CCPoint point;
    switch (pIndex%5) {
        case 0:
            point = ccp(252,622);
            break;
        case 1:
            point = ccp(795,527);
            break;
        case 2:
            point = ccp(364,431);
            break;
        case 3:
            point = ccp(595, 677);
            break;
        case 4:
            point = ccp(838, 640);
            break;
        default:
            point = CCPointZero;
            break;
    }
    float scaleValue = CJUtils::randomFloat(0.9, 2.0);
    
    CCParticleSystemQuad* lightParticle = CCParticleSystemQuad::create(getCommonFilePath("img","e001_common_drum_particle_lighting.plist").c_str());
    addChild(lightParticle, kDepth5_particle);
    lightParticle->setScale(scaleValue);
    lightParticle->setPosition(point);
    lightParticle->setAutoRemoveOnFinish(true);
}

void E002_Base_P500_Index::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == _sGoodByeNarrationName) {
        runAction(CCSequence::create(CCFadeOut::create(0.5),
                                     CCCallFunc::create(this, callfunc_selector(E002_Base_P500_Index::hideQuitAnimation)),
                                     NULL));
    }
}


#pragma mark - utils

int E002_Base_P500_Index::getSingUserDefaultValue()
{
    int value = CJUtils::getInstance()->getUserDefaultIntegerForKey(_sMenuUserDefaultKey);
    CJLog("E002_Base_P500_Index:: %s = %d", _sMenuUserDefaultKey.c_str(), CJUtils::getInstance()->getUserDefaultIntegerForKey(_sMenuUserDefaultKey.c_str()));
    return value;
}


#pragma mark - navigation

void E002_Base_P500_Index::onTouchedNavigationButtonAtInfo()
{
//    if (m_GuidePopup == NULL)
//    {
//        this->makeGuide(E002_Base_ImageGuide::createWithPage(eGuide_Type1, NULL));
//    }
//    
//    this->showGuideHandler();
}




void E002_Base_P500_Index::showFirstGuide()
{
    if (m_bIsGuideSkiped == false) {
        //showGuideHandler();
    }
}




void E002_Base_P500_Index::checkLms()
{
    //LMS
    std::string contendId = CJUtils::getInstance()->getContentID();
    std::string key510 = CJUtils::getStringMerge(contendId, "_p510_lms");
    std::string key520 = CJUtils::getStringMerge(contendId, "_p520_lms");
    std::string key530 = CJUtils::getStringMerge(contendId, "_p530_lms");
    
    int value510 = CJUtils::getInstance()->getUserDefaultIntegerForKey(key510);
    int value520 = CJUtils::getInstance()->getUserDefaultIntegerForKey(key520);
    int value530 = CJUtils::getInstance()->getUserDefaultIntegerForKey(key530);
    int values[3] = {value510, value520, value530};
    
    
    int resultValue = value510;
    for (int i = 0; i < 3; i++) {
        if (resultValue > values[i]) {
            resultValue = values[i];
        }
    }
    
    std::string key500 = CJUtils::getStringMerge(contendId, "_p500_lms");
    int value500 = CJUtils::getInstance()->getUserDefaultIntegerForKey(key500);
    if ( resultValue > value500) {
        CJUtils::getInstance()->setUserDefaultIntegerForKey(key500, resultValue);
        CJUtils::getInstance()->setLmsMenuEnd(5);
        CJLog("send LMS : 500 = %d",resultValue);
    }
    
    
    
//    CJUtils::getInstance()->setUserDefaultIntegerForKey(key, oldLms + 1);

}

