 

#include "../include/CJVoiceRecorderInterface.h" 
#include "CJUtils.h"
#include "CJDefines.h"
#include "CJ_RecorderIos.h"
static CJVoiceRecorderInterface * s_pInstance = 0;
static CJ_RecorderIos *rec_Instance  = NULL;
CJVoiceRecorderInterface::CJVoiceRecorderInterface()
{
    
}

CJVoiceRecorderInterface::~CJVoiceRecorderInterface()
{

}

CJVoiceRecorderInterface* CJVoiceRecorderInterface::getInstance()
{
    if (! s_pInstance)
    {
        s_pInstance = new CJVoiceRecorderInterface();
    }
    if(rec_Instance==NULL)
    {
        rec_Instance  = [[CJ_RecorderIos alloc]init];
    }
    return s_pInstance;
}

void   CJVoiceRecorderInterface::setRecSession()
{
    [rec_Instance setRecSession];
}

bool   CJVoiceRecorderInterface::getRecSession()
{
    return [rec_Instance getRecSession];
}

void   CJVoiceRecorderInterface::recVoiceRecording(std::string filePath)
{
    if (filePath == "")
        filePath = "tempRec";
    
    [rec_Instance readyRec:filePath.c_str()];
    [rec_Instance startRec];
}

void   CJVoiceRecorderInterface::stopVoiceRecording()
{
    [rec_Instance stopRec];
}

void   CJVoiceRecorderInterface::playRecordedVoice(std::string filePath)
{
    if (filePath == "")
        filePath = "tempRec";
    [rec_Instance playRecordFile:filePath.c_str()];
}

void   CJVoiceRecorderInterface::stopRecordedVoice()
{
    [rec_Instance stopRecordFile];
}
void   CJVoiceRecorderInterface::stopRecordPlayCallBack()
{
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_RECORDED_VOICE_FINISHCALL);
}
// CJNOTIFICATION_RECORDED_VOICE_FINISHCALL

void   CJVoiceRecorderInterface::pauseVoiceRecording()
{
    CJLog("pauseVoiceRecording");
}

void   CJVoiceRecorderInterface::resumeVoiceRecording()
{
    CJLog("resumeVoiceRecording");
}

void   CJVoiceRecorderInterface::pauseRecordedVoice()
{

}

void   CJVoiceRecorderInterface::resumeRecordedVoice()
{

}

extern "C"
{
    
//    void Java_com_cjeducations_lib_CJPlatformVoiceRecorder_voicePlayingFinishCall(JNIEnv *env, jobject thisobj)
//    {         
//        CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_RECORDED_VOICE_FINISHCALL);
//    }
}
