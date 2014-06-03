//
//  E001_C110_Success_Snd.cpp
//  SoundPhonics_Template
//
//  Created by Jeong.YJ on 13. 8. 8..
//
//

#include "E002_Base_SoundManager.h"
#include "CJMultimedia.h"
#include "CJUtils.h"

#define NARRATION_CHARACTER_TYPE_ANISON    100
#define NARRATION_CHARACTER_TYPE_BOOMBOOM  101
#define NARRATION_CHARACTER_TYPE_ROBOT     102
#define NARRATION_CHARACTER_TYPE_CHU       103
#define NARRATION_CHARACTER_TYPE_GRUMBIE   104

E002_Base_SoundManager::E002_Base_SoundManager()
{
    //Success(Correct) Sound Effect
    mSuccessSfxName = new std::vector<std::string>();
    
    for (int i = 1 ; i < 14; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_sfx_correct_%02d.mp3", i);
        mSuccessSfxName->push_back(name);
    }
    
    //Touch Sound Effect
    mWrongSfxName = new std::vector<std::string>();
    
    for (int i = 1 ; i < 14; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_sfx_wrong_%02d.mp3", i);
        mWrongSfxName->push_back(name);
    }
    
    //Reward Create Sound Effect
    mRewardCreateSfxName = new std::vector<std::string>();
    
    for (int i = 1 ; i < 4; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_sfx_reward_%02d.mp3", i);
        mRewardCreateSfxName->push_back(name);
    }

    //Default Button Touch Sound Effect
    mButtonSfxName = CJUtils::getInstance()->getCommonFilePath("snd","e002_common_sfx_btn_01.mp3").c_str();
    
    mButtonNarName = new std::vector<std::string>;
    
    for (int i = 1 ; i < 14; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_btn_%02d_as.mp3", i);
        mButtonNarName->push_back(name);
    }
    
    mAnisonCorrectNarr = new std::vector<std::string>;
    
    for (int i = 1 ; i < 29; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_correct_%02d_as.mp3", i);
        mAnisonCorrectNarr->push_back(name);
    }
    
    mBoomBoomCorrectNarr = new std::vector<std::string>;
    
    for (int i = 1 ; i < 29; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_correct_%02d_bb.mp3", i);
        mBoomBoomCorrectNarr->push_back(name);
    }

    mRobotCorrectNarr = new std::vector<std::string>;
    
    for (int i = 1 ; i < 29; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_correct_%02d_ar.mp3", i);
        mRobotCorrectNarr->push_back(name);
    }
    
    mChuCorrectNars = new std::vector<std::string>;
    
    for (int i = 1 ; i < 29; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_correct_%02d_ch.mp3", i);
        mChuCorrectNars->push_back(name);
    }
    
    mGrumbieCorrectNars = new std::vector<std::string>;
    
    for (int i = 1 ; i < 29; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_correct_%02d_gb.mp3", i);
        mGrumbieCorrectNars->push_back(name);
    }
    
    mAnisonWrongNarr = new std::vector<std::string>;
    
    for (int i = 1 ; i < 16; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_wrong_%02d_as.mp3", i);
        mAnisonWrongNarr->push_back(name);
    }
    
    mBoomBoomWrongNarr = new std::vector<std::string>;
    
    for (int i = 1 ; i < 16; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_wrong_%02d_bb.mp3", i);
        mBoomBoomWrongNarr->push_back(name);
    }
    
    mRobotWrongNarr = new std::vector<std::string>;
    
    for (int i = 1 ; i < 16; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_wrong_%02d_ar.mp3", i);
        mRobotWrongNarr->push_back(name);
    }
    
    mChuWrongNars = new std::vector<std::string>;
    
    for (int i = 1 ; i < 16; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_wrong_%02d_ch.mp3", i);
        mChuWrongNars->push_back(name);
    }
    
    mGrumbieWrongNars = new std::vector<std::string>;
    
    for (int i = 1 ; i < 16; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_wrong_%02d_gb.mp3", i);
        mGrumbieWrongNars->push_back(name);
    }
    
    mAnisonTouchNarr = new std::vector<std::string>;
    
    for (int i = 1 ; i < 11; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_loop_%02d_as.mp3", i);
        mAnisonTouchNarr->push_back(name);
    }
    
    mBoomBoomTouchNarr = new std::vector<std::string>;
    
    for (int i = 1 ; i < 11; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_loop_%02d_bb.mp3", i);
        mBoomBoomTouchNarr->push_back(name);
    }
    
    mRobotTouchNarr = new std::vector<std::string>;
    
    for (int i = 1 ; i < 11; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_loop_%02d_ar.mp3", i);
        mRobotTouchNarr->push_back(name);
    }
    
    mChuTouchNars = new std::vector<std::string>;
    
    for (int i = 1 ; i < 11; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_loop_%02d_ch.mp3", i);
        mChuTouchNars->push_back(name);
    }
    
    mGrumbieTouchNars = new std::vector<std::string>;
    
    for (int i = 1 ; i < 11; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_common_snd_loop_%02d_gb.mp3", i);
        mGrumbieTouchNars->push_back(name);
    }
}

