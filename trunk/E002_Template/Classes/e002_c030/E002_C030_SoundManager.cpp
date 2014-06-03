//
//  E002_C030_SoundManager.cpp
//  E002_Template
//
//  Created by Jeong.YJ on 13. 8. 8..
//
//

#include "E002_C030_SoundManager.h"
#include "CJMultimedia.h"
#include "CJUtils.h"


E002_C030_SoundManager::E002_C030_SoundManager()
{
    mLetsPlay1SfxName = new std::vector<std::string>();
    
    const char* letsPlay1[14] =
    {
        //Questions
        "e002_c030_p110_sfx_appear.mp3",             // 0
        "e002_c030_p110_sfx_wall_tap_02.mp3",        // 1
        "e002_c030_p110_sfx_wall_tap.mp3",           // 2
        "e002_c030_p110_sfx_wall_appear.mp3",        // 3
        "e002_c030_p000_action_sfx_correct_mk.mp3",  // 4
        "e002_c030_p000_action_sfx_correct_as.mp3",  // 5
        "e002_c030_p000_action_sfx_wrong_as.mp3",    // 6
        "e002_c030_p000_sfx_reward_item.mp3",        // 7
        
        //Reward
        "e002_c030_p130_sfx_run01.mp3",              // 8
        "e002_c030_p130_sfx_appear_mk.mp3",          // 9
        "e002_c030_p130_sfx_item.mp3",               // 10
        "e002_c030_p130_sfx_correct_piece.mp3",      // 11
        "e002_c030_p130_sfx_wrong_piece.mp3",        // 12
        "e002_c030_p130_sfx_completion.mp3"          // 13
    };
    
    for (int i = 0 ; i < 14; i++)
    {
        mLetsPlay1SfxName->push_back(letsPlay1[i]);
    }
    
    memset(letsPlay1, 0, sizeof(letsPlay1));
    
    mLetsPlay2SfxName = new std::vector<std::string>();
    
    const char* letsPlay2[15] =
    {
        //Questions
        "e002_c030_p210_sfx_card_app.mp3",          // 0
        "e002_c030_p210_sfx_card_open.mp3",         // 1
        "e002_c030_p210_sfx_move.mp3",              // 2
        "e002_c030_p210_sfx_card_in.mp3",           // 3
        "e002_c030_p210_sfx_card_open.mp3",         // 4
        "e002_c030_p000_sfx_reward_item.mp3",       // 5
        
        //Reward
        "e002_c030_p130_sfx_appear_mk.mp3",         // 6
        "e002_c030_p130_sfx_item.mp3",              // 7
        "e002_c030_p130_sfx_correct_piece.mp3",     // 8
        "e002_c030_p130_sfx_wrong_piece.mp3",       // 9
        "e002_c030_p130_sfx_completion.mp3",        // 10
        "e002_c030_p230_sfx_grip.mp3",              // 11
        "e002_c030_p230_sfx_jump_ar.mp3",           // 12
        "e002_c030_p230_sfx_jump_as.mp3",           // 13
        "e002_c030_p230_sfx_door_open.mp3",         // 14
    };
    
    for (int i = 0 ; i < 15; i++)
    {
        mLetsPlay2SfxName->push_back(letsPlay2[i]);
    }
    
    memset(letsPlay2, 0, sizeof(letsPlay2));

    mLetsPlay3SfxName = new std::vector<std::string>();
    
    const char* letsPlay3[14] =
    {
       //Questions
        "e002_c030_p310_intro_sfx_wheel.mp3",         // 0
        "e002_c030_p310_intro_sfx_wheel_rotate.mp3",  // 1
        "e002_c030_p130_sfx_run01.mp3",               // 2
        "e002_c030_p000_sfx_reward_item.mp3",         // 3
        
        //Reward
        "e002_c030_p130_sfx_appear_mk.mp3",           // 4
        "e002_c030_p130_sfx_item.mp3",                // 5
        "e002_c030_p130_sfx_correct_piece.mp3",       // 6
        "e002_c030_p130_sfx_wrong_piece.mp3",         // 7
        "e002_c030_p130_sfx_completion.mp3",          // 8
        "e002_c030_p330_sfx_fold.mp3",                // 9
        "e002_c030_p330_sfx_beam.mp3",                // 10
        
        //Ending
        "e002_c030_p300_ending_sfx_up.mp3",           // 11
        "e002_c030_p300_ending_sfx_move.mp3",         // 12
        "e002_c030_p300_ending_sfx_beam.mp3",         // 13

    };
    
    for (int i = 0 ; i < 14; i++)
    {
        mLetsPlay3SfxName->push_back(letsPlay3[i]);
    }
    
    memset(letsPlay3, 0, sizeof(letsPlay3));
    
    mLetsPlay1NarrName = new std::vector<std::string>();
    
    const char* letsPlay1Narr[2] =
    {
        "e002_c030_p110_snd_01_mk.mp3",           // 0
        "e002_c030_p130_snd_01_mk.mp3.mp3",       // 1
    };
    
    for (int i = 0 ; i < 2; i++)
    {
        mLetsPlay1NarrName->push_back(letsPlay1Narr[i]);
    }
    
    memset(letsPlay1Narr, 0, sizeof(letsPlay1Narr));
    
    mLetsPlay2NarrName = new std::vector<std::string>();
    
    const char* letsPlay2Narr[3] =
    {
        "e002_c030_p210_snd_01_mk.mp3",           // 0
        "e002_c030_p210_snd_02_mk.mp3",           // 1
        "e002_c030_p210_snd_03_mk.mp3",           // 2
    };
    
    for (int i = 0 ; i < 3; i++)
    {
        mLetsPlay2NarrName->push_back(letsPlay2Narr[i]);
    }
    
    memset(letsPlay2Narr, 0, sizeof(letsPlay2Narr));
    
    mLetsPlay3NarrName = new std::vector<std::string>();
    
    const char* letsPlay3Narr[4] =
    {
        "e002_c030_p310_snd_01_mk.mp3",           // 0
        "e002_c030_p320_snd_01_mk.mp3",           // 1
        "e002_c030_p320_snd_02_mk.mp3",           // 2
        "e002_c030_p330_snd_01_mk.mp3",           // 3
    };
    
    for (int i = 0 ; i < 4; i++)
    {
        mLetsPlay3NarrName->push_back(letsPlay3Narr[i]);
    }
    
    memset(letsPlay3Narr, 0, sizeof(letsPlay3Narr));
    
    mMeercatCorrectNarr = new std::vector<std::string>;
    
    for (int i = 1 ; i < 29; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_c030_common_snd_correct_%02d_mk.mp3", i);
        mMeercatCorrectNarr->push_back(name);
    }
    
    mMeercatWrongNarr = new std::vector<std::string>;
    
    for (int i = 1 ; i < 16; i++)
    {
        std::string name = CJUtils::getStringFormatInteger("e002_c030_common_snd_wrong_%02d_mk.mp3", i);
        mMeercatWrongNarr->push_back(name);
    }
}

