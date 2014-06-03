 

#include "../include/CJCameraInterface.h"
#include "jni/CJCameraInterfaceJni.h"
#include "CJUtils.h"
#include "CJDefines.h"

static CJCameraInterface * s_pInstance = 0;

CJCameraInterface::CJCameraInterface()
{
    isShowPreview = false;
}

CJCameraInterface::~CJCameraInterface()
{

}

CJCameraInterface* CJCameraInterface::getInstance()
{
    if (! s_pInstance)
    {
        s_pInstance = new CJCameraInterface();
    }
    
    return s_pInstance;
}

void  CJCameraInterface::showCameraPreview(std::string frameImgPath, int direction, int x, int y, int width, int height)
{
    isShowPreview = true;
    showCameraPreviewJNI(frameImgPath.c_str(), direction, x, y, width, height);
}

void  CJCameraInterface::takePicture()
{
    if(isShowPreview)
        takePictureJNI();
}

void CJCameraInterface::startRecording(std::string contentPath)
{
    isShowPreview = true;
    startRecordingJNI(contentPath.c_str());
}

void CJCameraInterface::stopRecording()
{
    if(isShowPreview)
        stopCameraRecordingJNI();
}

void CJCameraInterface::removeCameraView()
{
    isShowPreview = false;
    removeCameraViewJNI();
}

bool CJCameraInterface::isShowCameraPreview()
{
    return isShowPreview;
}

void CJCameraInterface::moveToCameraView(int x, int y)
{
   moveToCameraViewJNI(x, y);
}

extern "C"
{
    void Java_com_cjeducations_lib_CJPlatformCameraView_pictureFinishCall(JNIEnv *env, jobject thisobj, jstring path)
    {
        CCString *filePath = new CCString(env->GetStringUTFChars(path, false));
        
        std::string fullPath = filePath->getCString();
        std::string fileName =  CJUtils::getInstance()->stringTokenizer(fullPath, "/", false);
        CCString *onlyFileName = new CCString(fileName.c_str());
        delete filePath;
        env->ReleaseStringUTFChars(path, env->GetStringUTFChars(path, false));
        env->DeleteLocalRef(path);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_PICTURE_FINISHCALL, onlyFileName);
    }
    
    void Java_com_cjeducations_lib_CJPlatformCameraView_videoRecordingFinishCall(JNIEnv *env, jobject thisobj, jstring path)
    { 
        CCString *filePath = new CCString(env->GetStringUTFChars(path, false));
        
        std::string fullPath = filePath->getCString();
        std::string fileName =  CJUtils::getInstance()->stringTokenizer(fullPath, "/", false);
        CCString *onlyFileName = new CCString(fileName.c_str());
        delete filePath;
        env->ReleaseStringUTFChars(path, env->GetStringUTFChars(path, false));
        env->DeleteLocalRef(path);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_VIDEO_RECORDING_FINISHCALL, onlyFileName);
    }
    
    void Java_com_cjeducations_ithink_e002_E002Template_OnPauseVideoRecording(JNIEnv *env, jobject thisobj)
    {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_CAMERA_ONPAUSE_RECORDING_CALL);
    }
}
