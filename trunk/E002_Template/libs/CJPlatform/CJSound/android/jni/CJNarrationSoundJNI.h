
#ifndef __CJNarrationSoundJni__
#define __CJNarrationSoundJni__

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
 
 
extern "C"
{
    extern void preloadNarrationJNI(const char* path);
    extern void playNarrationJNI(const char* path, const bool isLoop);
    extern void stopNarrationJNI(const char* path);
    extern void pauseNarrationJNI(const char* path);
    extern void resumeNarrationJNI(const char* path);
    
    extern bool isNarrationPlayingJNI();
    
    extern void playAllNarrationJNI(const bool isLoop);
    extern void stopAllNarrationJNI();
    extern void pauseAllNarrationJNI();
    extern void resumeAllNarrationJNI();
    extern void removeAllNarrationJNI();
    
    extern float getNarrationMainVolumeJNI();
    extern void setNarrationMainVolumeJNI(const float volume); 
    extern void endNarrationJNI();
    
    extern float getCurrentPositionJNI(const char* path);
    extern float getNarrationTimeJNI(const char* path);
    
    extern float getDeviceVolumeJNI();
    
    extern void pauseToPlayingNarrationJNI();
    extern void resumePausedNarrationJNI();
    
}

#endif
