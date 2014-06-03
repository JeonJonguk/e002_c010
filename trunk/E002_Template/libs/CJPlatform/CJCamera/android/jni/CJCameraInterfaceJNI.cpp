

#include "CJCameraInterfaceJNI.h"

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
  
    void showCameraPreviewJNI(const char* frameImgPath, int direction, int x, int y, int width, int height)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "showCameraPreview", "(Ljava/lang/String;IIIII)V"))
        {
            return ;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(frameImgPath);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg, direction, x, y, width, height);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    void takePictureJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "takePicture", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void startRecordingJNI(const char* contentPath)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "startRecording", "(Ljava/lang/String;)V"))
        {
            return ;
        }
         
        jstring stringArg = methodInfo.env->NewStringUTF(contentPath);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void stopCameraRecordingJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "stopCameraRecording", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void removeCameraViewJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "removeCameraView", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void moveToCameraViewJNI(int x, int y)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "moveToCameraView", "(II)V"))
        {
            return ;
        }
         
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, x, y);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}
