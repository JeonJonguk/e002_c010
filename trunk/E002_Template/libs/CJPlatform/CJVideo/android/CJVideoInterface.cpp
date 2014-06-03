 

#include "../include/CJVideoInterface.h"
#include "jni/CJVideoInterfaceJni.h"
 

static CJVideoInterface * s_pInstance = 0;

CJVideoInterface::CJVideoInterface()
{
    
}

CJVideoInterface::~CJVideoInterface()
{

}

CJVideoInterface* CJVideoInterface::getInstance()
{
    if (! s_pInstance)
    {
        s_pInstance = new CJVideoInterface();
    }
    
    return s_pInstance;
}

void CJVideoInterface::playVideo(std::string filePath, bool isControllerVisible)
{
    playVideoJNI(filePath.c_str(), isControllerVisible);
}

void CJVideoInterface::stopVideo()
{
    stopVideoJNI();
}

void CJVideoInterface::pauseVideo()
{
    pauseVideoJNI();
}

void CJVideoInterface::resumeVideo()
{
    resumeVideoJNI();
}

void  CJVideoInterface::addVideoBtn(std::string btnPath, float x, float y, int tag)
{
    addButtonJNI(btnPath.c_str(), x, y, tag);
}

void CJVideoInterface::playFrameVideo(std::string frameImgPath, std::string contentPath, int x,int y,int width,int height)
{
    playFrameVideoJNI(frameImgPath.c_str(), contentPath.c_str(), x, y, width, height);
}

void CJVideoInterface::removeFrameVideo()
{
    removeFrameVideoJNI();
}

extern "C"
{
    void Java_com_cjeducations_lib_CJPlatformVideo_videoFinished(JNIEnv *env, jobject thisobj)
    {
         CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_VIDEO_FINISHCALL);
    }
    
    void Java_com_cjeducations_lib_CJPlatformVideo_videoBtnCallBack(JNIEnv *env, jobject thisobj, int tag)
    { 
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_VIDEO_BUTTONCALL, (CCObject*)tag);
    }
    
    void Java_com_cjeducations_lib_CJPlatformVideo_videoIndexCallBack(JNIEnv *env, jobject thisobj)
    {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_VIDEO_INDEX_BUTTONCALL);
    }
    
    void Java_com_cjeducations_lib_CJPlatformFrameVideoView_frameVideoFinishCall(JNIEnv *env, jobject thisobj)
    { 
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_FRAME_VIDEOVIEW_FINISHCALL);
    }
}
