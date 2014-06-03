 

#include "../include/CJVoiceRecorderInterface.h"
#include "jni/CJVoiceRecorderInterfaceJNI.h"
#include "CJUtils.h"
#include "CJDefines.h"

static CJVoiceRecorderInterface * s_pInstance = 0;

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
    
    return s_pInstance;
}

void   CJVoiceRecorderInterface::recVoiceRecording(std::string filePath)
{
    recVoiceRecordingJNI(filePath.c_str());
}

void   CJVoiceRecorderInterface::stopVoiceRecording()
{
    stopVoiceRecordingJNI();
}

void   CJVoiceRecorderInterface::pauseVoiceRecording()
{
    pauseVoiceRecordingJNI();
}

void   CJVoiceRecorderInterface::resumeVoiceRecording()
{
    resumeVoiceRecordingJNI();
}

void   CJVoiceRecorderInterface::playRecordedVoice(std::string filePath)
{
    playRecordedVoiceJNI(filePath.c_str());
}

void   CJVoiceRecorderInterface::stopRecordedVoice()
{
    stopRecordedVoiceJNI();
}

void   CJVoiceRecorderInterface::pauseRecordedVoice()
{
    pauseRecordedVoiceJNI();
}

void   CJVoiceRecorderInterface::resumeRecordedVoice()
{
    resumeRecordedVoiceJNI();
}

extern "C"
{
    void Java_com_cjeducations_ithink_e002_E002Template_RecordedVoicePlayFinished(JNIEnv *env, jobject thisobj)
    {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_RECORDED_VOICE_FINISHCALL);
    }
}
