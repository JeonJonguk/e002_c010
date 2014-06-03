

#include "CJVideoInterfaceJNI.h"

#define  LOG_TAG    "libVideoInterface"
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
 
    void playVideoJNI(const char* path, bool isControllerVisible)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "playVideo", "(Ljava/lang/String;Z)V"))
        {
            return ;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg, isControllerVisible);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    void stopVideoJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "stopVideo", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void pauseVideoJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "pauseVideo", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void resumeVideoJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "resumeVideo", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void addButtonJNI(const char* filePath, float x, float y, int tag)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "addVideoBtn", "(Ljava/lang/String;FFI)V"))
        {
            return ;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(filePath);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg, x, y, tag);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void playFrameVideoJNI(const char* frameImgPath, const char* contentPath, int x, int y, int width, int height)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "playFrameVideo", "(Ljava/lang/String;Ljava/lang/String;IIII)V"))
        {
            return ;
        }
        
        jstring stringArg1 = methodInfo.env->NewStringUTF(frameImgPath);
        jstring stringArg2 = methodInfo.env->NewStringUTF(contentPath);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg1, stringArg2, x, y, width, height);
        methodInfo.env->DeleteLocalRef(stringArg1);
        methodInfo.env->DeleteLocalRef(stringArg2);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void removeFrameVideoJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "removeFrameVideoView", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}
