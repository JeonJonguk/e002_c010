//
//  CJLMSDataStorage.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 23..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMSDataStorage.h"


//////////////////////////////////////////////////
//
// CJLMSDataStorage basic functions.
//
//////////////////////////////////////////////////
CJLMSDataStorage::CJLMSDataStorage()
{
    _dbConnectTimeout       = DEFAULT_DBCONN_TIMEOUT;
    
    _strDBPath.clear();
    _strPKGCode.clear();
    
    this->_resetKidsInfo();
}

CJLMSDataStorage::~CJLMSDataStorage()
{
    _strDBPath              = "";
    _dbConnectTimeout       = DEFAULT_DBCONN_TIMEOUT;
    
    this->_resetKidsInfo();
}

CJLMSDataStorage* CJLMSDataStorage::create()
{
    CJLMSDataStorage *pStorage = new CJLMSDataStorage();
    if(NULL!=pStorage)
    {
        return pStorage;
    }
    else
    {
        delete pStorage;
        pStorage = NULL;
        
        return NULL;
    }
}





//////////////////////////////////////////////////
//
// CJLMS_FileInterface operating functions.
//
//////////////////////////////////////////////////
void CJLMSDataStorage::_resetKidsInfo()
{
    _kidsInfo.iIdxKids          = INT_DEFAULT;
    _kidsInfo.iPKGKidsId        = INT_DEFAULT;
    _kidsInfo.iStage            = INT_DEFAULT;
    _kidsInfo.iTotalStage       = INT_DEFAULT;
    _kidsInfo.szName.clear();
    _kidsInfo.szImage.clear();
    _kidsInfo.szWriteDate.clear();
    _kidsInfo.szCompleteDate.clear();
    _kidsInfo.szPKGCode.clear();
    _kidsInfo.szBirth.clear();
}

void CJLMSDataStorage::setDBPath(std::string strDBPath)
{
    _strDBPath = strDBPath;
}

void CJLMSDataStorage::setDBConnectionTimeout(int iDBConnectionTimeOut)
{
    _dbConnectTimeout = iDBConnectionTimeOut;
}

void CJLMSDataStorage::setKidsInfo(KidsInfo kidsInfo)
{
    _kidsInfo = kidsInfo;
}

void CJLMSDataStorage::setCurrentContent(Content content)
{
    _currentContent = content;
}

void CJLMSDataStorage::setCurrentStage(int iStage)
{
    _kidsInfo.iStage = iStage;
}

void CJLMSDataStorage::setCurrentFile(ResFile resFile)
{
    _currentFile = resFile;
}

void CJLMSDataStorage::setPKGCode(std::string strPKGCode)
{
    _strPKGCode = strPKGCode;
}

std::string CJLMSDataStorage::getDBPath()
{
    return _strDBPath;
}


int CJLMSDataStorage::getDBConnectionTimeOut()
{
    return _dbConnectTimeout;
}


KidsInfo CJLMSDataStorage::getKidsInfo()
{
    return _kidsInfo;
}

int CJLMSDataStorage::getKidsPrimaryKey()
{
    return _kidsInfo.iPKGKidsId;
}

int CJLMSDataStorage::getCurrentStage()
{
    return _kidsInfo.iStage;
}

Content CJLMSDataStorage::getCurrentContent()
{
    return _currentContent;
}

int CJLMSDataStorage::getCurrentContentPrimaryKey()
{
    return _currentContent.iContentId;
}

std::string CJLMSDataStorage::getCurrentContentCode()
{
    return _currentContent.szContentCode;
}

ResFile CJLMSDataStorage::getCurrentFile()
{
    return _currentFile;
}

std::string CJLMSDataStorage::getPKGCode()
{
    return _strPKGCode;
}

int CJLMSDataStorage::getPKGID()
{
    if(0 == _strPKGCode.compare(kProjName_SoundPhonics1))
    {
        return kPKGCode_SoundPhonics1;
    }
    else if(0 == _strPKGCode.compare(kProjName_SoundPhonics2))
    {
        return kPKGCode_SoundPhonics2;
    }
    else
    {
        return INT_DEFAULT;
    }
}

