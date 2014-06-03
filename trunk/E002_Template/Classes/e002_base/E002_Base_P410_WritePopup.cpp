//
//  E002_Base_ImageGuide.cpp
//  SoundPhonics_Template
//
//  Created by whitems on 13. 7. 5..
//
//

#include "E002_Base_P410_WritePopup.h"
#include "E002_Base_DrawLayer.h"
#include "E002_Base_P410_Intro.h"

#include "CJUtils.h"
#include "THStringUtil.h"
#include <stdlib.h>


E002_Base_P410_WritePopup::E002_Base_P410_WritePopup()
{
    m_psdDictionary = new CCDictionary();
}

E002_Base_P410_WritePopup::~E002_Base_P410_WritePopup()
{
    delete m_psdDictionary;
}


#pragma mark - init


bool E002_Base_P410_WritePopup::init()
{
    if (!CJPopup::initWithColor(ccc4(0, 0, 0, 190))) {
        return true;
    }
    
    mCurrentDiary = CJUtils::getInstance()->getUserDefaultIntegerForKey(E002_USERDEFAULT_DIARY_NUMBER);
    
    return true;
}

void E002_Base_P410_WritePopup::onEnter()
{
    CJPopup::onEnter();
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    addSoundObserver();
}

void E002_Base_P410_WritePopup::onExit()
{
    CJPopup::onExit();
    removeSoundObserver();
}

void E002_Base_P410_WritePopup::setChildDictionary(CCDictionary *dictionary)
{
    m_childPsdDictionary = dictionary;
}

#pragma mark - setting function
void E002_Base_P410_WritePopup::showWritePopup()
{
    setPopup();
    setButtons();

}

void E002_Base_P410_WritePopup::setPopup()
{
    CJPsdParser::parseToPsdJSON("e002_common_diary_p410_write.json", &m_psdDictionary, true);
    
    CJSprite *bg = CJPsdParser::getPsdCommonSprite("e002_common_diary_write_img_bg01", m_psdDictionary);
    addChild(bg, kDepth1_actors);
    
    CJSprite *line = CJPsdParser::getPsdCommonSprite("e002_common_diary_write_img_bg00", m_psdDictionary);
    addChild(line, kDepth0_backImage);
    line->setAnchorPointWithoutPosition(ccp(0, 0));
    
    CJSprite* title = CJSprite::createWithFullPath(getContentID(CJUtils::getStringFormatInteger("_p410_img_text%02d_ans.png", mCurrentDiary - DIARY_1)).c_str());
	title->setPosition(CJPsdParser::getPsdPosition(getContentID(CJUtils::getStringFormatInteger("_p410_img_text%02d_ans", mCurrentDiary - DIARY_1)), m_childPsdDictionary));
	addChild(title, kDepth1_actors);
    title->setScale(0);
    
    title->runAction(CCSequence::create(CCDelayTime::create(0.3f),
                                        CCEaseElasticOut::create(CCScaleTo::create(1.5f, 1.0f)),
                                        NULL));
    
    playNarrationWithDelay(getContentID(CJUtils::getStringFormatInteger("_p410_snd_word_%02d_as.mp3", mCurrentDiary - DIARY_1 + 1)), 0.3f);

    CJSprite* content = CJSprite::createWithFullPath(getContentID(CJUtils::getStringFormatInteger("_p410_img_text%02d_bg00.png", mCurrentDiary - DIARY_1)).c_str());
    content->setPosition(CJPsdParser::getPsdPosition(getContentID(CJUtils::getStringFormatInteger("_p410_img_text%02d_bg00", mCurrentDiary - DIARY_1)), m_childPsdDictionary));
    addChild(content, kDepth0_backImage+1);
    
    if (mCurrentDiary > DIARY_2)
    {
        CJSprite* content = CJSprite::createWithFullPath(getContentID(CJUtils::getStringFormatInteger("_p410_img_text%02d_bg01.png", mCurrentDiary - DIARY_1)).c_str());
        content->setPosition(CJPsdParser::getPsdPosition(getContentID(CJUtils::getStringFormatInteger("_p410_img_text%02d_bg01", mCurrentDiary - DIARY_1)), m_childPsdDictionary));
        addChild(content, kDepth0_backImage+3);
    }

    E002_Base_DrawLayer* drawLayer = E002_Base_DrawLayer::create();
	drawLayer->init(getContentSize(),
                    ccp(0,0),
                    CJUtils::getInstance()->getCommonFilePath("img", "e002_common_diary_img_crayon_brush01.png")
                    );
    
	drawLayer->setBrushStroke(1);
	addChild(drawLayer, kDepth0_backImage+2, 101);
    
    drawLayer->setDraweable(true);
    drawLayer->setBrushColor(ccc3(0, 0, 0));
    drawLayer->setDrawSound("e002_common_diary_sfx_write01.mp3");
    
}

