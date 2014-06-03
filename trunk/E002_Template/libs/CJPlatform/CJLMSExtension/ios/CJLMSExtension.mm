//
//  CJLMSExtension.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 11. 8..
//
//

#include "CJLMSExtension.h"
#include "CJLMSExtension_objc.h"
#include "CCUserDefault.h"
#include "cocos2d.h"
#include <SystemConfiguration/CaptiveNetwork.h>

USING_NS_CC;

static void static_end()
{
    [CJLMSExtension_objc  end];
}

static std::string static_getDeviceDateTime()
{
    std::string date = [[[CJLMSExtension_objc sharedEngine] getDeviceDateTime] UTF8String];
    return date;
}

static std::string static_getTargetDateTime(unsigned int packageIndex)
{
    std::string date = [[[CJLMSExtension_objc sharedEngine] getTargetDateTime:packageIndex] UTF8String];
    return date;
}

namespace LMSExtension {
    static CJLMSExtension *s_pExtension;
    
    CJLMSExtension::CJLMSExtension()
    {
        
    }
    
    CJLMSExtension::~CJLMSExtension()
    {
        
    }
    
    CJLMSExtension* CJLMSExtension::sharedInstance()
    {
        if (! s_pExtension)
        {
            s_pExtension = new CJLMSExtension();
        }
        
        return s_pExtension;
    }
    
    void CJLMSExtension::releaseInstance()
    {
        if (s_pExtension)
        {
            delete s_pExtension;
            s_pExtension = NULL;
        }
        
        static_end();
    }
    
    std::string CJLMSExtension::getDBPath()
    {
        NSFileManager *fileManager = [NSFileManager defaultManager];
        NSError *error;
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        
        NSString *dbPath = [documentsDirectory stringByAppendingPathComponent:@"lms.sqlite"];
        
        if ([fileManager fileExistsAtPath:dbPath] == NO) {
            NSString *resourcePath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"PKG/lms.sqlite"];
            [fileManager copyItemAtPath:resourcePath toPath:dbPath error:&error];
        }
        return [dbPath cStringUsingEncoding:[NSString defaultCStringEncoding]];
    }
    
    void CJLMSExtension::callCertification()
    {
        
    }
    
    void CJLMSExtension::callYoutube(const char* youtubeId)
    {
        
    }
    
    long CJLMSExtension::compareDate(const char* startDate)
    {
        return 0;
    }
    
#pragma mark - download data param
    
    std::string CJLMSExtension::getAuthKey()
    {
        return "Txjxk3GmrS54liXrr34xOQA1BeZTl3y95v71ThFUp0ydaWZ0cdWsS34ESmj48Erac2tYyut2mVwM01FrKyp1JdvfX3C0AO13dsN1b4TrDeV2v5zhu0dUamS1Wzl6S2RVUud2gUddo398gUT0tlz1q3mTKzF2zGlvo0wWJN94u8Fx1087AeN3v5zhu0dUamS1Wzl6S2RVUud2gUddo398gUT0tlz1q3mTKzF2zGlvo0wWJN94GvtRm2Zh6Kh2";
    }
    
    std::string CJLMSExtension::getURL()
    {
        return "http://dev-mps.thinkle.net:10100/TGW/IS/mobileInterface/IF-TGW-IS-THINKLE-007";
    }
    
    std::string CJLMSExtension::getUserAgent()
    {
        return "AND;4.1.1 ;720x1024 ;KR ;  ; ;00:0a:eb:68:7f:ee ;ITP-R208W;THINKWARE ;9999 ;9;;json";
    }
    
    std::string CJLMSExtension::getTransactionId()
    {
        return "8605dbba-b4f9-4328-b0e8-9fd901409519";
    }
    
    std::string CJLMSExtension::getInterfaceId()
    {
        return "IF-TGW-IS-THINKLE-007";
    }
    
    std::string CJLMSExtension::getInterfaceVer()
    {
        return "0.1";
    }
    
    std::string CJLMSExtension::getRequestTime()
    {
        return "2013-01-21 11:41:21 028";
    }
    
    bool CJLMSExtension::getNetworkState()
    {
        return true;
    }
    
    int CJLMSExtension::getWifiStrength()
    {
        return 10;
    }
    
    long long CJLMSExtension::getFileSize(const char* path)
    {
        return 0;
    }
    
    bool CJLMSExtension::checkSDCardAvailable()
    {
        return true;
    }
    
    
