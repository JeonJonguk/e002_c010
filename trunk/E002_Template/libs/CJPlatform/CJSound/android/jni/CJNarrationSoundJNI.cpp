

#include "CJNarrationSoundJNI.h"

#define  LOG_TAG    "libNarrationSound"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  CLASS_NAME "com/cjeducations/lib/CJPlatformHelper"



typedef struct JniMethodInfo_
{
    JNIEnv *    env;
    jclass      classID;
    jmethodID   methodID;
} JniMethodInfo;

extern "C"
{
    // get env and cache it
    static JNIEnv* getJNIEnv(void)
    {
        
        JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
        if (NULL == jvm) {
            LOGD("Failed to get JNIEnv. JniHelper::getJavaVM() is NULL");
            return NULL;
        }
        
        JNIEnv *env = NULL;
        // get jni environment
        jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
        
        switch (ret) {
            case JNI_OK :
                // Success!
                return env;
                
            case JNI_EDETACHED :
                // Thread not attached
                
                // TODO : If calling AttachCurrentThread() on a native thread
                // must call DetachCurrentThread() in future.
                // see: http://developer.android.com/guide/practices/design/jni.html
                
                if (jvm->AttachCurrentThread(&env, NULL) < 0)
                {
                    LOGD("Failed to get the environment using AttachCurrentThread()");
                    return NULL;
                } else {
                    // Success : Attached and obtained JNIEnv!
                    return env;
                }
                
            case JNI_EVERSION :
                // Cannot recover from this error
                LOGD("JNI interface version 1.4 not supported");
                break;
            default :
                LOGD("Failed to get the environment using GetEnv()");
                return NULL;
        }
    }
    
    // get class and make it a global reference, release it at endJni().
    static jclass getClassID(JNIEnv *pEnv)
    {
        jclass ret = pEnv->FindClass(CLASS_NAME);
        if (! ret)
        {
            LOGD("Failed to find class of %s", CLASS_NAME);
        }
        
        return ret;
    }
    
    static bool getStaticMethodInfo(JniMethodInfo &methodinfo, const char *methodName, const char *paramCode)
    {
        jmethodID methodID = 0;
        JNIEnv *pEnv = 0;
        bool bRet = false;
        
        do
        {
            pEnv = getJNIEnv();
            if (! pEnv)
            {
                break;
            }
            
            jclass classID = getClassID(pEnv);
            
            methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
            if (! methodID)
            {
                LOGD("Failed to find static method id of %s", methodName);
                break;
            }
            
            methodinfo.classID = classID;
            methodinfo.env = pEnv;
            methodinfo.methodID = methodID;
            
            bRet = true;
        } while (0);
        
        return bRet;
    }
    
#pragma mark - dir func
 
    void preloadNarrationJNI(const char* path)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "preloadNarration", "(Ljava/lang/String;)V"))
        {
            return ;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void playNarrationJNI(const char* path, const bool isLoop)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "playNarration", "(Ljava/lang/String;Z)V"))
        {
            return ;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg, isLoop);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void stopNarrationJNI(const char* path)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "stopNarration", "(Ljava/lang/String;)V"))
        {
            return ;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
    }
    
    void pauseNarrationJNI(const char* path)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "pauseNarration", "(Ljava/lang/String;)V"))
        {
            return ;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void resumeNarrationJNI(const char* path)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "resumeNarration", "(Ljava/lang/String;)V"))
        {
            return ;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    bool isNarrationPlayingJNI()
    {
        JniMethodInfo methodInfo;
        jboolean ret = false;
        
        if (! getStaticMethodInfo(methodInfo, "isNarrationPlaying", "()Z"))
        {
            return ret;
        }
         
        ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    void playAllNarrationJNI(const bool isLoop)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "playAllNarration", "(Z)V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, isLoop);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void stopAllNarrationJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "stopAllNarration", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    void removeAllNarrationJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "removeAllNarration", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void pauseAllNarrationJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "pauseAllNarration", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void resumeAllNarrationJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "resumeAllNarration", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    float getNarrationMainVolumeJNI()
    {
        JniMethodInfo methodInfo;
        jfloat ret = 0.5;
        
        if (! getStaticMethodInfo(methodInfo, "getNarrationMainVolume", "()F"))
        {
            return ret;
        }
        
        ret = methodInfo.env->CallStaticFloatMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    void setNarrationMainVolumeJNI(const float volume)
    {
        JniMethodInfo methodInfo; 
        
        if (! getStaticMethodInfo(methodInfo, "setNarrationMainVolume", "(F)V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (float)volume);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
        
    void endNarrationJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "end", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    float getCurrentPositionJNI(const char* path)
    {
        JniMethodInfo methodInfo;
        jint ret = 0;
        
        if (! getStaticMethodInfo(methodInfo, "getCurrentPosition", "(Ljava/lang/String;)I"))
        {
            float temp = ret / 1000.0;
            return temp;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path); 
        ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID, stringArg);

        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        float temp = ret / 1000.0;
        return temp;
    }
    
    float getNarrationTimeJNI(const char* path)
    {
        JniMethodInfo methodInfo;
        jint ret = 0;
        
        if (! getStaticMethodInfo(methodInfo, "getNarrationTime", "(Ljava/lang/String;)I"))
        {
            float temp = ret / 1000.0;
            return temp;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        float temp = ret / 1000.0;
        return temp;
    }
    
    float getDeviceVolumeJNI()
    {
        JniMethodInfo methodInfo;
        jint ret = 0;
        
        if (! getStaticMethodInfo(methodInfo, "getDeviceVolume", "()I"))
        {
            return (float)ret;
        }
         
        ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID);
        
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return (float)ret;
    }
    
    
    void pauseToPlayingNarrationJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "pauseToPlayingNarration", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);

    }
    
    void resumePausedNarrationJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "resumePausedNarration", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);

    }
}