void E002_Base_P410_WritePopup::setButtons()
{
    CJSprite* closeBtnN = CJSprite::createWithCommonPath("e002_common_diary_btn_close_n.png");
    CJSprite* closeBtnS = CJSprite::createWithCommonPath("e002_common_diary_btn_close_s.png");
    
    CCMenuItemSprite*  closeBtn = CCMenuItemSprite::create(closeBtnN,
                                                             closeBtnS,
                                                             this,
                                                             menu_selector(E002_Base_P410_WritePopup::onTouchedCloseBtn));
    
    closeBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_btn_close_n", m_psdDictionary));
    
    CJSprite* rewriteBtnN = CJSprite::createWithCommonPath("e002_common_diary_btn_rewrite_n.png");
    CJSprite* rewriteBtnS = CJSprite::createWithCommonPath("e002_common_diary_btn_rewrite_s.png");

    CCMenuItemSprite*  rewriteBtn = CCMenuItemSprite::create(rewriteBtnN,
                                                           rewriteBtnS,
                                                           this,
                                                            menu_selector(E002_Base_P410_WritePopup::onTouchedRewriteBtn));
    
    rewriteBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_btn_rewrite_n", m_psdDictionary));
    
    CJSprite* oKBtnN = CJSprite::createWithCommonPath("e002_common_diary_btn_ok_n.png");
    CJSprite* oKBtnS= CJSprite::createWithCommonPath("e002_common_diary_btn_ok_s.png");
    
    CCMenuItemSprite*  OKBtn = CCMenuItemSprite::create(oKBtnN,
                                                          oKBtnS,
                                                          this,
                                                          menu_selector(E002_Base_P410_WritePopup::_onTouchedOKBtn));
    
    OKBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_btn_ok_n", m_psdDictionary));
    
    
   

    CCMenu *menu = CCMenu::create(closeBtn, rewriteBtn, OKBtn, NULL);

    menu->setPosition(CCPointZero);
    addChild(menu, kDepth1_actors);

}

void E002_Base_P410_WritePopup::onNarrationFinishedCallback(std::string fileName)
{
    if(fileName == "e002_common_snd_btn_02_as.mp3")
    {
        onTouchedOKBtn();
    }
}

void E002_Base_P410_WritePopup::_onTouchedOKBtn()
{
    stopAllNarration();
    playBtnEffect();
    playCommonNarration("e002_common_snd_btn_02_as.mp3");

}

void E002_Base_P410_WritePopup::onTouchedCloseBtn()
{
    hidePopup();
    playBtnEffect();
    ((E002_Base_P410_Intro*)getParent())->removeWritePopup();

    CCNotificationCenter::sharedNotificationCenter()->postNotification(E002_NOTIFICATION_DIARY_WRITE_CLOSECALL);    
}

void E002_Base_P410_WritePopup::onTouchedRewriteBtn()
{
    playBtnEffect();
    playCommonNarration("e002_common_snd_btn_01_as.mp3");

    removeChildByTag(101, true);
    
    E002_Base_DrawLayer* drawLayer = E002_Base_DrawLayer::create();
	drawLayer->init(getContentSize(),
                    ccp(0,0),
                    CJUtils::getInstance()->getCommonFilePath("img", "e002_common_diary_img_crayon_brush01.png")
                    );
    
	drawLayer->setBrushStroke(1);
	addChild(drawLayer, kDepth0_backImage+2, 101);
    
    drawLayer->setDraweable(true);
    drawLayer->setBrushColor(ccc3(0, 0, 0));
    drawLayer->setDrawSound("e002_common_diary_sfx_write01.mp3");

}

void E002_Base_P410_WritePopup::onTouchedOKBtn()
{
    hidePopup();
    ((E002_Base_P410_Intro*)getParent())->removeWritePopup();
    CCNotificationCenter::sharedNotificationCenter()->postNotification(E002_NOTIFICATION_DIARY_WRITE_FINISHCALL);
}

void E002_Base_P410_WritePopup::playBtnEffect()
{
    CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd","e002_common_sfx_btn_01.mp3"));
}

std::string E002_Base_P410_WritePopup::getContentID(std::string resource)
{
    return CJUtils::getInstance()->getContentID().append(resource);
}
