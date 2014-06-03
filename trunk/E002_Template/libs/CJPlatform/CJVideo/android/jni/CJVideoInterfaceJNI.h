
#ifndef __CJNarrationVideoJni__
#define __CJNarrationVideoJni__

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

 
extern "C"
{
    extern void playVideoJNI(const char* path, bool isControllerVisible);
    extern void stopVideoJNI();
    extern void pauseVideoJNI();
    extern void resumeVideoJNI();
    extern void addButtonJNI(const char* filePath, float x, float y, int tag);
    extern void playFrameVideoJNI(const char* frameImgPath, const char* contentPath, int x, int y, int width, int height);
    extern void removeFrameVideoJNI();
}

#endif
