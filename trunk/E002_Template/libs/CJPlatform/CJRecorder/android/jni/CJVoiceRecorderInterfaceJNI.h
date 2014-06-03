
#ifndef __CJVoiceRecorderJni__
#define __CJVoiceRecorderJni__

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

 
extern "C"
{
    extern void recVoiceRecordingJNI(const char* filePath);
    extern void stopVoiceRecordingJNI();
    extern void pauseVoiceRecordingJNI();
    extern void resumeVoiceRecordingJNI();
    
    extern void playRecordedVoiceJNI(const char* filePath);
    extern void stopRecordedVoiceJNI();
    extern void pauseRecordedVoiceJNI();
    extern void resumeRecordedVoiceJNI();
}

#endif
