//
//  CJMultimedia.h
//  CJ_Template
//
//  Created by Dongjin Park on 12. 10. 24..
//
//

#ifndef CJ_Template_CJMultimedia_h
#define CJ_Template_CJMultimedia_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CJDefines.h"


USING_NS_CC;
using namespace CocosDenshion;

class CJMultimedia
{
    
private:
    std::vector<std::string> *m_effectSounds;
    
public:
    
    CJMultimedia();
    ~CJMultimedia();
    
    static CJMultimedia* getInstance();
    
    void releaseMultimedia();

    void playBGM(std::string fileName, bool bLoop);
    void pauseBGM();
    void stopBGM();
    void resumeBGM();
    float getBGMVolume();
    void setBGMVolume(float pVolume);
    
    unsigned int playEffect(std::string fileName, bool bLoop = false);
    void pauseEffect(int soundId);
    void pauseAllEffects();
    void stopEffect(int soundId);
    void stopAllEffect();
    void resumeEffect(int soundId);
    void resumeAllEffects();
    void playEffectWithDelay(CCNode* sender, std::string filePath, float delay);
    void _playEffectWithDelayCallfunc(CCNode* sender, void* filePath);
    CCActionInstant* playEffectWithDelayCallfuncND(CCNode* sender, std::string fileName);

    void unloadAllEffects();
    
    void preloadNarration(std::string filePath);
    void playNarration(std::string filePath);
    void playNarration(std::string filePath, bool bLoop);
    void stopNarration(std::string filePath);
    void pauseNarration(std::string filePath);
    void resumeNarration(std::string filePath);
    void playNarrationWithDelay(CCNode* sender, std::string filePath, float delay);
    void _playNarrationWithDelayCallfunc(CCNode* sender, void* filePath);
    static CCActionInstant* playNarrationWithDelayCallfuncND(CCNode* sender, std::string fileName);
    
    void playAllNarration();
    void playAllNarration(bool bLoop);
    void pauseAllNarration();
    void resumeAllNarration();
    void stopAllNarration();
    void removeAllNarration();

    float getNarrationCurrentPosition(std::string filePath);
    float getNarrationTime(std::string filePath);
    
    bool isNarrationPlaying();
    float getNarrationMainVolume();
    void setNarrationMainVolume(const float volume); 
    void unloadAllNarration();
     
    void stopAllSound();
    void pauseAllSound();
    void resumeAllSound();
    void getPauseSounds(); 
    
    void unloadAllSounds();
    
    void pauseToPlayingNarration();
    void resumePausedNarration();
    
    //video
    void playVideo(std::string fileName, bool isControllerVisible);
    void pauseVideo();
    void resumeVideo();
    void stopVideo();
    void addButtonVideo(std::string btnPath, float x, float y, int tag);
    void playFrameVideo(std::string frameImgPath, std::string contentPath, int x, int y, int width, int height);
    void removeFrameVideo();
    
    //camera
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    void setGallerySession();
    bool getGallerySession();
    void saveToPhotoLibraryWithFileName(std::string strFileName);
#endif
    
    
    void showCameraPreview(std::string frameImgPath, int direction, int x, int y, int width, int height);
    void takePicture();
    void startVideoRecording(std::string contentPath);
    void stopVideoRecording();
    void removeCameraView();
    bool isShowCameraPreivew();
    void moveToCameraView(int x, int y);
    
    //sound recording
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    void setRecSession();
    bool getRecSession();
#endif
    void startVoiceRecording(std::string filePath = "");
    void stopVoiceRecording();
    void pauseVoiceRecording();
    void resumeVoiceRecording();
    
    
    void playRecordedVoice(std::string filePath = "");
    void stopRecordedVoice();
    void pauseRecordedVoice();
    void resumeRecordedVoice();
    
    float getDeviceVolume();
    
    
    void showBrowser(std::string pszURL); 
};


#endif
