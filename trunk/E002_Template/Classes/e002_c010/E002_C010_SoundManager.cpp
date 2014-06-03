//
//  E002_C010_SoundManager.cpp
//  E002_C010_Project
//
//  Created by smallsnail on 2014. 4. 1..
//
//

#include "E002_C010_SoundManager.h"

#include "CJMultimedia.h"
#include "CJUtils.h"


E002_C010_SoundManager::E002_C010_SoundManager()
{
    
    nCorrectIndex = 0;
    nWrongIndex = 0;
    
    mBGMs = new std::vector<std::string>();
//    mBGMs->push_back("e002_c010_snd_bgm_main.mp3");
    mBGMs->push_back("e002_c010_snd_bgm_01.mp3");
    mBGMs->push_back("e002_c010_snd_bgm_02.mp3");
    mBGMs->push_back("e002_c010_snd_bgm_03.mp3");
    mBGMs->push_back("e002_c010_snd_bgm_03_2.mp3");
    
    
    
    
    // Correct Narration ================================================================
    // Anison ===========================================================================
    mAnisonCorrectNarration = new std::vector<std::string>;
    //lesson1
    mAnisonCorrectNarration->push_back(getSndPath("e002_c010_p110_snd_correct_1_as.mp3"));
    mAnisonCorrectNarration->push_back(getSndPath("e002_c010_p110_snd_correct_2_as.mp3"));
    mAnisonCorrectNarration->push_back(getCommonSndPath("e002_common_snd_correct_03_as.mp3"));
    //lesson2
    mAnisonCorrectNarration->push_back(getSndPath("e002_c010_p210_snd_correct_01_as.mp3"));
    mAnisonCorrectNarration->push_back(getSndPath("e002_c010_p210_snd_correct_02_as.mp3"));
    mAnisonCorrectNarration->push_back(getCommonSndPath("e002_common_snd_correct_04_as.mp3"));
    //lesson3
    mAnisonCorrectNarration->push_back(getSndPath("e002_c010_p310_snd_correct_01_as.mp3"));
    mAnisonCorrectNarration->push_back(getSndPath("e002_c010_p310_snd_correct_02_as.mp3"));
    mAnisonCorrectNarration->push_back(getCommonSndPath("e002_common_snd_correct_10_as.mp3"));
    //lesson3-2
    mAnisonCorrectNarration->push_back(getCommonSndPath("e002_common_snd_correct_06_as.mp3"));
    mAnisonCorrectNarration->push_back(getCommonSndPath("e002_common_snd_correct_16_as.mp3"));
    mAnisonCorrectNarration->push_back(getCommonSndPath("e002_common_snd_correct_19_as.mp3"));
    
    
    mAnisonWrongNarration = new std::vector<std::string>;
    //lesson1 is null
    //lesson2
    mAnisonWrongNarration->push_back(getCommonSndPath("e002_common_snd_wrong_13_as.mp3"));
    mAnisonWrongNarration->push_back(getCommonSndPath("e002_common_snd_wrong_11_as.mp3"));
    mAnisonWrongNarration->push_back(getCommonSndPath("e002_common_snd_wrong_14_as.mp3"));
    //lesson3
    mAnisonWrongNarration->push_back(getCommonSndPath("e002_common_snd_wrong_05_as.mp3"));
    mAnisonWrongNarration->push_back(getCommonSndPath("e002_common_snd_wrong_13_as.mp3"));
    mAnisonWrongNarration->push_back(getCommonSndPath("e002_common_snd_wrong_01_as.mp3"));
    //lesson3-2
    mAnisonWrongNarration->push_back(getCommonSndPath("e002_common_snd_wrong_05_as.mp3"));
    mAnisonWrongNarration->push_back(getCommonSndPath("e002_common_snd_wrong_13_as.mp3"));
    mAnisonWrongNarration->push_back(getCommonSndPath("e002_common_snd_wrong_01_as.mp3"));
  
    
    //Other one ==========================================================================
    
    mOtherOneCorrentNarration = new std::vector<std::string>;
    //lesson1
    mOtherOneCorrentNarration->push_back(getSndPath("e002_c010_p110_snd_correct_3_gb.mp3"));
    mOtherOneCorrentNarration->push_back(getCommonSndPath("e002_common_snd_correct_24_gb.mp3"));
    mOtherOneCorrentNarration->push_back(getCommonSndPath("e002_common_snd_correct_25_gb.mp3"));
    //lesson2
    mOtherOneCorrentNarration->push_back(getSndPath("e002_c010_p210_snd_correct_03_bb.mp3"));
    mOtherOneCorrentNarration->push_back(getSndPath("e002_c010_p210_snd_correct_04_bb.mp3"));
    mOtherOneCorrentNarration->push_back(getSndPath("e002_c010_p210_snd_correct_05_bb.mp3"));
    //lesson3
    mOtherOneCorrentNarration->push_back(getSndPath("e002_c010_p310_snd_correct_01_ch.mp3"));
    mOtherOneCorrentNarration->push_back(getSndPath("e002_c010_p310_snd_correct_02_ch.mp3"));
    mOtherOneCorrentNarration->push_back(getSndPath("e002_c010_p310_snd_correct_03_ch.mp3"));
    //lesson3-2
    mOtherOneCorrentNarration->push_back(getSndPath("e002_c010_p320_snd_correct_01_ch.mp3"));
    mOtherOneCorrentNarration->push_back(getSndPath("e002_c010_p320_snd_correct_02_ch.mp3"));
    mOtherOneCorrentNarration->push_back(getCommonSndPath("e002_c010_p310_snd_correct_03_ch.mp3"));
    
 
    mOtherOneWrongNarration = new std::vector<std::string>;
    //lesson1 is null
    //lesson2
    mOtherOneWrongNarration->push_back(getCommonSndPath("e002_common_snd_wrong_04_bb.mp3"));
    mOtherOneWrongNarration->push_back(getCommonSndPath("e002_common_snd_wrong_12_bb.mp3"));
    mOtherOneWrongNarration->push_back(getSndPath("e002_c010_p210_snd_wrong_01_bb.mp3"));
    //lesson3
    mOtherOneWrongNarration->push_back(getSndPath("e002_c010_p310_snd_wrong_01_ch.mp3"));
    mOtherOneWrongNarration->push_back(getSndPath("e002_c010_p310_snd_wrong_02_ch.mp3"));
    mOtherOneWrongNarration->push_back(getSndPath("e002_c010_p310_snd_wrong_03_ch.mp3"));
    //lesson3-2
    mOtherOneWrongNarration->push_back(getSndPath("e002_c010_p320_snd_wrong_01_ch.mp3"));
    mOtherOneWrongNarration->push_back(getSndPath("e002_c010_p320_snd_wrong_02_ch.mp3"));
    mOtherOneWrongNarration->push_back(getSndPath("e002_c010_p320_snd_wrong_03_ch.mp3"));
    
}

