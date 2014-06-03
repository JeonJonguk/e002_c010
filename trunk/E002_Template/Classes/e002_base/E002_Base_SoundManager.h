//
//  E002_Base_SoundManager.h
//  SoundPhonics_Template
//
//  Created by Jeong.YJ on 13. 8. 8..
//
//

#ifndef E002_Template_E002_Base_SoundManager_h
#define E002_Template_E002_Base_SoundManager_h

#include "cocos2d.h"

class E002_Base_SoundManager
{
private:
    std::vector<std::string>        *mSuccessSfxName;
    std::vector<std::string>        *mWrongSfxName;
    std::vector<std::string>        *mRewardCreateSfxName;
    
    std::string                      mButtonSfxName;
    std::vector<std::string>        *mButtonNarName;
    
    std::vector<std::string>        *mAnisonCorrectNarr;
    std::vector<std::string>        *mBoomBoomCorrectNarr;
    std::vector<std::string>        *mRobotCorrectNarr;
    std::vector<std::string>        *mChuCorrectNars;
    std::vector<std::string>        *mGrumbieCorrectNars;
    
    std::vector<std::string>        *mAnisonWrongNarr;
    std::vector<std::string>        *mBoomBoomWrongNarr;
    std::vector<std::string>        *mRobotWrongNarr;
    std::vector<std::string>        *mChuWrongNars;
    std::vector<std::string>        *mGrumbieWrongNars;
    
    std::vector<std::string>        *mAnisonTouchNarr;
    std::vector<std::string>        *mBoomBoomTouchNarr;
    std::vector<std::string>        *mRobotTouchNarr;
    std::vector<std::string>        *mChuTouchNars;
    std::vector<std::string>        *mGrumbieTouchNars;
    
    
public:
    ~E002_Base_SoundManager();
    E002_Base_SoundManager();
    
    void playSuccessSfxSnd();
    void playWrongSfxSnd();
    void playRewardCreateSfxSnd();
    
    std::string playSuccessSfxSnd(int index, bool onlyFilePath = false);
    std::string playWrongSfxSnd(int index, bool onlyFilePath = false);
    std::string playRewardCreateSfxSnd(int index, bool onlyFilePath = false);
    
    void playButtonSfxSnd();
    //void playButtonNarrSnd(int index);
    
    std::string playSuccessNarr(int characterType);
    std::string playSuccessNarr(int characterType, int index, bool onlyFilePath = false);
    
    std::string playWrongNarr(int characterType);
    std::string playWrongNarr(int characterType, int index, bool onlyFilePath = false);
    
    std::string playTouchNarr(int characterType);
    std::string playTouchNarr(int characterType, int index , bool onlyFilePath = false);
    
    std::string playAnisonSuccessNarr();
    std::string playAnisonSuccessNarr(int index, bool onlyFilePath = false);
   
    std::string playBoomBoomSuccessNarr();
    std::string playBoomBoomSuccessNarr(int index, bool onlyFilePath = false);
    
    std::string playRobotSuccessNarr();
    std::string playRobotSuccessNarr(int index, bool onlyFilePath = false);
    
    std::string playChuSuccessNarr();
    std::string playChuSuccessNarr(int index, bool onlyFilePath = false);
    
    std::string playGrumbieSuccessNarr();
    std::string playGrumbieSuccessNarr(int index, bool onlyFilePath = false);

    std::string playAnisonWrongNarr();
    std::string playAnisonWrongNarr(int index, bool onlyFilePath = false);
    
    std::string playBoomBoomWrongNarr();
    std::string playBoomBoomWrongNarr(int index, bool onlyFilePath = false);
    
    std::string playRobotWrongNarr();
    std::string playRobotWrongNarr(int index, bool onlyFilePath = false);
    
    std::string playChuWrongNarr();
    std::string playChuWrongNarr(int index, bool onlyFilePath = false);
    
    std::string playGrumbieWrongNarr();
    std::string playGrumbieWrongNarr(int index, bool onlyFilePath = false);
    
    std::string playAnisonTouchNarr();
    std::string playAnisonTouchNarr(int index, bool onlyFilePath = false);
    
    std::string playBoomBoomTouchNarr();
    std::string playBoomBoomTouchNarr(int index, bool onlyFilePath = false);
    
    std::string playRobotTouchNarr();
    std::string playRobotTouchNarr(int index, bool onlyFilePath = false);
    
    std::string playChuTouchNarr();
    std::string playChuTouchNarr(int index, bool onlyFilePath = false);
    
    std::string playGrumbieTouchNarr();
    std::string playGrumbieTouchNarr(int index, bool onlyFilePath = false);
};
#endif
