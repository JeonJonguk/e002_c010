//
//  CJMultimedia.cpp
//  SoundPhonics_Template
//
//  Created by Jeong.YJ on 13. 5. 9..
//
//

#include "CJMultimedia.h" 
#include "CJNarrationSound.h"
#include "CJVideoInterface.h"
#include "CJCameraInterface.h"
#include "CJVoiceRecorderInterface.h"
#include "CJUriConnection.h"
#include "CJUtils.h"

static CJMultimedia *m_spMultimedia;

CJMultimedia::CJMultimedia()
{
    m_effectSounds = new std::vector<std::string>();
}

CJMultimedia::~CJMultimedia()
{
    unloadAllSounds();
    delete m_effectSounds; 
    
    releaseMultimedia();
}

CJMultimedia* CJMultimedia::getInstance()
{
    if(!m_spMultimedia)
    {
        m_spMultimedia  = new CJMultimedia();
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0);
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0);
    }
    
    return m_spMultimedia;
}

void CJMultimedia::releaseMultimedia()
{
    if (m_spMultimedia)
    {
        delete m_spMultimedia;
        m_spMultimedia = NULL;
    }
}

float CJMultimedia::getDeviceVolume()
{
    return CJNarrationSound::getInstance()->getDeviceVolume();
}

#pragma mark - Sound Multimedia
#pragma mark - Control Sound
void CJMultimedia::unloadAllSounds()
{
    if(m_effectSounds->size()==0)
        return;
    
    for(int i = 0; i < m_effectSounds->size(); i++)
    {
        SimpleAudioEngine::sharedEngine()->unloadEffect((char*)m_effectSounds->at(i).c_str());
    }
    
    if(m_effectSounds->size()>0)
    {
        m_effectSounds->clear();
    }
    
    unloadAllNarration();
}

void CJMultimedia::unloadAllEffects()
{
    if(m_effectSounds->size()==0)
        return;
    
    for(int i = 0; i < m_effectSounds->size(); i++)
    {
        SimpleAudioEngine::sharedEngine()->unloadEffect((char*)m_effectSounds->at(i).c_str());
    }
    
    if(m_effectSounds->size()>0)
    {
        m_effectSounds->clear();
    }
}

void CJMultimedia::stopAllSound()
{
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    stopBGM();
    stopAllNarration();
}

void CJMultimedia::pauseAllSound()
{
    pauseAllEffects();
    pauseBGM();
    pauseAllNarration();

}

void CJMultimedia::resumeAllSound()
{
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    resumeBGM();
    resumeAllNarration();
}


void CJMultimedia::getPauseSounds()
{
    
}



#pragma mark - BGM

void CJMultimedia::playBGM(std::string fileName, bool bLoop)
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(fileName.c_str(), bLoop);

}

