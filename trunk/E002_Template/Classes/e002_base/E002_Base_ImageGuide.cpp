//
//  E002_Base_ImageGuide.cpp
//  SoundPhonics_Template
//
//  Created by whitems on 13. 7. 5..
//
//

#include "E002_Base_ImageGuide.h"

#include "CJUtils.h"

enum
{
    kTagBG = 500,
    kTagHand,
    kTagMenu,
};

E002_Base_ImageGuide::E002_Base_ImageGuide()
{
    m_psdDictionary = new CCDictionary();
    mCurrentPage = 0;
    isOnePageGuide = true;
    mIsFirstGuide = false;
}

E002_Base_ImageGuide::~E002_Base_ImageGuide()
{
    delete m_psdDictionary;
}


#pragma mark - init


bool E002_Base_ImageGuide::init()
{
    if (CJPopup::initWithColor(ccc4(0, 0, 0, 0))) {
        return true;
    }
    
    return true;
}

void E002_Base_ImageGuide::onEnter()
{
    CJPopup::onEnter();
    
    winSize = CCDirector::sharedDirector()->getWinSize();
}

void E002_Base_ImageGuide::onExit()
{
    CJPopup::onExit();
}

#pragma mark - touch

bool E002_Base_ImageGuide::onTouchBegan(CCPoint tp)
{
    return false;
}

void E002_Base_ImageGuide::onTouchMoved(CCPoint tp)
{
    
    
}

void E002_Base_ImageGuide::onTouchEnded(CCPoint tp)
{
    
}

#pragma mark - setting function

void E002_Base_ImageGuide::setGuide(std::vector<E002_Base_ImageGuide_Item*> *items)
{
    CJPsdParser::parseToPsdJSON("e002_common_guide.json", &m_psdDictionary, true);

    mGuideItems = items;

    if (mGuideItems != NULL && mGuideItems->size() > 1)
    {
        isOnePageGuide = false;
    }
    
    setBackground();
    setGuideSprite();
}

void E002_Base_ImageGuide::setBackground()
{
    if(getChildByTag(kTagBG) != NULL)
    {
        removeChildByTag(kTagBG);
    }
    
    CJSprite* bg = CJSprite::create(CJUtils::getInstance()->getFilePath("img", mGuideItems->at(mCurrentPage)->getBackgroundImg(), true).c_str());
    bg->setPosition(ccp(winSize.width/2, winSize.height/2));
    addChild(bg, kDepth0_backImage, kTagBG);
}

void E002_Base_ImageGuide::setGuideSprite()
{
    if (getChildByTag(kTagMenu) != NULL)
    {
        removeChildByTag(kTagMenu);
    }
    
    CJSprite* closeBtnN = CJSprite::createWithCommonPath("e002_common_btn_close_n.png");
    CJSprite* closeBtnS = CJSprite::createWithCommonPath("e002_common_btn_close_s.png");

    CCMenuItemSprite* closeItem = CCMenuItemSprite::create(closeBtnN,
                                                           closeBtnS,
                                                           this,
                                                            menu_selector(E002_Base_ImageGuide::onTouchedCloseBtn));
    
    closeItem->setPosition(CCPointMake(winSize.width - 49, winSize.height- (49+ OS_HEIGHT_GAP)));
    
    CJSprite *bottomRightBtnN;
    CJSprite *bottomRightBtnS;
    CJSprite *bottomLeftBtnN;
    CJSprite *bottomLeftBtnS;
    CCMenuItemSprite* bottomRightBtn;
    CCMenuItemSprite* bottomLeftBtn;

    CCMenu *menu;
    
    if(isOnePageGuide)
    {
        bottomRightBtnN = CJSprite::createWithCommonPath("e002_common_img_btn_start_n.png");
        bottomRightBtnS = CJSprite::createWithCommonPath("e002_common_img_btn_start_s.png");
        
        bottomRightBtn = CCMenuItemSprite::create(bottomRightBtnN,
                                                  bottomRightBtnS,
                                                  this,
                                                  menu_selector(E002_Base_ImageGuide::onTouchedCloseBtn));

        bottomRightBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_img_btn_start_n", m_psdDictionary));
        bottomRightBtn->setVisible(mIsFirstGuide);
        
        menu = CCMenu::create(closeItem, bottomRightBtn, NULL);
    }
    else if(!isOnePageGuide && mCurrentPage == 0)
    {
        bottomRightBtnN = CJSprite::createWithCommonPath("e002_common_img_btn_next_n.png");
        bottomRightBtnS = CJSprite::createWithCommonPath("e002_common_img_btn_next_s.png");
        
        bottomRightBtn = CCMenuItemSprite::create(bottomRightBtnN,
                                                  bottomRightBtnS,
                                                  this,
                                                  menu_selector(E002_Base_ImageGuide::onTouchedNextBtn));
        
        bottomRightBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_img_btn_next_n", m_psdDictionary));
        
        menu = CCMenu::create(closeItem, bottomRightBtn, NULL);
    }
    else if(!isOnePageGuide && mCurrentPage == 1)
    {
        bottomRightBtnN = CJSprite::createWithCommonPath("e002_common_img_btn_start_n.png");
        bottomRightBtnS = CJSprite::createWithCommonPath("e002_common_img_btn_start_s.png");
        
        bottomRightBtn = CCMenuItemSprite::create(bottomRightBtnN,
                                                  bottomRightBtnS,
                                                  this,
                                                  menu_selector(E002_Base_ImageGuide::onTouchedStartBtn));
        
        bottomRightBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_img_btn_start_n", m_psdDictionary));
        bottomRightBtn->setVisible(mIsFirstGuide);
        
        bottomLeftBtnN = CJSprite::createWithCommonPath("e002_common_img_btn_prev_n.png");
        bottomLeftBtnS = CJSprite::createWithCommonPath("e002_common_img_btn_prev_s.png");
        
        bottomLeftBtn = CCMenuItemSprite::create(bottomLeftBtnN,
                                                  bottomLeftBtnS,
                                                  this,
                                                  menu_selector(E002_Base_ImageGuide::onTouchedPreBtn));
        
        bottomLeftBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_img_btn_prev_n", m_psdDictionary));

        menu = CCMenu::create(closeItem, bottomLeftBtn, bottomRightBtn, NULL);

    }
    
    menu->setPosition(CCPointZero);
    addChild(menu, kDepth1_actors, kTagMenu);

    showHandGuide();
}

