//
//  CJLMSExtensionJni.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 11. 8..
//
//

#include "CJSaveDataInterfaceJni.h"

#define  LOG_TAG    "libLMSExtension"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
//#define  CLASS_NAME "org/cocos2dx/lib/CJDirectory"
#define  CLASS_NAME "com/cjeducations/lib/CJPlatformDirectory"


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
 
    std::string getAssetImagePathJNI(const char* pName)
    {
        // std::string getStringForKeyJNI()
        JniMethodInfo methodInfo;
        std::string ret;
        
        if (!getStaticMethodInfo(methodInfo, "SaveAssetImageSave", "(Ljava/lang/String;)Ljava/lang/String;"))
        {
            ret = "error_userdefault";
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(pName);
        jstring str = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        
        if(str)
        {
        	const char* temp = (char*)methodInfo.env->GetStringUTFChars(str, NULL);
            ret = temp;
        	methodInfo.env->ReleaseStringUTFChars(str, temp);
        	methodInfo.env->DeleteLocalRef(str);
        } else {
            ret = "error_userdefault";
        }
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;

        
        
    }
    
    void createBaseDirJNI()
    {
        // void createBaseDir()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "createBaseDir", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    std::string getHiddenDirPathJNI()
    {
        // std::string getHiddenDirPath()
        JniMethodInfo methodInfo;
        std::string ret;
        
        if (!getStaticMethodInfo(methodInfo, "getHiddenDirPath", "()Ljava/lang/String;"))
        {
            ret = "error_data";
        }
        
        jstring str = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        
        if(str)
        {
        	const char* temp = (char*)methodInfo.env->GetStringUTFChars(str, NULL);
            ret = temp;
        	methodInfo.env->ReleaseStringUTFChars(str, temp);
        	methodInfo.env->DeleteLocalRef(str);
        } else {
            ret = "error_data";
        }
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    std::string getResourceDirPathJNI(const char *szProjectIdenty)
    {
        // std::string getResourceDirPath()
        JniMethodInfo methodInfo;
        std::string ret;
        
        if (!getStaticMethodInfo(methodInfo, "getResourceDirPath", "(Ljava/lang/String;)Ljava/lang/String;"))
        {
            ret = "error_data";
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(szProjectIdenty);
        jstring str = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        
        if(str)
        {
        	const char* temp = (char*)methodInfo.env->GetStringUTFChars(str, NULL);
            ret = temp;
        	methodInfo.env->ReleaseStringUTFChars(str, temp);
        	methodInfo.env->DeleteLocalRef(str);
        } else {
            ret = "error_data";
        }
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
}
