 

#include "../include/CJNarrationSound.h"
#include "jni/CJNarrationSoundJni.h"
#include "CJUtils.h"
#include "CJDefines.h"

static CJNarrationSound * s_pInstance = 0;

CJNarrationSound::CJNarrationSound()
{
    
}

CJNarrationSound::~CJNarrationSound()
{

}

CJNarrationSound* CJNarrationSound::getInstance()
{
    if (! s_pInstance)
    {
        s_pInstance = new CJNarrationSound();
    }
    
    return s_pInstance;
}

void CJNarrationSound::preloadNarration(std::string filePath)
{
    preloadNarrationJNI(filePath.c_str());
}

//void CJNarrationSound::playNarration(std::string filePath)
//{
//    playNarrationJNI(filePath.c_str(), false);
//}

void CJNarrationSound::playNarration(std::string filePath, bool bLoop)
{
    playNarrationJNI(filePath.c_str(), bLoop);
}

void CJNarrationSound::playAllNarration(bool bLoop)
{
    playAllNarrationJNI(bLoop);
}

void CJNarrationSound::stopNarration(std::string filePath)
{
    stopNarrationJNI(filePath.c_str());
}

void CJNarrationSound::stopAllNarration()
{
    stopAllNarrationJNI();
}

void CJNarrationSound::removeAllNarration()
{
    removeAllNarrationJNI();
}

void CJNarrationSound::pauseNarration(std::string filePath)
{
    pauseNarrationJNI(filePath.c_str());
}

void CJNarrationSound::pauseAllNarration()
{
    pauseAllNarrationJNI();
}

void CJNarrationSound::resumeNarration(std::string filePath)
{
    resumeNarrationJNI(filePath.c_str());
}

void CJNarrationSound::resumeAllNarration()
{
    resumeAllNarrationJNI();
}

bool CJNarrationSound::isNarrationPlaying()
{
    return isNarrationPlayingJNI();
}

float CJNarrationSound::getNarrationMainVolume()
{
    float ret = 0;
    
    ret = getNarrationMainVolumeJNI();
    
    return ret;
}

void CJNarrationSound::setNarrationMainVolume(const float volume)
{
    setNarrationMainVolumeJNI(volume);
}

float CJNarrationSound::getCurrentPosition(std::string filePath)
{
    return getCurrentPositionJNI(filePath.c_str());
}

float CJNarrationSound::getNarrationTime(std::string filePath)
{
    return getNarrationTimeJNI(filePath.c_str());
}

float CJNarrationSound::getDeviceVolume()
{
    return getDeviceVolumeJNI();
}

void CJNarrationSound::unloadAllNarration()
{
    endNarrationJNI();
}

void CJNarrationSound::pauseToPlayingNarration()
{
    pauseToPlayingNarrationJNI();
}

void CJNarrationSound::resumePausedNarration()
{
    resumePausedNarrationJNI();
}


extern "C"
{
    void Java_com_cjeducations_ithink_e002_E002Template_NarrationFinished(JNIEnv *env, jobject thisobj, jstring path)
    {
        
        CCString *filePath = new CCString(env->GetStringUTFChars(path, false));

        std::string fullPath = filePath->getCString();
        std::string fileName =  CJUtils::getInstance()->stringTokenizer(fullPath, "/", false);
        CCString *onlyFileName = new CCString(fileName.c_str());
        delete filePath;
        env->ReleaseStringUTFChars(path, env->GetStringUTFChars(path, false));
        env->DeleteLocalRef(path);
 
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_VOICE_FINISHCALL, onlyFileName);
    }
}
