//
//  CJLMSExtension.cpp
//  S001_Template
//
//  Created by Soonho Hong on 12. 11. 8..
//
//

#include "CJLMSExtension.h"
#include "CJSaveDataInterface.h"
#include "jni/CJLMSExtensionJni.h"

namespace LMSExtension {
    static CJLMSExtension * s_pInstance = 0;
    
    CJLMSExtension::CJLMSExtension()
    {
        
    }
    
    CJLMSExtension::~CJLMSExtension()
    {

    }
    
    CJLMSExtension* CJLMSExtension::sharedInstance()
    {
        if (! s_pInstance)
        {
            s_pInstance = new CJLMSExtension();
        }
        
        return s_pInstance;
    }
    
    void CJLMSExtension::releaseInstance()
    {
        endCJJNI();
    }
    
    std::string CJLMSExtension::getDBPath()
    {
        std::string pRet = CJSaveDataInterface::sharedInstance()->getHiddenDirPath();
        pRet.append("/lms.sqlite");
        
        return pRet;
    }
    
    void CJLMSExtension::callCertification()
    {
        callCertificationJNI();
    }
    
    bool CJLMSExtension::getNetworkState()
    {
        return getNetworkStateJNI();
    }
    
    void CJLMSExtension::callYoutube(const char* youtubeId)
    {
        callYoutubeJNI(youtubeId);
    }
    
    long CJLMSExtension::compareDate(const char* startDate)
    {
        return compareDateJNI(startDate);
    }
	
    int CJLMSExtension::getWifiStrength()
    {
        return getWifiStrengthJNI();
    }

    
#pragma mark - download data param
    
    std::string CJLMSExtension::getAuthKey()
    {
        return getAuthKeyJNI();
    }
    
    std::string CJLMSExtension::getURL()
    {
        return getURLJNI();
    }
    
    std::string CJLMSExtension::getUserAgent()
    {
        return getUserAgentJNI();
    }
    
    std::string CJLMSExtension::getTransactionId()
    {
        return getTransactionIdJNI();
    }
    
    std::string CJLMSExtension::getInterfaceId()
    {
        return getInterfaceIdJNI();
    }
    
    std::string CJLMSExtension::getInterfaceVer()
    {
        return getInterfaceVerJNI();
    }
    
    std::string CJLMSExtension::getRequestTime()
    {
        return getRequestTimeJNI();
    }
    
#pragma mark - file system
    
    long long CJLMSExtension::getFileSize(const char* path)
    {
        return getFileSizeJNI(path);
    }
    
    bool CJLMSExtension::checkSDCardAvailable()
    {
        return checkSDCardAvailableJNI();
    }
    
    long long CJLMSExtension::getFreeSpace()
    {
        return getFreeSpaceJNI();
    }
    
    void CJLMSExtension::checkStorageSize()
    {
        checkStorageSizeJNI();
    }
    
    bool CJLMSExtension::removeSaveFile(const char* path)
    {
        return removeSaveFileJNI(path);
    }
    
#pragma mark - get account info
    
    std::string CJLMSExtension::getChildId()
    {
        return getChildIdJNI();
    }
    
    std::string CJLMSExtension::getChildName()
    {
        return getChildNameJNI();
    }
    
    std::string CJLMSExtension::getChildBirth()
    {
        return getChildBirthJNI();
    }
    
    std::string CJLMSExtension::getChildImage()
    {
        return getChildImageJNI();
    }
    
#pragma mark - set mail
    
    void CJLMSExtension::setMailFile(const char* path)
    {
        setMailFileJNI(path);
    }
    
    void CJLMSExtension::setMailTitle(const char* title)
    {
        setMailTitleJNI(title);
    }
    
#pragma mark - init list
    
    void CJLMSExtension::initStepList()
    {
        initStepListJNI();
    }
    
    void CJLMSExtension::initContentList()
    {
        initContentListJNI();
    }
    
    void CJLMSExtension::initLearnList()
    {
        initLearnListJNI();
    }
    
