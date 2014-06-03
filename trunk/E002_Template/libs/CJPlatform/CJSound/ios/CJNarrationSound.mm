

#include "../include/CJNarrationSound.h"
#include "CJUtils.h"
#include "CJNarrationIos.h"
#include "CJDefines.h"
#include "MediaPlayer/MediaPlayer.h"

static CJNarrationSound * s_NarrationInstance = 0;
static std::vector<CJNarrationIos*> mArrIosBridge;
//static std::vector<CJNarrationIos*> vecBeRemoveNarration;

std::vector<CJNarrationIos*> m_arrPausedNarrations;

CJNarrationSound::CJNarrationSound()
{

}

CJNarrationSound::~CJNarrationSound()
{
    NSLog(@"CJNarrationSound::~CJNarrationSound");
}


CJNarrationSound* CJNarrationSound::getInstance()
{
    if (! s_NarrationInstance)
    {
        s_NarrationInstance = new CJNarrationSound();
    }
    
    return s_NarrationInstance;
}

void CJNarrationSound::preloadNarration(std::string filePath)
{
    
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        if([mArrIosBridge.at(i) getFileName] == filePath)
        {
            [((CJNarrationIos*)mArrIosBridge.at(i)) preloadNarration:filePath.c_str()];
            
            return;
        }
    }
    CJNarrationIos *tempIos = [[CJNarrationIos alloc]init];
    [tempIos preloadNarration:filePath.c_str()];
    mArrIosBridge.push_back(tempIos);
    
    
}

//void CJNarrationSound::playNarration(std::string filePath)
//{
////    for (int i = 0; i < mArrIosBridge.size(); i++)
////    {
////        if(strcmp([mArrIosBridge.at(i) getFileName], filePath.c_str()) == 0)
////        {
////            CJNarrationSound::getInstance()->stopNarration(filePath);
////            s_NarrationInstance->playNarration(filePath, false);
////        }
////    }
//    playNarration(filePath, false);
//}

float CJNarrationSound::getCurrentPosition(std::string filePath)
{
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        if([mArrIosBridge.at(i) getFileName] == filePath)
        {
            CJNarrationIos* ios = mArrIosBridge.at(i);
            return [ios getNarrationCurrentPosition:filePath.c_str()];

        }
    }
    return 0.f;
}

float CJNarrationSound::getNarrationTime(std::string filePath)
{
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        if([mArrIosBridge.at(i) getFileName] == filePath)
        {
            CJNarrationIos* ios = mArrIosBridge.at(i);
            return [ios getNarrationTime:filePath.c_str()];
            
        }
    }
    
    if(CCFileUtils::sharedFileUtils()->isFileExist(filePath))
    {
        CJNarrationIos *tempIos = [[CJNarrationIos alloc]init];
        [tempIos preloadNarration:filePath.c_str()];
        float time = [tempIos getNarrationTime:filePath.c_str()];
        [tempIos unloadPlayer];
        [tempIos release];
        
        return time;
    }
    
    return 0.f;
}

float CJNarrationSound::getDeviceVolume()
{
    float volume;
    
    MPMusicPlayerController *iPad = [MPMusicPlayerController iPodMusicPlayer];
    
    volume = [iPad volume];
    
    return volume;
}

void CJNarrationSound::playNarration(std::string filePath, bool bLoop)
{
    
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        if([mArrIosBridge.at(i) getFileName] == filePath)
        {
            CJNarrationSound::getInstance()->stopNarration(filePath);
        }
    }
    CJNarrationIos *tempIos = [[CJNarrationIos alloc] init];
    mArrIosBridge.push_back(tempIos);
    [tempIos playNarration:filePath.c_str() isLooping:bLoop];
    
}

void CJNarrationSound::playAllNarration(bool bLoop)
{
    for (int i = 0; i<mArrIosBridge.size(); i++)
    {
        std::string strfilePath = [mArrIosBridge.at(i) getFileName];
        [((CJNarrationIos*)mArrIosBridge.at(i)) playNarration:strfilePath.c_str() isLooping:bLoop];
    }
}

void CJNarrationSound::stopNarration(std::string filePath)
{
    NSLog(@"stopNarration");
    std::vector<CJNarrationIos*>::iterator it = mArrIosBridge.begin();
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        if([mArrIosBridge.at(i) getFileName] == filePath)
        {
            std::string strfilePath = [mArrIosBridge.at(i) getFileName];
            [((CJNarrationIos*)mArrIosBridge.at(i)) stopNarration:strfilePath.c_str()];
            [((CJNarrationIos*)mArrIosBridge.at(i)) unloadPlayer];
    
//            callFunctionWithDelay(callfuncND_selector(CJNarrationSound::test), 0.3, (void*)mArrIosBridge.at(i));
//            vecBeRemoveNarration.push_back(mArrIosBridge.at(i));
            
            mArrIosBridge.erase(it);
            break;
        }
        it ++;
    }
    
    
}

void CJNarrationSound::test(CCNode* sender, void *data)
{
    CJNarrationIos* iosObj = (CJNarrationIos*)data;
    if (iosObj) {
        NSLog(@"iosObj : release");
        [iosObj release];
    }
    
}

void CJNarrationSound::callFunctionWithDelay(cocos2d::SEL_CallFuncND aSelector, float fDelayTime, void* data)
{
    cocos2d::CCActionManager *manager = cocos2d::CCDirector::sharedDirector()->getActionManager();
    cocos2d::CCCallFuncND *callFunc = cocos2d::CCCallFuncND::create((cocos2d::CCObject *)this, aSelector, data);
    cocos2d::CCDelayTime *delay = cocos2d::CCDelayTime::create(fDelayTime);
    cocos2d::CCSequence *action = cocos2d::CCSequence::create(delay, callFunc, NULL);
    
    manager->addAction(CCSequence::create(action,NULL), (cocos2d::CCNode *)this, false);
}

