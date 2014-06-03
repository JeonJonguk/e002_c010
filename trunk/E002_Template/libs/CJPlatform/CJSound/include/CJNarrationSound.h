 

#pragma once

#include "cocos2d.h"


USING_NS_CC;  


class CJNarrationSound
{

public:
     
    CJNarrationSound();
    ~CJNarrationSound();

    
    
    /**
     @brief Get the shared Engine object,it will new one when first time be called
     */
    static CJNarrationSound* getInstance();
    
    /**
     @brief Release the shared Engine object
     @warning It must be called before the application exit, or a memroy leak will be casued.
     */
     
    void    preloadNarration(std::string filePath);
//    void    playNarration(std::string filePath);
    void    playNarration(std::string filePath, bool bLoop = false);
    
    void    stopNarration(std::string filePath);
    
    void    pauseNarration(std::string filePath);
    
    void    resumeNarration(std::string filePath);
    
    void    playAllNarration(bool bLoop);
    void    pauseAllNarration();
    void    resumeAllNarration();
    void    stopAllNarration();
    void    removeAllNarration();

    bool    isNarrationPlaying(); 
   
    float   getNarrationMainVolume();
    void    setNarrationMainVolume(const float volume);
    void    setNarrationVolume(const float volume, std::string filePath);
    
    float   getNarrationTime(std::string filePath);
    float   getCurrentPosition(std::string filePath);
    
    void    unloadAllNarration();
    
//    void    onVoiceCallBack(const char*fileName);
    void    onVoiceCallBack(std::string fileName);
    void    audioPlayerCallbackPlay(void *player);
    void    audioPlayerCallbackPause(void *player);
    void    audioPlayerCallbackStop(void* audioPlayer);

    float   getDeviceVolume();
    
    
    void pauseToPlayingNarration();
    void resumePausedNarration();

    void callFunctionWithDelay(cocos2d::SEL_CallFuncND aSelector, float fDelayTime, void* data);
    void test(CCNode* sender, void *data);
};

