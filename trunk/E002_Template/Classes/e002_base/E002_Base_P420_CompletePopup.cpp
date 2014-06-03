//
//  E002_Base_ImageGuide.cpp
//  SoundPhonics_Template
//
//  Created by whitems on 13. 7. 5..
//
//

#include "E002_Base_P420_CompletePopup.h"

#include "CJUtils.h"
#include "THStringUtil.h"
#include <stdlib.h>
enum
{
    kTagPicture = 500,
};

E002_Base_P420_CompletePopup::E002_Base_P420_CompletePopup()
{
    m_psdDictionary = new CCDictionary();
    mShowingAnimation = new std::vector<E002_Base_DiaryAnimationInfo*>();

}

E002_Base_P420_CompletePopup::~E002_Base_P420_CompletePopup()
{
    delete m_psdDictionary;
}


#pragma mark - init


bool E002_Base_P420_CompletePopup::init(bool fromIndex)
{
    if (!CJPopup::initWithColor(ccc4(0, 0, 0, 190))) {
        return true;
    }
    
    m_isFromIndex = fromIndex;
    mCurrentDiary = CJUtils::getInstance()->getUserDefaultIntegerForKey(E002_USERDEFAULT_DIARY_NUMBER);
    
    return true;
}

void E002_Base_P420_CompletePopup::onEnter()
{
    CJPopup::onEnter();
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    addSoundObserver();
}

void E002_Base_P420_CompletePopup::onExit()
{
    CJPopup::onExit();
    removeSoundObserver();
}

#pragma mark - setting function
void E002_Base_P420_CompletePopup::showCompletePopup()
{
    setPopup();
    setButtions();
    
    if (!m_isFromIndex)
    {
        playCommonNarration("e002_common_snd_family_02_as.mp3");
    }
    
    playCommonEffect("e002_common_diary_sfx_complete_pop.mp3");
}

void E002_Base_P420_CompletePopup::setPopup()
{
    CJPsdParser::parseToPsdJSON("e002_common_diary_p420_complete.json", &m_psdDictionary, true);
    
    CJSprite *frame = CJPsdParser::getPsdCommonSprite("e002_common_diary_complete_img_frame", m_psdDictionary);
    addChild(frame, kDepth1_actors);
    
    CJSprite *anison = CJPsdParser::getPsdCommonSprite("e002_common_diary_complete_anison_00", m_psdDictionary);
    addChild(anison, kDepth1_actors);
    
    anison->runAction(CJUtils::getSeqAction(-1,
                                          0.3,
                                          getCommonFilePath("img","e002_common_diary_complete_anison_01.png").c_str(),
                                          getCommonFilePath("img","e002_common_diary_complete_anison_00.png").c_str(),
                                          NULL));

    
    
}

void E002_Base_P420_CompletePopup::showPicture()
{

    //    get data
    CJLMSResource resource = CJLMSContentInterface::getInstance()->getResFile(mCurrentDiary, eFileType_Extend);
//    //
//        CCLog("%d", resource.menuID);
//    CCLog("%s", resource.szBGImageName.c_str());
//        CCLog("%s", resource.szCaptureImageName.c_str());
//        CCLog("%s", resource.szExtendData.c_str());
//    
    
    CJSprite* diaryLayer = CJSprite::create(resource.szBGImageName.c_str());
    
	diaryLayer->setColor(ccWHITE);
	diaryLayer->setPosition(winCenter);
	addChild(diaryLayer, kDepth0_backImage, kTagPicture);

    std::string flashInfo = resource.szExtendData.c_str();
    
    if (flashInfo == "")
    {
        resizeScalePicture();
        return;
    }
    
    std::vector<std::string> characters = THStringUtil::split(flashInfo.c_str(), '%');
    
    for (int i = 0; i < characters.size(); i++ )
    {
        E002_Base_DiaryAnimationInfo *info = new E002_Base_DiaryAnimationInfo();
        
        std::vector<std::string> characterInfo = THStringUtil::split(characters.at(i).c_str(), '/');
    
        info->setAniName(characterInfo.at(0));
        info->setNumber(atoi(characterInfo.at(1).c_str()));
        info->setPositionX(atof(characterInfo.at(2).c_str()));
        info->setPositionY(atof(characterInfo.at(3).c_str()));
        
        mShowingAnimation->push_back(info);
    }
    
    showCharacters();
}

