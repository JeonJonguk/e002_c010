//
//  E002_Base_ImageGuide.cpp
//  SoundPhonics_Template
//
//  Created by whitems on 13. 7. 5..
//
//

#include "E002_Base_CompletePopup.h"

#include "CJUtils.h"

enum
{
    kTagBG = 500,
    kTagHand,
    kTagMenu,
};

E002_Base_CompletePopup::E002_Base_CompletePopup()
{
    m_psdDictionary = new CCDictionary();
}

E002_Base_CompletePopup::~E002_Base_CompletePopup()
{
    delete m_psdDictionary;
}


#pragma mark - init


bool E002_Base_CompletePopup::init(int pageNumber)
{
    if (!CJPopup::initWithColor(ccc4(0, 0, 0, 190))) {
        return true;
    }
    
    mPageNumber = pageNumber;
    
    return true;
}

void E002_Base_CompletePopup::onEnter()
{
    CJPopup::onEnter();
    
    winSize = CCDirector::sharedDirector()->getWinSize();
}

void E002_Base_CompletePopup::onExit()
{
    CJPopup::onExit();
}

#pragma mark - setting function
void E002_Base_CompletePopup::showCompletePopup()
{
    setPopup();
    setButtions();
}

void E002_Base_CompletePopup::setPopup()
{
    CJPsdParser::parseToPsdJSON("e002_common_popup.json", &m_psdDictionary, true);
    
    std::string title;
    
    if(mPageNumber == P100)
    {
        title = "e002_common_img_end_text00";
    }
    else if(mPageNumber == P200)
    {
        title = "e002_common_img_end_text01";
    }
    else if(mPageNumber == P300)
    {
        title = "e002_common_img_end_text02";
    }
    else
    {
        return;
    }
    
    CJSprite *titleSprite = CJPsdParser::getPsdCommonSprite(title, m_psdDictionary);
    addChild(titleSprite, kDepth1_actors);
    
    
}


void E002_Base_CompletePopup::setButtions()
{
    CJSprite* nextBtnN = CJSprite::createWithCommonPath("e002_common_btn_end_next_n.png");
    CJSprite* nextBtnS = CJSprite::createWithCommonPath("e002_common_btn_end_next_s.png");

    CCMenuItemSprite*  nextBtn = CCMenuItemSprite::create(nextBtnN,
                                                           nextBtnS,
                                                           this,
                                                            menu_selector(E002_Base_CompletePopup::onTouchedNextBtn));
    
    nextBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_btn_end_next_n", m_psdDictionary));
    
    CJSprite* replayBtnN = CJSprite::createWithCommonPath("e002_common_btn_end_replay_n.png");
    CJSprite* replayBtnS = CJSprite::createWithCommonPath("e002_common_btn_end_replay_s.png");
    
    CCMenuItemSprite*  replayBtn = CCMenuItemSprite::create(replayBtnN,
                                                          replayBtnS,
                                                          this,
                                                          menu_selector(E002_Base_CompletePopup::onTouchedReplayBtn));
    
    replayBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_btn_end_replay_n", m_psdDictionary));
    
    
   

    CCMenu *menu = CCMenu::create(nextBtn, replayBtn, NULL);

    menu->setPosition(CCPointZero);
    addChild(menu, kDepth1_actors);

}



void E002_Base_CompletePopup::onTouchedReplayBtn()
{
    playBtnEffect();

}

void E002_Base_CompletePopup::onTouchedNextBtn()
{
    playBtnEffect();
}


void E002_Base_CompletePopup::playBtnEffect()
{
    CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd","e002_common_sfx_btn_01.mp3"));
}
