//
//  CJLMSExtensionJni.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 11. 8..
//
//

#include "CJLMSExtensionJni.h"

#define  LOG_TAG    "libLMSExtension"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  CLASS_NAME "com/cjeducations/activity/CJPackageActivity"

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
    
    static bool getStaticMethodInfoForRecovery(JniMethodInfo &methodinfo, const char *methodName, const char *paramCode)
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

    		jclass classID = pEnv->FindClass("com/cjeducations/ithink/e002/RecoveryReceiver");

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

    void endCJJNI()
    {
        // void end()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "end", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void finishRecoveryJNI()
    {
        // void finishRecovery()
        
        JniMethodInfo methodInfo;
        
        if (!getStaticMethodInfoForRecovery(methodInfo, "finishRecovery", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void callCertificationJNI()
    {
        // void callCertification()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "callCertification", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void callYoutubeJNI(const char* youtubeId)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "callYoutube", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(youtubeId);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    long compareDateJNI(const char* startDate)
    {
        JniMethodInfo methodInfo;
        jlong ret = 0;
        
        if (! getStaticMethodInfo(methodInfo, "compareDate", "(Ljava/lang/String;)J"))
        {
            return ret;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(startDate);
        ret = methodInfo.env->CallStaticLongMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    bool getNetworkStateJNI()
    {
        // boolean getNetworkState()
        
        JniMethodInfo methodInfo;
        jboolean ret = false;
        
        if (! getStaticMethodInfo(methodInfo, "getNetworkState", "()Z"))
        {
            return ret;
        }
        
        ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
  
    int getWifiStrengthJNI()
    {
        JniMethodInfo methodInfo;
        int ret = 0;
        
        if (! getStaticMethodInfo(methodInfo, "getWifiStrength", "()I"))
        {
            return ret;
        }
        
        ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    
#pragma mark - download data param

    std::string getAuthKeyJNI()
    {
    	// std::string getAuthKey()
        JniMethodInfo methodInfo;
        std::string ret;
        

        if (!getStaticMethodInfo(methodInfo, "getAuthKey", "()Ljava/lang/String;"))
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

    std::string getURLJNI()
    {

    	// std::string getURL()
        JniMethodInfo methodInfo;
        std::string ret;

        if (!getStaticMethodInfo(methodInfo, "getURL", "()Ljava/lang/String;"))
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

    std::string getUserAgentJNI()
    {
    	// std::string getUserAgent()
        JniMethodInfo methodInfo;
        std::string ret;

        if (!getStaticMethodInfo(methodInfo, "getUserAgent", "()Ljava/lang/String;"))
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

    std::string getTransactionIdJNI()
    {
    	// std::string getTransactionId()
        JniMethodInfo methodInfo;
        std::string ret;

        if (!getStaticMethodInfo(methodInfo, "getTransactionId", "()Ljava/lang/String;"))
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

    std::string getInterfaceIdJNI()
    {
    	// std::string getInterfaceId()
        JniMethodInfo methodInfo;
        std::string ret;

        if (!getStaticMethodInfo(methodInfo, "getInterfaceId", "()Ljava/lang/String;"))
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

    std::string getInterfaceVerJNI()
    {
    	// std::string getInterfaceVer()
        JniMethodInfo methodInfo;
        std::string ret;

        if (!getStaticMethodInfo(methodInfo, "getInterfaceVer", "()Ljava/lang/String;"))
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

    std::string getRequestTimeJNI()
    {
    	// std::string getRequestTime()
        JniMethodInfo methodInfo;
        std::string ret;

        if (!getStaticMethodInfo(methodInfo, "getRequestTime", "()Ljava/lang/String;"))
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

#pragma mark - file system
    
    long long getFileSizeJNI(const char* path)
    {
        // int getFileSize()
        
        JniMethodInfo methodInfo;
        jlong ret = 0;
        
        if (! getStaticMethodInfo(methodInfo, "getFileSize", "(Ljava/lang/String;)J"))
        {
            return ret;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        ret = methodInfo.env->CallStaticLongMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    bool checkSDCardAvailableJNI()
    {
        // boolean removeSaveFile()
        
        JniMethodInfo methodInfo;
        jboolean ret = false;
        
        if (! getStaticMethodInfo(methodInfo, "checkSDCardAvailable", "()Z"))
        {
            return ret;
        }
        
        ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    long long getFreeSpaceJNI()
    {
        // int getFreeSpace()
        
        JniMethodInfo methodInfo;
        jlong ret = 0;
        
        if (! getStaticMethodInfo(methodInfo, "getFreeSpace", "()J"))
        {
            return ret;
        }
        
        ret = methodInfo.env->CallStaticLongMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    void checkStorageSizeJNI()
    {
        // void checkSDCard()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "checkStorageSize", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    bool removeSaveFileJNI(const char* path)
    {
        // boolean removeSaveFile()
        
        JniMethodInfo methodInfo;
        jboolean ret = false;
        
        if (! getStaticMethodInfo(methodInfo, "removeSaveFile", "(Ljava/lang/String;)Z"))
        {
            return ret;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
#pragma mark - get account info
    
    std::string getChildIdJNI()
    {
        // std::string getChildId()
        JniMethodInfo methodInfo;
        std::string ret;
        
        if (!getStaticMethodInfo(methodInfo, "getChildId", "()Ljava/lang/String;"))
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
    
    std::string getChildNameJNI()
    {
        // std::string getChildName()
        JniMethodInfo methodInfo;
        std::string ret;
        
        if (!getStaticMethodInfo(methodInfo, "getChildName", "()Ljava/lang/String;"))
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
    
    std::string getChildBirthJNI()
    {
        // std::string getChildBirth()
        JniMethodInfo methodInfo;
        std::string ret;
        
        if (!getStaticMethodInfo(methodInfo, "getChildBirth", "()Ljava/lang/String;"))
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
    
    std::string getChildImageJNI()
    {
        // std::string getChildImage()
        JniMethodInfo methodInfo;
        std::string ret;
        
        if (!getStaticMethodInfo(methodInfo, "getChildImage", "()Ljava/lang/String;"))
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
        
        return ret;
    }
    
#pragma mark - set mail
    
    void setMailFileJNI(const char* path)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setMailFile", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(path);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void setMailTitleJNI(const char* title)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setMailTitle", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(title);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
#pragma mark - init list
    
    void initStepListJNI()
    {
        // void initStepList()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "initStepList", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void initContentListJNI()
    {
        // void initContentList()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "initContentList", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void initLearnListJNI()
    {
        // void initLearnList()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "initLearnList", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void initGradeListJNI()
    {
        // void initGradeList()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "initGradeList", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
#pragma mark - init struct
    
    void initStepJNI()
    {
        // void initStep()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "initStep", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void initContentJNI()
    {
        // void initContent()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "initContent", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void initLearnJNI()
    {
        // void initLearn()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "initLearn", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void initGradeJNI()
    {
        // void initGrade()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "initGrade", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
#pragma mark - add struct to list
    
    void addStepJNI()
    {
        // void addStep()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "addStep", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void addContentJNI()
    {
        // void addContent()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "addContent", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void addLearnJNI(unsigned int childID)
    {
    	// void addLearn()

    	JniMethodInfo methodInfo;

    	if (! getStaticMethodInfo(methodInfo, "addLearn", "(I)V"))
    	{
    		return;
    	}

    	methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)childID);
    	methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void addGradeJNI()
    {
        // void addGrade()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "addGrade", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
#pragma mark - set Step struct
    
    void setStepCountJNI(unsigned int nCount)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setStepCount", "(I)V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)nCount);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void setStepKeyJNI(const char* szKey)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setStepKey", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(szKey);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void setStepStartDateJNI(const char* szStartDate)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setStepStartDate", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(szStartDate);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void setStepEndDateJNI(const char* szEndDate)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setStepEndDate", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(szEndDate);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void setStepExtraJNI(const char* szExtra)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setStepExtra", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(szExtra);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
#pragma mark - set Content struct
    
    void setContentCodeJNI(const char* szContentCode)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setContentCode", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(szContentCode);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void setContentGradeJNI()
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setContentGrade", "()V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void setContentExtraJNI(const char* szExtra)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setContentExtra", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(szExtra);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void setContentListJNI()
    {
        // void initStepList()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setContentList", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
#pragma mark - set Learn struct
    
    void setLearnPKGNameJNI(const char* szPKGName)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setLearnPKGName", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(szPKGName);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void setLearnCompleteDateJNI(const char* szCompleteDate)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setLearnCompleteDate", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(szCompleteDate);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void setLearnListJNI()
    {
        // void initStepList()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setLearnList", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
#pragma mark - set Grade struct
    
    void setGradeJNI(unsigned int iGrade)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setGrade", "(I)V"))
        {
            return ;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (int)iGrade);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void setGradeDateJNI(const char* szWriteDate)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setGradeDate", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(szWriteDate);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void setGradeExtraJNI(const char* szExtra)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "setGradeExtra", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(szExtra);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
#pragma mark - send to LMSCenter
    
    unsigned int sendLMSCenterJNI()
    {
        // int sendLMSCenter()
        
        JniMethodInfo methodInfo;
        int ret = 0;
        
        if (! getStaticMethodInfo(methodInfo, "sendLMSCenter", "()I"))
        {
            return ret;
        }
        
        ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return (unsigned int)ret;
    }
    
    unsigned int sendMailJNI(const char* text)
    {
        // int sendLMSCenter()
        
        JniMethodInfo methodInfo;
        int ret = 0;
        
        if (! getStaticMethodInfo(methodInfo, "sendMail", "(Ljava/lang/String;)I"))
        {
            return ret;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(text);
        ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return (unsigned int)ret;
    }
    
#pragma mark - get String
    
    std::string getDeviceDateTimeJNI()
    {
        // std::string getDeviceDateTime()
        JniMethodInfo methodInfo;
        std::string ret;

        if (!getStaticMethodInfoForRecovery(methodInfo, "getDeviceDateTime", "()Ljava/lang/String;"))
        {
            ret = "error_date_time";
        }

        jstring str = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);

        if(str)
        {
        	const char* temp = (char*)methodInfo.env->GetStringUTFChars(str, NULL);
            ret = temp;
        	methodInfo.env->ReleaseStringUTFChars(str, temp);
        	methodInfo.env->DeleteLocalRef(str);
        } else {
            ret = "error_date_time";
        }
        methodInfo.env->DeleteLocalRef(methodInfo.classID);

        return ret;
    }
    
    std::string getTargetDateTimeJNI(unsigned int packageIndex)
    {
        // std::string getDeviceDateTime()
        JniMethodInfo methodInfo;
        std::string ret;
        
        if (!getStaticMethodInfo(methodInfo, "getTargetDateTime", "(I)Ljava/lang/String;"))
        {
            ret = "error_date_time";
        }
        
        jstring str = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, (int)packageIndex);
         
        if(str)
        {
        	const char* temp = (char*)methodInfo.env->GetStringUTFChars(str, NULL);
            ret = temp;
        	methodInfo.env->ReleaseStringUTFChars(str, temp);
        	methodInfo.env->DeleteLocalRef(str);
        } else {
            ret = "error_date_time";
        }
        methodInfo.env->DeleteLocalRef(methodInfo.classID);

        return ret;
    }
    
    std::string getDiffDateJNI(const char* date, int days)
    {
        // std::string getDiffDate()
        JniMethodInfo methodInfo;
        std::string ret;
        
        if (!getStaticMethodInfoForRecovery(methodInfo, "getDiffDate", "(Ljava/lang/String;I)Ljava/lang/String;"))
        {
            ret = "error_date_time";
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(date);
        jstring str = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, stringArg, (int)days);
        
        if(str)
        {
        	const char* temp = (char*)methodInfo.env->GetStringUTFChars(str, NULL);
            ret = temp;
        	methodInfo.env->ReleaseStringUTFChars(str, temp);
        	methodInfo.env->DeleteLocalRef(str);
        } else {
            ret = "error_date_time";
        }
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return ret;
    }
    
    void showThinkleStoreJNI()
    {
        // void initGrade()
        
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "showThinkleStore", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
    void showBrowserJNI(const char *szUrl)
    {
        JniMethodInfo methodInfo;
        
        if (! getStaticMethodInfo(methodInfo, "showBrowser", "(Ljava/lang/String;)V"))
        {
            return;
        }
        
        jstring stringArg = methodInfo.env->NewStringUTF(szUrl);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}
