 

#ifndef __CJFlatform__CJVoiceRecorderInterface__
#define __CJFlatform__CJVoiceRecorderInterface__

#include <vector>
#include "cocos2d.h" 
#include "CJDefines.h"
 

USING_NS_CC;

class CJVoiceRecorderInterface
{
private: 
    
public:
     
    CJVoiceRecorderInterface();
    ~CJVoiceRecorderInterface();
  
    static CJVoiceRecorderInterface* getInstance();
    
    void   setRecSession();
    bool   getRecSession();
    void   recVoiceRecording(std::string filePath);
    void   stopVoiceRecording();
    void   pauseVoiceRecording();
    void   resumeVoiceRecording();
    
    void   playRecordedVoice(std::string filePath);
    void   stopRecordedVoice();
    void   pauseRecordedVoice();
    void   resumeRecordedVoice();
    void   stopRecordPlayCallBack();    
};

#endif  