void E002_Base_ImageGuide::onTouchedCloseBtn()
{
    playBtnEffect();
    sendCompleteMsg();
}

void E002_Base_ImageGuide::onTouchedStartBtn()
{
    playBtnEffect();
    sendCompleteMsg();
}

void E002_Base_ImageGuide::onTouchedNextBtn()
{
    playBtnEffect();
    
    mCurrentPage = 1;
    
    setBackground();
    setGuideSprite();
}

void E002_Base_ImageGuide::onTouchedPreBtn()
{
    playBtnEffect();
    
    mCurrentPage = 0;
    
    setBackground();
    setGuideSprite();
}

void E002_Base_ImageGuide::showHandGuide()
{
    if (getChildByTag(kTagHand) != NULL)
    {
        removeChildByTag(kTagHand);
    }
    
    CJSprite *hand = CJSprite::createWithCommonPath("e002_common_img_guide_hand.png");
    hand->setPosition(mGuideItems->at(mCurrentPage)->getStartPosition());
    hand->setOpacity(0);
    addChild(hand, kDepth1_actors, kTagHand);
    
    CJSprite *light;
    
    if (mGuideItems->at(mCurrentPage)->getEndPosition().x == mGuideItems->at(mCurrentPage)->getStartPosition().x
        && mGuideItems->at(mCurrentPage)->getEndPosition().y == mGuideItems->at(mCurrentPage)->getStartPosition().y) {

        hand->setOpacity(255);
        
        light = CJSprite::createWithCommonPath("e002_common_img_guide_hand_effect.png");
        light->setPosition(ccp(mGuideItems->at(mCurrentPage)->getStartPosition().x - 80, mGuideItems->at(mCurrentPage)->getStartPosition().y + 80));
        light->setOpacity(255);
        addChild(light, kDepth1_actors - 1);
        
    }
    
    
    if (light != NULL)
    {
        CCRepeat *repeat = CCRepeat::create(CCSequence::create(CCFadeIn::create(0.2f),
                                                              CCFadeOut::create(0.2),
                                                              NULL), -1);
        
        light->runAction(repeat);
    }
    else
    {
        CCRepeat *repeat = CCRepeat::create(CCSequence::create(CCFadeIn::create(0.2f),
                                                               CCMoveTo::create(1.0f, mGuideItems->at(mCurrentPage)->getEndPosition()),
                                                               CCFadeOut::create(0.2),
                                                               CCMoveTo::create(0, mGuideItems->at(mCurrentPage)->getStartPosition()),
                                                               CCDelayTime::create(0.5),
                                                               NULL), -1);

        hand->runAction(repeat);
    }
}

void E002_Base_ImageGuide::sendCompleteMsg()
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_GUIDE_CLOSECALL);
}

void E002_Base_ImageGuide::playBtnEffect()
{
    CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd","e002_common_sfx_btn_01.mp3"));
}

void E002_Base_ImageGuide::setFirstGuide(bool isFirst)
{
    mIsFirstGuide = isFirst;
}
