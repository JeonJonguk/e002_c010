//
//  E001_C110_Success_Snd.h
//  SoundPhonics_Template
//
//  Created by Jeong.YJ on 13. 8. 8..
//
//

#ifndef E002_Template_E002_C030_SoundManager_h
#define E002_Template_E002_C030_SoundManager_h

#include "E002_Base_SoundManager.h"

class E002_C030_SoundManager : public E002_Base_SoundManager
{
private:
    std::vector<std::string>        *mLetsPlay1SfxName;
    std::vector<std::string>        *mLetsPlay2SfxName;
    std::vector<std::string>        *mLetsPlay3SfxName;
    
    std::vector<std::string>        *mLetsPlay1NarrName;
    std::vector<std::string>        *mLetsPlay2NarrName;
    std::vector<std::string>        *mLetsPlay3NarrName;
    
    std::vector<std::string>        *mMeercatCorrectNarr;
    std::vector<std::string>        *mMeercatWrongNarr;
    
public:
    
    ~E002_C030_SoundManager();
    E002_C030_SoundManager();
    
    std::string playLetsPlay1Effect(int index, bool onlyFilePath = false);
    std::string playLetsPlay2Effect(int index, bool onlyFilePath = false);
    std::string playLetsPlay3Effect(int index, bool onlyFilePath = false);

    std::string playMeercatSuccessNarr();
    std::string playMeercatSuccessNarr(int index, bool onlyFilePath = false);
    
    std::string playMeercatWrongNarr();
    std::string playMeercatWrongNarr(int index, bool onlyFilePath = false);

    std::string playLetsPlay1Narration(int index, bool onlyFilePath = false);
    std::string playLetsPlay2Narration(int index, bool onlyFilePath = false);
    std::string playLetsPlay3Narration(int index, bool onlyFilePath = false);
};
#endif
