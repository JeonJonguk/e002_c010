//
//  CJLMSPKGInterface.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 23..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMSPKGInterface.h"
#include "CJLMSExtension.h"

#include "E002_LMSInterface.h"


using namespace LMSExtension;

static CJLMSPKGInterface *_sPKGInterface = NULL;


//////////////////////////////////////////////////
//
// CJLMSPKGInterface basic functions.
//
//////////////////////////////////////////////////
CJLMSPKGInterface::CJLMSPKGInterface()
{
    CJLMSExtension::sharedInstance();
    if(false == E002_LMSInterface::isExistInstance())
    {
        E002_LMSInterface::getInstance()->init(CJLMSExtension::sharedInstance()->getDBPath());
    }
}

CJLMSPKGInterface::~CJLMSPKGInterface()
{
}

CJLMSPKGInterface* CJLMSPKGInterface::getInstance()
{
    if(false == CJLMSPKGInterface::isExistInstance())
    {
        _sPKGInterface      = new CJLMSPKGInterface();
    }
    
    return _sPKGInterface;
}

void CJLMSPKGInterface::release()
{
    if(true == CJLMSPKGInterface::isExistInstance())
    {
        delete _sPKGInterface;
        _sPKGInterface = NULL;
    }
}

bool CJLMSPKGInterface::isExistInstance()
{
    if(NULL!=_sPKGInterface)
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
// CJLMS_ContentInterface operating functions.
//
//////////////////////////////////////////////////
bool CJLMSPKGInterface::isChildIDLogined()
{
    return E002_LMSInterface::getInstance()->isLauncherLogined();
}

std::string CJLMSPKGInterface::getResourceRootPath()
{
    return E002_LMSInterface::getInstance()->getResourceRootPath();
}

bool CJLMSPKGInterface::startPackage(int iTotalStage, std::string strPKGCode)
{
    return E002_LMSInterface::getInstance()->startPackage(iTotalStage, strPKGCode);
}

bool CJLMSPKGInterface::endPackage()
{
    return E002_LMSInterface::getInstance()->endPackage();
}

bool CJLMSPKGInterface::startContent(std::string strContentCode)
{
    return E002_LMSInterface::getInstance()->startContent(strContentCode);
}

bool CJLMSPKGInterface::endContent()
{
    return E002_LMSInterface::getInstance()->endContent();
}

bool CJLMSPKGInterface::setContentResourcePraise(int iFileID, ePraiseType ePraiseType)
{
    return E002_LMSInterface::getInstance()->setContentResourcePraise(iFileID, ePraiseType);
}



int CJLMSPKGInterface::getOpenStage()
{
    return E002_LMSInterface::getInstance()->getOpenStage();
}

bool CJLMSPKGInterface::setOpenStage(int iStage)
{
    return E002_LMSInterface::getInstance()->setOpenStage(iStage);
}

int CJLMSPKGInterface::getCurrentStage()
{
    return E002_LMSInterface::getInstance()->getCurrentStage();
}

KidsInfo CJLMSPKGInterface::getKidsInfo()
{
    return E002_LMSInterface::getInstance()->getKidsInfo();
}

Content CJLMSPKGInterface::getContent()
{
    return E002_LMSInterface::getInstance()->getContent();
}

Content CJLMSPKGInterface::getContent(int iStage)
{
    return E002_LMSInterface::getInstance()->getContent(iStage);
}

KidsContent CJLMSPKGInterface::getKidsContent(int iContentPrimaryKey)
{
    return E002_LMSInterface::getInstance()->getKidsContent(iContentPrimaryKey);
}

std::vector<KidsContent>* CJLMSPKGInterface::getKidsContents()
{
    return E002_LMSInterface::getInstance()->getKidsContents();
}

std::vector<Progress>* CJLMSPKGInterface::getProgresses(int iContentPrimaryKey)
{
    return E002_LMSInterface::getInstance()->getProgresses(iContentPrimaryKey);
}

std::vector<Grade>* CJLMSPKGInterface::getGrades(int iContentPrimaryKey)
{
    return E002_LMSInterface::getInstance()->getGrades(iContentPrimaryKey);
}

std::vector<Grade>* CJLMSPKGInterface::getGrades(int iContentPrimaryKey, int iQuestionPrimaryKey)
{
    return E002_LMSInterface::getInstance()->getGrades(iContentPrimaryKey, iQuestionPrimaryKey);
}

std::vector<ResFile>* CJLMSPKGInterface::getContentResources(int iContentPrimaryKey, eFileType eFileType)
{
    return E002_LMSInterface::getInstance()->getContentResources(iContentPrimaryKey, eFileType);
}

std::vector<ResFile>* CJLMSPKGInterface::getPackageResources(eFileType eFileType)
{
    return E002_LMSInterface::getInstance()->getPackageResources(eFileType);
}