#pragma mark - file system
    
    long long CJLMSExtension::getFreeSpace()
    {
        return 10000000;
    }
    
    void CJLMSExtension::checkStorageSize()
    {
        
    }
    
    bool CJLMSExtension::removeSaveFile(const char* path)
    {
        return [[NSFileManager defaultManager] removeItemAtPath:[NSString stringWithUTF8String:path] error:nil];
        
//        return false;
    }
    
#pragma mark - get account info
    
    std::string CJLMSExtension::getChildId()
    {
        return "11";
    }
    
    std::string CJLMSExtension::getChildName()
    {
//        return "lala";
        return "점박이";
//        return "가나다라마바사아자차카타파하가";
    }
    
    std::string CJLMSExtension::getChildBirth()
    {
        return "1";
    }
    
    std::string CJLMSExtension::getChildImage()
    {
        return "pkg_common/photo_thumnail_dummy.png";
    }
   
#pragma mark - set mail
    
    void CJLMSExtension::setMailFile(const char* path)
    {
    }
    
    void CJLMSExtension::setMailTitle(const char* title)
    {
    }
    
#pragma mark - init list
    
    void CJLMSExtension::initStepList()
    {
    }
    
    void CJLMSExtension::initContentList()
    {
    }
    
    void CJLMSExtension::initLearnList()
    {
    }
    
    void CJLMSExtension::initGradeList()
    {
    }
    
#pragma mark - init struct
    
    void CJLMSExtension::initStep()
    {
    }
    
    void CJLMSExtension::initContent()
    {
    }
    
    void CJLMSExtension::initLearn()
    {
    }
    
    void CJLMSExtension::initGrade()
    {
    }
    
#pragma mark - add struct to list
    
    void CJLMSExtension::addStep()
    {
    }
    
    void CJLMSExtension::addContent()
    {
    }
    
    void CJLMSExtension::addLearn(unsigned int childID)
    {
    }
    
    void CJLMSExtension::addGrade()
    {
    }
    
#pragma mark - set Step struct
    
    void CJLMSExtension::setStepCount(unsigned int nCount)
    {
    }
    
    void CJLMSExtension::setStepKey(const char* szKey)
    {
    }
    
    void CJLMSExtension::setStepStartDate(const char* szStartDate)
    {
    }
    
    void CJLMSExtension::setStepEndDate(const char* szEndDate)
    {
    }
    
    void CJLMSExtension::setStepExtra(const char* szExtra)
    {
    }
    
#pragma mark - set Content struct
    
    void CJLMSExtension::setContentCode(const char* szContentCode)
    {
    }
    
    void CJLMSExtension::setContentGrade()
    {
    }
    
    void CJLMSExtension::setContentExtra(const char* szExtra)
    {
    }
    
    void CJLMSExtension::setContentList()
    {
    }
    
#pragma mark - set Learn struct
    
    void CJLMSExtension::setLearnPKGName(const char* szPKGName)
    {
    }
    
    void CJLMSExtension::setLearnCompleteDate(const char* szCompleteDate)
    {
    }
    
    void CJLMSExtension::setLearnList()
    {
    }
    
#pragma mark - set Grade struct
    
    void CJLMSExtension::setGrade(unsigned int iGrade)
    {
    }
    
    void CJLMSExtension::setGradeDate(const char* szWriteDate)
    {
    }
    
    void CJLMSExtension::setGradeExtra(const char* szExtra)
    {
    }
    
#pragma mark - send to LMSCenter
    
    unsigned int CJLMSExtension::sendLMSCenter()
    {
        return 0;
    }
    
    unsigned int CJLMSExtension::sendMail(const char* text)
    {
        return 0;
    }
    
#pragma mark - get String
    
    std::string CJLMSExtension::getDeviceDateTime()
    {
        return static_getDeviceDateTime();
    }
    
    std::string CJLMSExtension::getTargetDateTime(unsigned int packageIndex)
    {
        return static_getTargetDateTime(packageIndex);
    }
    
    std::string CJLMSExtension::getDiffDate(const char* date, int days)
    {
        return date;
    }
    
    
    
    void CJLMSExtension::showThinkleStore()
    {
        // nothing
    }
    
    void CJLMSExtension::showBrowser(const char *szUrl)
    {
        NSURL *url = [NSURL URLWithString:[NSString stringWithUTF8String:szUrl]];
        [[UIApplication sharedApplication] openURL:url];
    }
}