void CJMultimedia::pauseBGM()
{
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void CJMultimedia::stopBGM()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void CJMultimedia::resumeBGM()
{
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


float CJMultimedia::getBGMVolume()
{
    return SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}

void CJMultimedia::setBGMVolume(float pVolume)
{
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(pVolume);
}

#pragma mark - Effect

unsigned int CJMultimedia::playEffect(std::string fileName, bool bLoop)
{
	unsigned int soundId;
    
    soundId = SimpleAudioEngine::sharedEngine()->playEffect(fileName.c_str(), bLoop);
    
    m_effectSounds->push_back(fileName);
    
	return soundId;
}

void CJMultimedia::pauseEffect(int soundId)
{
    SimpleAudioEngine::sharedEngine()->pauseEffect(soundId);
}

void CJMultimedia::pauseAllEffects()
{
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

void CJMultimedia::stopEffect(int soundId)
{
    SimpleAudioEngine::sharedEngine()->stopEffect(soundId);
}

void CJMultimedia::stopAllEffect()
{
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

void CJMultimedia::resumeEffect(int soundId)
{
    SimpleAudioEngine::sharedEngine()->resumeEffect(soundId);
}

void CJMultimedia::resumeAllEffects()
{
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

void CJMultimedia::playEffectWithDelay(CCNode* sender, std::string fileName, float delay)
{
    if (delay != 0) {
        
        sender->runAction(CCSequence::create(CCDelayTime::create(delay),
                                             CCCallFuncND::create(sender, callfuncND_selector(CJMultimedia::_playEffectWithDelayCallfunc),new CCString(fileName)),
                                             NULL));
    }
    else{
        playEffect(fileName);
    }
}

CCActionInstant* CJMultimedia::playEffectWithDelayCallfuncND(CCNode* sender, std::string fileName )
{
    CCActionInstant* soundCallfunc;
    soundCallfunc = CCCallFuncND::create(sender, callfuncND_selector(CJMultimedia::_playEffectWithDelayCallfunc), new CCString(fileName));
    return soundCallfunc;
}


void CJMultimedia::_playEffectWithDelayCallfunc(CCNode* sender, void* filePath)
{
    CCString *fileName = (CCString *)filePath;
    CJMultimedia::getInstance()->playEffect(fileName->getCString());
//    fileName->release();
    CC_SAFE_DELETE(fileName);
}

#pragma mark - Narration

void CJMultimedia::preloadNarration(std::string fileName)
{
    CJNarrationSound::getInstance()->preloadNarration(fileName);
}

void CJMultimedia::playNarration(std::string fileName)
{
    playNarration(fileName, false);
}

void CJMultimedia::playNarration(std::string fileName, bool bLoop)
{
    CJNarrationSound::getInstance()->playNarration(fileName, bLoop);
}

void CJMultimedia::stopNarration(std::string fileName)
{
    CJNarrationSound::getInstance()->stopNarration(fileName);
}

void CJMultimedia::pauseNarration(std::string fileName)
{
    CJNarrationSound::getInstance()->pauseNarration(fileName);
}

void CJMultimedia::resumeNarration(std::string fileName)
{
    CJNarrationSound::getInstance()->resumeNarration(fileName);
}

float CJMultimedia::getNarrationCurrentPosition(std::string filePath)
{
    return CJNarrationSound::getInstance()->getCurrentPosition(filePath);
}

float CJMultimedia::getNarrationTime(std::string filePath)
{
    return CJNarrationSound::getInstance()->getNarrationTime(filePath);
}

void CJMultimedia::playNarrationWithDelay(CCNode* sender, std::string fileName, float delay)
{
    if (delay != 0) {
        
        sender->runAction(CCSequence::create(CCDelayTime::create(delay),
                                             playNarrationWithDelayCallfuncND(sender, fileName),
                                             NULL));
    }
    else{
        playNarration(fileName);
    }
}

CCActionInstant* CJMultimedia::playNarrationWithDelayCallfuncND(CCNode* sender, std::string fileName )
{
    CCActionInstant* soundCallfunc;
    soundCallfunc = CCCallFuncND::create(sender, callfuncND_selector(CJMultimedia::_playNarrationWithDelayCallfunc), new CCString(fileName));
    return soundCallfunc;
}


void CJMultimedia::_playNarrationWithDelayCallfunc(CCNode* sender, void* filePath)
{
    CCString *fileName = (CCString *)filePath;
    playNarration(fileName->getCString());
    fileName->release();
}
    


void CJMultimedia::playAllNarration()
{
    CJNarrationSound::getInstance()->playAllNarration(false);
}

void CJMultimedia::playAllNarration(bool bLoop)
{
    CJNarrationSound::getInstance()->playAllNarration(bLoop);
}

void CJMultimedia::pauseAllNarration()
{
    CJNarrationSound::getInstance()->pauseAllNarration();
}

void CJMultimedia::resumeAllNarration()
{
    CJNarrationSound::getInstance()->resumeAllNarration();
}

void CJMultimedia::stopAllNarration()
{
    CJNarrationSound::getInstance()->stopAllNarration();
}

void CJMultimedia::removeAllNarration()
{
    CJNarrationSound::getInstance()->removeAllNarration();
}

bool CJMultimedia::isNarrationPlaying()
{
    return CJNarrationSound::getInstance()->isNarrationPlaying();
}

float CJMultimedia::getNarrationMainVolume()
{
    return CJNarrationSound::getInstance()->getNarrationMainVolume();
}

void CJMultimedia::setNarrationMainVolume(const float volume)
{
    CJNarrationSound::getInstance()->setNarrationMainVolume(volume);
}

void CJMultimedia::unloadAllNarration()
{
    CJNarrationSound::getInstance()->unloadAllNarration();
}


void CJMultimedia::pauseToPlayingNarration()
{
    CJNarrationSound::getInstance()->pauseToPlayingNarration();
}

void CJMultimedia::resumePausedNarration()
{
    CJNarrationSound::getInstance()->resumePausedNarration();    
}


#pragma mark - Video Multimedia
#pragma mark - Control Video 
void CJMultimedia::playVideo(std::string fileName, bool isControllerVisible)
{
    CJVideoInterface::getInstance()->playVideo(fileName, isControllerVisible);
}

void CJMultimedia::pauseVideo()
{
    CJVideoInterface::getInstance()->pauseVideo();
}

void CJMultimedia::resumeVideo()
{
    CJVideoInterface::getInstance()->resumeVideo();
}

void CJMultimedia::stopVideo()
{
    CJVideoInterface::getInstance()->stopVideo();
}

void CJMultimedia::addButtonVideo(std::string btnPath, float x, float y, int tag)
{
    CJVideoInterface::getInstance()->addVideoBtn(btnPath,
                                                 x,
                                                 y,
                                                 tag);
}

void CJMultimedia::playFrameVideo(std::string frameImgPath, std::string contentPath, int x, int y, int width, int height)
{
    CJVideoInterface::getInstance()->playFrameVideo(frameImgPath,
                                                    contentPath,
                                                    x,
                                                    y,
                                                    width,
                                                    height);
}

void CJMultimedia::removeFrameVideo()
{
    CJVideoInterface::getInstance()->removeFrameVideo();
}

#pragma mark - Camera Multimedia
#pragma mark - Control Camera

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void CJMultimedia::setGallerySession()
{
    CJCameraInterface::getInstance()->setGallerySession();
}

bool CJMultimedia::getGallerySession()
{
    return CJCameraInterface::getInstance()->getGallerySession();
}

void CJMultimedia::saveToPhotoLibraryWithFileName(std::string strFileName)
{
    CJCameraInterface::getInstance()->saveToPhotoLibraryWithFileName(strFileName);
}
#endif

void CJMultimedia::showCameraPreview(std::string frameImgPath, int direction, int x, int y, int width, int height)
{
    CJCameraInterface::getInstance()->showCameraPreview(frameImgPath,
                                                        direction,
                                                        x,
                                                        y,
                                                        width,
                                                        height);
}

void CJMultimedia::takePicture()
{
    CJCameraInterface::getInstance()->takePicture();
}

void CJMultimedia::startVideoRecording(std::string contentPath)
{
    //Temp File Name
    //Get filename through LMS function of CJUtil class
    CJCameraInterface::getInstance()->startRecording(contentPath);
}

void CJMultimedia::stopVideoRecording()
{
    CJCameraInterface::getInstance()->stopRecording();
}

void CJMultimedia::removeCameraView()
{
    CJCameraInterface::getInstance()->removeCameraView();
}

bool CJMultimedia::isShowCameraPreivew()
{
    return CJCameraInterface::getInstance()->isShowCameraPreview();
}

void CJMultimedia::moveToCameraView(int x, int y)
{
    CJCameraInterface::getInstance()->moveToCameraView(x, y);
}

#pragma mark - Voice Recording Multimedia
#pragma mark - Control Voice Recording

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void CJMultimedia::setRecSession()
{
    CJVoiceRecorderInterface::getInstance()->setRecSession();
}

bool CJMultimedia::getRecSession()
{
    return CJVoiceRecorderInterface::getInstance()->getRecSession();
}
#endif

void CJMultimedia::startVoiceRecording(std::string filePath)
{
    CJVoiceRecorderInterface::getInstance()->recVoiceRecording(filePath);
}

void CJMultimedia::stopVoiceRecording()
{
    CJVoiceRecorderInterface::getInstance()->stopVoiceRecording();
}

void CJMultimedia::pauseVoiceRecording()
{
    CJVoiceRecorderInterface::getInstance()->pauseVoiceRecording();
}

void CJMultimedia::resumeVoiceRecording()
{
    CJVoiceRecorderInterface::getInstance()->resumeVoiceRecording();
}

void CJMultimedia::playRecordedVoice(std::string filePath)
{
    CJVoiceRecorderInterface::getInstance()->playRecordedVoice(filePath);
}

void CJMultimedia::stopRecordedVoice()
{
    CJVoiceRecorderInterface::getInstance()->stopRecordedVoice();
}

void CJMultimedia::pauseRecordedVoice()
{
    CJVoiceRecorderInterface::getInstance()->pauseRecordedVoice();
}

void CJMultimedia::resumeRecordedVoice()
{
    CJVoiceRecorderInterface::getInstance()->resumeRecordedVoice();
}


void CJMultimedia::showBrowser(std::string pszURL)
{
    CJUriConnection::getInstance()->showBrowser(pszURL);
}
 