E002_Base_SoundManager::~E002_Base_SoundManager()
{
    CC_SAFE_DELETE(mSuccessSfxName);
    CC_SAFE_DELETE(mWrongSfxName);
    CC_SAFE_DELETE(mRewardCreateSfxName);
}

void E002_Base_SoundManager::playSuccessSfxSnd()
{
    CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd", mSuccessSfxName->at(rand()%mSuccessSfxName->size()).c_str()));
}

void E002_Base_SoundManager::playWrongSfxSnd()
{
    CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd", mWrongSfxName->at(rand()%mWrongSfxName->size()).c_str()));
}

void E002_Base_SoundManager::playRewardCreateSfxSnd()
{
    CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd", mRewardCreateSfxName->at(rand()%mRewardCreateSfxName->size()).c_str()));
}

std::string E002_Base_SoundManager::playSuccessSfxSnd(int index, bool onlyFilePath)
{
    std::string filePath = mSuccessSfxName->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd", filePath.c_str()));
    
    return filePath;
}

std::string E002_Base_SoundManager::playWrongSfxSnd(int index, bool onlyFilePath)
{
    std::string filePath = mWrongSfxName->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd", filePath.c_str()));
    
    return filePath;
}

std::string E002_Base_SoundManager::playRewardCreateSfxSnd(int index, bool onlyFilePath)
{
    std::string filePath = mRewardCreateSfxName->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getCommonFilePath("snd", mRewardCreateSfxName->at(index - 1).c_str()));
    
    return filePath;
}

void E002_Base_SoundManager::playButtonSfxSnd()
{
    CJMultimedia::getInstance()->playEffect(mButtonSfxName);
}

std::string E002_Base_SoundManager::playSuccessNarr(int characterType)
{
    std::string sndPath;
    
    switch (characterType)
    {
        case NARRATION_CHARACTER_TYPE_ANISON:
            sndPath = mAnisonCorrectNarr->at(rand()%mAnisonCorrectNarr->size());
            break;
        case NARRATION_CHARACTER_TYPE_BOOMBOOM:
            sndPath = mBoomBoomCorrectNarr->at(rand()%mBoomBoomCorrectNarr->size());
            break;
        case NARRATION_CHARACTER_TYPE_ROBOT:
            sndPath = mRobotCorrectNarr->at(rand()%mRobotCorrectNarr->size());
            break;
        case NARRATION_CHARACTER_TYPE_CHU:
            sndPath = mChuCorrectNars->at(rand()%mChuCorrectNars->size());
            break;
        case NARRATION_CHARACTER_TYPE_GRUMBIE:
            sndPath = mGrumbieCorrectNars->at(rand()%mGrumbieCorrectNars->size());
            break;
        default:
            break;
    }
    
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());

    return sndPath;
}