E002_C030_SoundManager::~E002_C030_SoundManager()
{ 
    CC_SAFE_DELETE(mLetsPlay1SfxName);
    CC_SAFE_DELETE(mLetsPlay2SfxName);
    CC_SAFE_DELETE(mLetsPlay3SfxName);
}

std::string E002_C030_SoundManager::playLetsPlay1Effect(int index, bool onlyFilePath)
{
    std::string sndPath = mLetsPlay1SfxName->at(index);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getFilePath("snd", sndPath.c_str()));
    
    return sndPath;
}

std::string E002_C030_SoundManager::playLetsPlay2Effect(int index, bool onlyFilePath)
{
    std::string sndPath = mLetsPlay2SfxName->at(index);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getFilePath("snd", sndPath.c_str()));
    
    return sndPath;
}

std::string E002_C030_SoundManager::playLetsPlay3Effect(int index, bool onlyFilePath)
{
    std::string sndPath = mLetsPlay3SfxName->at(index);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playEffect(CJUtils::getInstance()->getFilePath("snd", sndPath.c_str()));
    
    return sndPath;
}

std::string E002_C030_SoundManager::playMeercatSuccessNarr()
{
    std::string sndPath = mMeercatCorrectNarr->at(rand()%mMeercatCorrectNarr->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_C030_SoundManager::playMeercatSuccessNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mMeercatCorrectNarr->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_C030_SoundManager::playMeercatWrongNarr()
{
    std::string sndPath = mMeercatWrongNarr->at(rand()%mMeercatWrongNarr->size());
    CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_C030_SoundManager::playMeercatWrongNarr(int index, bool onlyFilePath)
{
    std::string sndPath = mMeercatWrongNarr->at(index - 1);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getFilePath("snd", sndPath).c_str());
    
    return sndPath;
}

std::string E002_C030_SoundManager::playLetsPlay1Narration(int index, bool onlyFilePath)
{
    std::string sndPath = mLetsPlay1NarrName->at(index);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getFilePath("snd", sndPath.c_str()));
    
    return sndPath;
}

std::string E002_C030_SoundManager::playLetsPlay2Narration(int index, bool onlyFilePath)
{
    std::string sndPath = mLetsPlay2NarrName->at(index);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getFilePath("snd", sndPath.c_str()));
    
    return sndPath;
}

std::string E002_C030_SoundManager::playLetsPlay3Narration(int index, bool onlyFilePath)
{
    std::string sndPath = mLetsPlay3NarrName->at(index);
    
    if(!onlyFilePath)
        CJMultimedia::getInstance()->playNarration(CJUtils::getInstance()->getFilePath("snd", sndPath.c_str()));
    
    return sndPath;
}