void E002_Base_P420_CompletePopup::showCharacters()
{
    for (int i = 0; i < mShowingAnimation->size(); i++)
    {
        CJAnimation *ani;
        
        if (mShowingAnimation->at(i)->getAniName() == ANISON)
        {
            ani = playAnimationWithCommonPath(ANISON, CJUtils::getStringFormatInteger("e002_common_diary_flash_as%02d_loop", mShowingAnimation->at(i)->getNumber()), -1, kDepth2_questions, getChildByTag(kTagPicture));
        }
        else if (mShowingAnimation->at(i)->getAniName() == CHU)
        {
            ani = playAnimationWithCommonPath(CHU, CJUtils::getStringFormatInteger("e002_common_diary_flash_ch%02d_loop", mShowingAnimation->at(i)->getNumber()), -1, kDepth2_questions, getChildByTag(kTagPicture));
        }
        else if (mShowingAnimation->at(i)->getAniName() == BOOMBOOM)
        {
            ani = playAnimationWithCommonPath(BOOMBOOM, CJUtils::getStringFormatInteger("e002_common_diary_flash_bb%02d_loop", mShowingAnimation->at(i)->getNumber()), -1, kDepth2_questions, getChildByTag(kTagPicture));
        }
        else if (mShowingAnimation->at(i)->getAniName() == GRUMBIE)
        {
            ani = playAnimationWithCommonPath(GRUMBIE, CJUtils::getStringFormatInteger("e002_common_diary_flash_gb%02d_loop", mShowingAnimation->at(i)->getNumber()), -1, kDepth2_questions, getChildByTag(kTagPicture));
        }
        else if (mShowingAnimation->at(i)->getAniName() == ALPHAROBOT)
        {
            ani = playAnimationWithCommonPath(ALPHAROBOT, CJUtils::getStringFormatInteger("e002_common_diary_flash_ar%02d_loop", mShowingAnimation->at(i)->getNumber()), -1, kDepth2_questions, getChildByTag(kTagPicture));
        }
        
        ani->setPosition(ccp(mShowingAnimation->at(i)->getPositionX(), mShowingAnimation->at(i)->getPositionY()));;

    }
    
    resizeScalePicture();
}

void E002_Base_P420_CompletePopup::resizeScalePicture()
{
    getChildByTag(kTagPicture)->setScale(0.62);
    getChildByTag(kTagPicture)->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_complete_img_position", m_psdDictionary));
}

void E002_Base_P420_CompletePopup::setFlashDataPool(STL_MULTIMAP_DATAPOOL datapool)
{
    setAllDatapool(datapool);
    createAllAnimations();
    
    showPicture();
}


void E002_Base_P420_CompletePopup::setButtions()
{
    CJSprite* reworkBtnN = CJSprite::createWithCommonPath("e002_common_diary_btn_rework_n.png");
    CJSprite* reworkBtnS = CJSprite::createWithCommonPath("e002_common_diary_btn_rework_s.png");

    CCMenuItemSprite*  reworkBtn = CCMenuItemSprite::create(reworkBtnN,
                                                           reworkBtnS,
                                                           this,
                                                            menu_selector(E002_Base_P420_CompletePopup::_onTouchedReworkBtn));
    
    reworkBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_btn_rework_n", m_psdDictionary));
    
    CJSprite* finishBtnN = CJSprite::createWithCommonPath("e002_common_diary_btn_finish_n.png");
    CJSprite* finishBtnS = CJSprite::createWithCommonPath("e002_common_diary_btn_finish_s.png");
    
    CCMenuItemSprite*  finishBtn = CCMenuItemSprite::create(finishBtnN,
                                                          finishBtnS,
                                                          this,
                                                          menu_selector(E002_Base_P420_CompletePopup::_onTouchedFinishBtn));
    
    finishBtn->setPosition(CJPsdParser::getPsdPosition("e002_common_diary_btn_finish_n", m_psdDictionary));
    
    
   

    CCMenu *menu = CCMenu::create(reworkBtn, finishBtn, NULL);

    menu->setPosition(CCPointZero);
    addChild(menu, kDepth1_actors);

}

void E002_Base_P420_CompletePopup::onNarrationFinishedCallback(std::string fileName)
{
    if (fileName == "e002_common_snd_btn_01_as.mp3")
    {
        onTouchedReworkBtn();
    }
    else if (fileName == "e002_common_snd_btn_04_as.mp3")
    {
        onTouchedFinishBtn();
    }
}

void E002_Base_P420_CompletePopup::_onTouchedReworkBtn()
{
    stopAllNarration();
    
    playBtnEffect();
    playCommonNarration("e002_common_snd_btn_01_as.mp3");
}

void E002_Base_P420_CompletePopup::_onTouchedFinishBtn()
{
    stopAllNarration();
    
    playBtnEffect();
    playCommonNarration("e002_common_snd_btn_04_as.mp3");
}

void E002_Base_P420_CompletePopup::onTouchedReworkBtn()
{
    hidePopup();
}

void E002_Base_P420_CompletePopup::onTouchedFinishBtn()
{
    hidePopup();
}


void E002_Base_P420_CompletePopup::playBtnEffect()
{
    CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd","e002_common_sfx_btn_01.mp3"));
}