std::string E002_Base_SoundManager::playSuccessNarr(int characterType, int index, bool onlyFilePath)
{
    std::string sndPath;
    index -= 1;
    
    switch (characterType)
    {
        case NARRATION_CHARACTER_TYPE_ANISON:
            sndPath = mAnisonCorrectNarr->at(index);
            break;
        case NARRATION_CHARACTER_TYPE_BOOMBOOM:
            sndPath = mBoomBoomCorrectNarr->at(index);
            break;
        case NARRATION_CHARACTER_TYPE_ROBOT:
            sndPath = mRobotCorrectNarr->at(index);
            break;
        case NARRATION_CHARACTER_TYPE_CHU:
            sndPath = mChuCorrectNars->at(index);
            break;
        case NARRATION_CHARACTER_TYPE_GRUMBIE:
            sndPath = mGrumbieCorrectNars->at(index);
            break;
        default:
            break;
    }
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playWrongNarr(int characterType)
{
    std::string sndPath;
    
    switch (characterType)
    {
        case NARRATION_CHARACTER_TYPE_ANISON:
            sndPath = mAnisonWrongNarr->at(rand()%mAnisonWrongNarr->size());
            break;
        case NARRATION_CHARACTER_TYPE_BOOMBOOM:
            sndPath = mBoomBoomWrongNarr->at(rand()%mBoomBoomWrongNarr->size());
            break;
        case NARRATION_CHARACTER_TYPE_ROBOT:
            sndPath = mRobotWrongNarr->at(rand()%mRobotWrongNarr->size());
            break;
        case NARRATION_CHARACTER_TYPE_CHU:
            sndPath = mChuWrongNars->at(rand()%mChuWrongNars->size());
            break;
        case NARRATION_CHARACTER_TYPE_GRUMBIE:
            sndPath = mGrumbieWrongNars->at(rand()%mGrumbieWrongNars->size());
            break;
        default:
            break;
    }
    
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playWrongNarr(int characterType, int index, bool onlyFilePath)
{
    std::string sndPath;
    
    index -= 1;
    
    switch (characterType)
    {
        case NARRATION_CHARACTER_TYPE_ANISON:
            sndPath = mAnisonWrongNarr->at(index);
            break;
        case NARRATION_CHARACTER_TYPE_BOOMBOOM:
            sndPath = mBoomBoomWrongNarr->at(index);
            break;
        case NARRATION_CHARACTER_TYPE_ROBOT:
            sndPath = mRobotWrongNarr->at(index);
            break;
        case NARRATION_CHARACTER_TYPE_CHU:
            sndPath = mChuWrongNars->at(index);
            break;
        case NARRATION_CHARACTER_TYPE_GRUMBIE:
            sndPath = mGrumbieWrongNars->at(index);
            break;
        default:
            break;
    }
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playTouchNarr(int characterType)
{
    std::string sndPath;
    
    switch (characterType)
    {
        case NARRATION_CHARACTER_TYPE_ANISON:
            sndPath = mAnisonTouchNarr->at(rand()%mAnisonTouchNarr->size());
            break;
        case NARRATION_CHARACTER_TYPE_BOOMBOOM:
            sndPath = mBoomBoomTouchNarr->at(rand()%mBoomBoomTouchNarr->size());
            break;
        case NARRATION_CHARACTER_TYPE_ROBOT:
            sndPath = mRobotTouchNarr->at(rand()%mRobotTouchNarr->size());
            break;
        case NARRATION_CHARACTER_TYPE_CHU:
            sndPath = mChuTouchNars->at(rand()%mChuTouchNars->size());
            break;
        case NARRATION_CHARACTER_TYPE_GRUMBIE:
            sndPath = mGrumbieTouchNars->at(rand()%mGrumbieTouchNars->size());
            break;
        default:
            break;
    }
    
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playTouchNarr(int characterType, int index, bool onlyFilePath)
{
    std::string sndPath;
    
    index -= 1;
    
    switch (characterType)
    {
        case NARRATION_CHARACTER_TYPE_ANISON:
            sndPath = mAnisonTouchNarr->at(index);
            break;
        case NARRATION_CHARACTER_TYPE_BOOMBOOM:
            sndPath = mBoomBoomTouchNarr->at(index);
            break;
        case NARRATION_CHARACTER_TYPE_ROBOT:
            sndPath = mRobotTouchNarr->at(index);
            break;
        case NARRATION_CHARACTER_TYPE_CHU:
            sndPath = mChuTouchNars->at(index);
            break;
        case NARRATION_CHARACTER_TYPE_GRUMBIE:
            sndPath = mGrumbieTouchNars->at(index);
            break;
        default:
            break;
    }
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playAnisonSuccessNarr()
{
    std::string sndPath = mAnisonCorrectNarr->at(rand()%mAnisonCorrectNarr->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playAnisonSuccessNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mAnisonCorrectNarr->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playBoomBoomSuccessNarr()
{
    std::string sndPath = mBoomBoomCorrectNarr->at(rand()%mBoomBoomCorrectNarr->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playBoomBoomSuccessNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mBoomBoomCorrectNarr->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playRobotSuccessNarr()
{
    std::string sndPath = mRobotCorrectNarr->at(rand()%mRobotCorrectNarr->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playRobotSuccessNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mRobotCorrectNarr->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playChuSuccessNarr()
{
    std::string sndPath = mChuCorrectNars->at(rand()%mChuCorrectNars->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playChuSuccessNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mChuCorrectNars->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playGrumbieSuccessNarr()
{
    std::string sndPath = mGrumbieCorrectNars->at(rand()%mGrumbieCorrectNars->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playGrumbieSuccessNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mGrumbieCorrectNars->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playAnisonWrongNarr()
{
    std::string sndPath = mAnisonWrongNarr->at(rand()%mAnisonWrongNarr->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playAnisonWrongNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mAnisonWrongNarr->at(index - 1);
 
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playBoomBoomWrongNarr()
{
    std::string sndPath = mBoomBoomWrongNarr->at(rand()%mBoomBoomWrongNarr->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playBoomBoomWrongNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mBoomBoomWrongNarr->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playRobotWrongNarr()
{
    std::string sndPath = mRobotWrongNarr->at(rand()%mRobotWrongNarr->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playRobotWrongNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mRobotWrongNarr->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playChuWrongNarr()
{
    std::string sndPath = mChuWrongNars->at(rand()%mChuWrongNars->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playChuWrongNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mChuWrongNars->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playGrumbieWrongNarr()
{
    std::string sndPath = mGrumbieWrongNars->at(rand()%mGrumbieWrongNars->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playGrumbieWrongNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mGrumbieWrongNars->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playAnisonTouchNarr()
{
    std::string sndPath = mAnisonTouchNarr->at(rand()%mAnisonTouchNarr->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playAnisonTouchNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mAnisonTouchNarr->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playBoomBoomTouchNarr()
{
    std::string sndPath = mBoomBoomTouchNarr->at(rand()%mBoomBoomTouchNarr->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playBoomBoomTouchNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mBoomBoomTouchNarr->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playRobotTouchNarr()
{
    std::string sndPath = mRobotTouchNarr->at(rand()%mRobotTouchNarr->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playRobotTouchNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mRobotTouchNarr->at(index);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playChuTouchNarr()
{
    std::string sndPath = mChuTouchNars->at(rand()%mChuTouchNars->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playChuTouchNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mChuTouchNars->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playGrumbieTouchNarr()
{
    std::string sndPath = mGrumbieTouchNars->at(rand()%mGrumbieTouchNars->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_Base_SoundManager::playGrumbieTouchNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mGrumbieTouchNars->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getCommonFilePath("snd", sndPath).c_str());
    
    return sndPath;
}