E002_C010_SoundManager::~E002_C010_SoundManager()
{
    
    CC_SAFE_DELETE(mAnisonCorrectNarration);
    CC_SAFE_DELETE(mAnisonWrongNarration);
    CC_SAFE_DELETE(mOtherOneCorrentNarration);
    CC_SAFE_DELETE(mOtherOneWrongNarration);
}


void E002_C010_SoundManager::playBgm(eSndPageType sType)
{
    CJLog("SoundManager BGM : %s",CJUtils::getInstance()->getFilePath("snd",mBGMs->at(sType).c_str()).c_str());
    CJMultimedia::getInstance()->playBGM(CJUtils::getInstance()->getFilePath("snd",mBGMs->at(sType).c_str()), true);
}


#pragma mark - play correct & wrong
std::string E002_C010_SoundManager::playCorrectNarrationAnison(eSndPageType sType)
{
    int temp = _checkPageNum(sType);
    int index = temp*3 + (nCorrectIndex%3);
    std::string path = mAnisonCorrectNarration->at(index);
    CJMultimedia::getInstance()->playNarration(path.c_str());
    path =  CJUtils::getInstance()->stringTokenizer(path, "/", false);
    nCorrectIndex++;
    return path;
}


std::string E002_C010_SoundManager::playWrongNarrationAnison(eSndPageType sType)
{
    int temp = _checkPageNum(sType)-1;
    int index = temp*3 + (nWrongIndex%3);

    std::string path = mAnisonWrongNarration->at(index);
    CJMultimedia::getInstance()->playNarration(path.c_str());
    path =  CJUtils::getInstance()->stringTokenizer(path, "/", false);
    nWrongIndex++;
    return path;
}

std::string E002_C010_SoundManager::playCorrectNarrationOtherOne(eSndPageType sType)
{
    int temp = _checkPageNum(sType);
    int index = temp*3 + (nCorrectIndex%3);

    std::string path = mOtherOneCorrentNarration->at(index);
    CJMultimedia::getInstance()->playNarration(path.c_str());
    path =  CJUtils::getInstance()->stringTokenizer(path, "/", false);
    nCorrectIndex++;
    return path;
}

std::string E002_C010_SoundManager::playWrongNarrationOtherOne(eSndPageType sType)
{
    int temp = _checkPageNum(sType)-1;
    int index = temp*3 + (nWrongIndex%3);

    std::string path = mOtherOneWrongNarration->at(index);
    CJMultimedia::getInstance()->playNarration(path.c_str());
    path =  CJUtils::getInstance()->stringTokenizer(path, "/", false);
    nWrongIndex++;
    CJLog("path = %s",path.c_str());
    return path;
}




#pragma mark - utils
std::string E002_C010_SoundManager::getSndPath(std::string path)
{
    return CJUtils::getInstance()->getFilePath("snd", path);
}

std::string E002_C010_SoundManager::getCommonSndPath(std::string path)
{
    return CJUtils::getInstance()->getCommonFilePath("snd", path);
}

int E002_C010_SoundManager::_checkPageNum(eSndPageType sType)
{
    int temp = 0;
    switch (sType) {
        case p110:
            temp = 0;
            break;
        case p210:
            temp = 1;
            break;
        case p310:
            temp = 2;
            break;
        case p320:
            temp = 3;
            break;
        default:
            CJLog("E002_C010_SoundManager error = %d",sType);
            break;
    }
    return temp;

}