    void CJLMSExtension::initGradeList()
    {
        initGradeListJNI();
    }
    
#pragma mark - init struct
    
    void CJLMSExtension::initStep()
    {
        initStepJNI();
    }
    
    void CJLMSExtension::initContent()
    {
        initContentJNI();
    }
    
    void CJLMSExtension::initLearn()
    {
        initLearnJNI();
    }
    
    void CJLMSExtension::initGrade()
    {
        initGradeJNI();
    }
    
#pragma mark - add struct to list
    
    void CJLMSExtension::addStep()
    {
        addStepJNI();
    }
    
    void CJLMSExtension::addContent()
    {
        addContentJNI();
    }
    
    void CJLMSExtension::addLearn(unsigned int childID)
    {
    	addLearnJNI(childID);
    }
    
    void CJLMSExtension::addGrade()
    {
        addGradeJNI();
    }
    
#pragma mark - set Step struct
    
    void CJLMSExtension::setStepCount(unsigned int nCount)
    {
        setStepCountJNI(nCount);
    }
    
    void CJLMSExtension::setStepKey(const char* szKey)
    {
        setStepKeyJNI(szKey);
    }
    
    void CJLMSExtension::setStepStartDate(const char* szStartDate)
    {
        setStepStartDateJNI(szStartDate);
    }
    
    void CJLMSExtension::setStepEndDate(const char* szEndDate)
    {
        setStepEndDateJNI(szEndDate);
    }
    
    void CJLMSExtension::setStepExtra(const char* szExtra)
    {
        setStepExtraJNI(szExtra);
    }
    
#pragma mark - set Content struct
    
    void CJLMSExtension::setContentCode(const char* szContentCode)
    {
        setContentCodeJNI(szContentCode);
    }
    
    void CJLMSExtension::setContentGrade()
    {
        setContentGradeJNI();
    }
    
    void CJLMSExtension::setContentExtra(const char* szExtra)
    {
        setContentExtraJNI(szExtra);
    }
    
    void CJLMSExtension::setContentList()
    {
        setContentListJNI();
    }
    
#pragma mark - set Learn struct
    
    void CJLMSExtension::setLearnPKGName(const char* szPKGName)
    {
        setLearnPKGNameJNI(szPKGName);
    }
    
    void CJLMSExtension::setLearnCompleteDate(const char* szCompleteDate)
    {
        setLearnCompleteDateJNI(szCompleteDate);
    }
    
    void CJLMSExtension::setLearnList()
    {
        setLearnListJNI();
    }
    
#pragma mark - set Grade struct
    
    void CJLMSExtension::setGrade(unsigned int iGrade)
    {
        setGradeJNI(iGrade);
    }
    
    void CJLMSExtension::setGradeDate(const char* szWriteDate)
    {
        setGradeDateJNI(szWriteDate);
    }
    
    void CJLMSExtension::setGradeExtra(const char* szExtra)
    {
        setGradeExtraJNI(szExtra);
    }
    
#pragma mark - send to LMSCenter
    
    unsigned int CJLMSExtension::sendLMSCenter()
    {
        return sendLMSCenterJNI();
    }
    
    unsigned int CJLMSExtension::sendMail(const char* text)
    {
        return sendMailJNI(text);
    }
    
#pragma mark - get String
    
    std::string CJLMSExtension::getDeviceDateTime()
    {
        return getDeviceDateTimeJNI();
    }
    
    std::string CJLMSExtension::getTargetDateTime(unsigned int packageIndex)
    {
        return getTargetDateTimeJNI(packageIndex);
    }
    
    std::string CJLMSExtension::getDiffDate(const char* date, int days)
    {
        return getDiffDateJNI(date, days);
    }
    
    
    
    
    
    
    
    
    void CJLMSExtension::showThinkleStore()
    {
        showThinkleStoreJNI();
    }
    
    void CJLMSExtension::showBrowser(const char *szUrl)
    {
        showBrowserJNI(szUrl);
    }
}