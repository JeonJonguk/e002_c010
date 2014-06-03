
#ifndef __CJUriConnectionJni__
#define __CJUriConnectionJni__

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
 
 
extern "C"
{
    extern void showBrowserConnectionJNI(const char* path);
}

#endif
