//
//  E002_C010_SoundManager.h
//  E002_C010_Project
//
//  Created by smallsnail on 2014. 4. 1..
//
//

#ifndef E002_C010_Project_E002_C010_SoundManager_h
#define E002_C010_Project_E002_C010_SoundManager_h

#include "E002_Base_SoundManager.h"
class E002_C010_SoundManager : public E002_Base_SoundManager
{
public:
    enum eSndPageType{
        p110,
        p210,
        p310,
        p320,
    };
    
private:
    int                             nCorrectIndex;
    int                             nWrongIndex;
    
    std::vector<std::string>        *mBGMs;

    std::vector<std::string>        *mAnisonCorrectNarration;
    std::vector<std::string>        *mAnisonWrongNarration;
    
    std::vector<std::string>        *mOtherOneCorrentNarration;
    std::vector<std::string>        *mOtherOneWrongNarration;
public:
    
    ~E002_C010_SoundManager();
    E002_C010_SoundManager();
    
    void playBgm(eSndPageType sType);
    
    std::string playCorrectNarrationAnison(eSndPageType sType);
    std::string playWrongNarrationAnison(eSndPageType sType);
    std::string playCorrectNarrationOtherOne(eSndPageType sType);
    std::string playWrongNarrationOtherOne(eSndPageType sType);
    
    //util
    std::string getSndPath(std::string path);
    std::string getCommonSndPath(std::string path);
    int _checkPageNum(eSndPageType sType);
};

#endif
