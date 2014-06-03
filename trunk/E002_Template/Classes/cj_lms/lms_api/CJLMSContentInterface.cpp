//
//  CJLMSContentInterface.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 23..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMSContentInterface.h"
#include "CJLMSExtension.h"

#include "E002_LMSInterface.h"


using namespace LMSExtension;

static CJLMSContentInterface *_sContentInterface = NULL;



//////////////////////////////////////////////////
//
// CJLMSContentInterface basic functions.
//
//////////////////////////////////////////////////
CJLMSContentInterface::CJLMSContentInterface()
{
    CJLMSExtension::sharedInstance();
    if(false == E002_LMSInterface::isExistInstance())
    {
        E002_LMSInterface::getInstance()->init(CJLMSExtension::sharedInstance()->getDBPath());
    }
}

CJLMSContentInterface::~CJLMSContentInterface()
{
    
}

CJLMSContentInterface* CJLMSContentInterface::getInstance()
{
    if(false == CJLMSContentInterface::isExistInstance())
    {
        _sContentInterface  = new CJLMSContentInterface();
    }
    
    return _sContentInterface;
}

void CJLMSContentInterface::release()
{
    if(true == CJLMSContentInterface::isExistInstance())
    {
        delete _sContentInterface;
        _sContentInterface = NULL;
    }
}

bool CJLMSContentInterface::isExistInstance()
{
    if(NULL!=_sContentInterface)
    {
        return true;
    }
    else
    {
        return false;
    }
}





void CJLMSContentInterface::showPackage()
{
    
}


//////////////////////////////////////////////////
//
// CJLMSContentInterface operating functions.
//
//////////////////////////////////////////////////
bool CJLMSContentInterface::setLMSMenuEnd(int iMenuID)
{
    return E002_LMSInterface::getInstance()->setContentProgress(iMenuID);
}

bool CJLMSContentInterface::setLMSGrade(std::vector<CJLMSQuestionResult> questionResults)
{
//    return E002_LMSInterface::getInstance()->setContentGrade(questionResults);
}


std::string CJLMSContentInterface::getLMSFileName(int iMenuID, eFileType eFileType,
                                                  std::string strExtend1/* = ""*/, std::string strExtend2/* = ""*/)
{
    return E002_LMSInterface::getInstance()->getLMSFileName(iMenuID, eFileType, strExtend1, strExtend2);
}

bool CJLMSContentInterface::saveLMSFile()
{
    return E002_LMSInterface::getInstance()->saveLMSFile();
}

CJLMSResource CJLMSContentInterface::getResFile(int iMenuID, eFileType eFileType) {
    return E002_LMSInterface::getInstance()->getResFile(iMenuID, eFileType);
}

int CJLMSContentInterface::getKidsIdx()
{
    return E002_LMSInterface::getInstance()->getKidsIdxKids();
}


