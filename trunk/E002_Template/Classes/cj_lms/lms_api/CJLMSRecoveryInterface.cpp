//
//  CJLMSRecoveryInterface.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 10. 17..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMSRecoveryInterface.h"
#include "CJLMSExtension.h"

#define kCJEducations_E001_LMS_PATH     "mnt/sdcard/.CJEducations/com.cjeducations.ithink.e001/lms.sqlite"

using namespace LMSExtension;

static CJLMSRecoveryInterface *_sRecoveryInterface = NULL;


//////////////////////////////////////////////////
//
// CJLMSRecoveryInterface basic functions.
//
//////////////////////////////////////////////////
CJLMSRecoveryInterface::CJLMSRecoveryInterface()
{
    CJLMSExtension::sharedInstance();
    if(false == E002_LMSInterface::isExistInstance())
    {
        E002_LMSInterface::getInstance()->init(kCJEducations_E001_LMS_PATH);
    }
}

CJLMSRecoveryInterface::~CJLMSRecoveryInterface()
{
    E002_LMSInterface::release();
}

CJLMSRecoveryInterface* CJLMSRecoveryInterface::getInstance()
{
    if(false == CJLMSRecoveryInterface::isExistInstance())
    {
        _sRecoveryInterface = new CJLMSRecoveryInterface();
    }
    
    return _sRecoveryInterface;
}

void CJLMSRecoveryInterface::release()
{
    if(true == CJLMSRecoveryInterface::isExistInstance())
    {
        delete _sRecoveryInterface;
        _sRecoveryInterface = NULL;
    }
}

bool CJLMSRecoveryInterface::isExistInstance()
{
    if(NULL!=_sRecoveryInterface)
    {
        return true;
    }
    else
    {
        return false;
    }
}



//////////////////////////////////////////////////
//
// CJLMSRecoveryInterface recovery functions.
//
//////////////////////////////////////////////////
bool CJLMSRecoveryInterface::startPackage(int iTotalStage, std::string strPKGCode, int iIdxKids,
                                          std::string strStartDate, std::string strEndDate)
{
    return E002_LMSInterface::getInstance()->recoveryStartPackage(iTotalStage, strPKGCode, iIdxKids,
                                                                  strStartDate, strEndDate);
}

bool CJLMSRecoveryInterface::endPackage()
{
    return E002_LMSInterface::getInstance()->recoveryEndContent();
}

bool CJLMSRecoveryInterface::startContent(std::string strContentCode,
                                          std::string strStartDate, std::string strEndDate)
{
    return E002_LMSInterface::getInstance()->recoveryStartContent(strContentCode,
                                                                  strStartDate, strEndDate);
}

bool CJLMSRecoveryInterface::endContent()
{
    return E002_LMSInterface::getInstance()->recoveryEndContent();
}

bool CJLMSRecoveryInterface::setContentProgress(int iMenuID, int iCount, std::string strKey,
                                                std::string strStartDate, std::string strEndDate)
{
    return E002_LMSInterface::getInstance()->recoverySetContentProgress(iMenuID, iCount, strKey,
                                                                        strStartDate, strEndDate);
}

bool CJLMSRecoveryInterface::setContentGrade(std::string strExtra, std::string strDate)
{
    return E002_LMSInterface::getInstance()->recoverySetContentGrade(strExtra, strDate);
}