void CJNarrationSound::stopAllNarration()
{
//    NSLog(@"stopAllNarration");
//    for (int i = 0; i < vecBeRemoveNarration.size(); i++) {
//        if(vecBeRemoveNarration[i] != nil)
//        {
//            [vecBeRemoveNarration[i] release];
//            
//        }
//    }
//    vecBeRemoveNarration.clear();
    
    
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        std::string strfilePath = [mArrIosBridge.at(i) getFileName];
        CJNarrationIos* narration = ((CJNarrationIos*)mArrIosBridge.at(i));
        if ([narration isNarrationPlaying]) {
            [narration stopNarration:strfilePath.c_str()];
            [narration unloadPlayer];
            [narration release];
        }

    }
    mArrIosBridge.clear();
//    CJNarrationSound::getInstance()->unloadAllNarration();
}

void CJNarrationSound::removeAllNarration()
{
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        std::string strfilePath = [mArrIosBridge.at(i) getFileName];
        CJNarrationIos* narration = ((CJNarrationIos*)mArrIosBridge.at(i));
        [narration stopNarration:strfilePath.c_str()];
        [narration unloadPlayer];
        [narration release];
    }
    mArrIosBridge.clear();
}


void CJNarrationSound::pauseNarration(std::string filePath)
{
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        if([mArrIosBridge.at(i) getFileName] == filePath)
        {
            std::string strfilePath = [mArrIosBridge.at(i) getFileName];
            [((CJNarrationIos*)mArrIosBridge.at(i)) pauseNarration:strfilePath.c_str()];
        }
    }
}

void CJNarrationSound::pauseAllNarration()
{
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        std::string strfilePath = [mArrIosBridge.at(i) getFileName];
        [((CJNarrationIos*)mArrIosBridge.at(i))  pauseNarration:strfilePath.c_str()];
    }
}

void CJNarrationSound::resumeNarration(std::string filePath)
{
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        if([mArrIosBridge.at(i) getFileName] == filePath)
        {
            std::string strfilePath = [mArrIosBridge.at(i) getFileName];
            [((CJNarrationIos*)mArrIosBridge.at(i)) resumeNarration:strfilePath.c_str()];
        }
        
    }
}

void CJNarrationSound::resumeAllNarration()
{
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        std::string strfilePath = [mArrIosBridge.at(i) getFileName];
        [((CJNarrationIos*)mArrIosBridge.at(i))  resumeNarration:strfilePath.c_str()];
    }
}

bool CJNarrationSound::isNarrationPlaying()
{
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        if([((CJNarrationIos*)mArrIosBridge.at(i)) isNarrationPlaying])
        {
            return true;
        }
    }
    
    return false;
}

float CJNarrationSound::getNarrationMainVolume()
{
    float sumValue = 0;
    
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        sumValue += (float)[((CJNarrationIos*)mArrIosBridge.at(i)) getNarrationVolume];
    }
    return sumValue / mArrIosBridge.size();
}

void CJNarrationSound::setNarrationMainVolume(const float volume)
{
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        [((CJNarrationIos*)mArrIosBridge.at(i)) setNarrationVolume:volume];
    }
}

void CJNarrationSound::setNarrationVolume(const float volume, std::string filePath)
{
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        if([mArrIosBridge.at(i) getFileName] == filePath)
        {
            [((CJNarrationIos*)mArrIosBridge.at(i)) setNarrationVolume:volume];
            return;
        }
    }
    //    SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

void CJNarrationSound::unloadAllNarration()
{
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        std::string strfilePath = [mArrIosBridge.at(i) getFileName];
        if ((CJNarrationIos*)mArrIosBridge.at(i) != nil) {
            [((CJNarrationIos*)mArrIosBridge.at(i)) unloadPlayer];
            [((CJNarrationIos*)mArrIosBridge.at(i)) release];
        }
        
    }
    
    mArrIosBridge.clear();
}

//void CJNarrationSound::onVoiceCallBack(const char*fileName)
void CJNarrationSound::onVoiceCallBack(std::string fileName)
{
    std::string fullPath = fileName;
    stopNarration(fileName);
    fullPath =  CJUtils::getInstance()->stringTokenizer(fullPath, "/", false);
    
    CCString *tempfileName = CCString::create(fullPath);
//    CCLog("CallBack fileName = %s",tempfileName->getCString());
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CJNOTIFICATION_VOICE_FINISHCALL, tempfileName);
    
}
//add play observer
void CJNarrationSound::audioPlayerCallbackPlay(void *player)
{
//    CJNarrationSound *sound = (CJNarrationSound*)player;// use player
}
//add pause observer
void CJNarrationSound::audioPlayerCallbackPause(void *player)
{
    
}
// add stop observer
void CJNarrationSound::audioPlayerCallbackStop(void *player)
{
    
}


void CJNarrationSound::pauseToPlayingNarration()
{
    for (int i = 0; i < mArrIosBridge.size(); i++)
    {
        CJNarrationIos* narration = mArrIosBridge.at(i);
        
        if([narration isNarrationPlaying])
        {
            NSLog(@" narration is playing! ");
            [mArrIosBridge.at(i) pauseNarration:""];
            m_arrPausedNarrations.push_back((CJNarrationIos*)mArrIosBridge.at(i));
        }
    }
}

void CJNarrationSound::resumePausedNarration()
{
    for (int i = 0; i < m_arrPausedNarrations.size(); i++)
    {
        NSLog(@" narration was resumed! ");
        [m_arrPausedNarrations.at(i)  resumeNarration:""];
    }
    m_arrPausedNarrations.clear();
}
