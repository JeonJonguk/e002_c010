
#ifndef __CJCameraInterfaceJni__
#define __CJCameraInterfaceJni__

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

 
extern "C"
{
    extern void showCameraPreviewJNI(const char* frameImgPath, int direction, int x, int y, int width, int height);
    extern void takePictureJNI();
    extern void startRecordingJNI(const char* contentPath);
    extern void stopCameraRecordingJNI();
    extern void removeCameraViewJNI();
    extern void moveToCameraViewJNI(int x, int y);
}

#endif
