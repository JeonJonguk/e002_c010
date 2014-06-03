//
//  CJLMS_KidsContentInterface.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMS_KidsContentInterface.h"

//////////////////////////////////////////////////
//
// CJLMS_KidsContentInterface basic functions.
//
//////////////////////////////////////////////////
CJLMS_KidsContentInterface::CJLMS_KidsContentInterface(CJLMSDBManage *pDBManager)
{
    _dbManager      = pDBManager;
    _dbKidsContent  = CJLMSKidsContent::create(_dbManager);
}

CJLMS_KidsContentInterface::~CJLMS_KidsContentInterface()
{
    delete _dbKidsContent;
    
    _dbManager      = NULL;
    _dbKidsContent  = NULL;
}

CJLMS_KidsContentInterface* CJLMS_KidsContentInterface::create(CJLMSDBManage *pDBManager)
{
    CJLMS_KidsContentInterface *pInterface = new CJLMS_KidsContentInterface(pDBManager);
    if(NULL!=pInterface)
    {
        return pInterface;
    }
    else
    {
        delete pInterface;
        pInterface = NULL;
        
        return NULL;
    }
}







//////////////////////////////////////////////////
//
// CJLMS_KidsContentInterface operating functions.
//
//////////////////////////////////////////////////
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////
bool CJLMS_KidsContentInterface::setKidsContent(KidsContent kidsContent, int iKidsPrimaryKey)
{
    return _dbKidsContent->insertKidsContent(kidsContent, iKidsPrimaryKey);
}


//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////
bool CJLMS_KidsContentInterface::setKidsContentCount(int iKidsPrimaryKey, int iContentPrimaryKey, int iCount)
{
    return _dbKidsContent->updateCount(iKidsPrimaryKey, iContentPrimaryKey, iCount);
}

bool CJLMS_KidsContentInterface::setKidsContentGrade(int iKidsPrimaryKey, int iContentPrimaryKey, int iGrade)
{
    return _dbKidsContent->updateGrade(iKidsPrimaryKey, iContentPrimaryKey, iGrade);
}

bool CJLMS_KidsContentInterface::setKidsContentStartDate(int iKidsPrimaryKey, int iContentPrimaryKey, std::string strStartDate)
{
    return _dbKidsContent->updateStartDate(iKidsPrimaryKey, iContentPrimaryKey, strStartDate);
}

bool CJLMS_KidsContentInterface::setKidsContentEndDate(int iKidsPrimaryKey, int iContentPrimaryKey, std::string strEndDate)
{
    return _dbKidsContent->updateEndDate(iKidsPrimaryKey, iContentPrimaryKey, strEndDate);
}

bool CJLMS_KidsContentInterface::setKidsContentUpdateID(int iKidsPrimaryKey, int iContentPrimaryKey, int iUpdateID)
{
    return _dbKidsContent->updateUpdateId(iKidsPrimaryKey, iContentPrimaryKey, iUpdateID);
}


//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
std::vector<KidsContent>* CJLMS_KidsContentInterface::getKidsContents(int iKidsPrimaryKey)
{
    return _dbKidsContent->selectKidsContents(iKidsPrimaryKey);
}

KidsContent CJLMS_KidsContentInterface::getKidsContent(int iKidsPrimaryKey, int iContentPrimaryKey)
{
    return _dbKidsContent->selectKidsContent(iKidsPrimaryKey, iContentPrimaryKey);
}

int CJLMS_KidsContentInterface::getKidsContentPrimaryKey(int iKidsPrimaryKey, int iContentPrimaryKey)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, iContentPrimaryKey);
    return kidsContent.iKidsContentId;
}

int CJLMS_KidsContentInterface::getKidsContentCount(int iKidsPrimaryKey, int iContentPrimaryKey)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, iContentPrimaryKey);
    return kidsContent.nCount;
}

int CJLMS_KidsContentInterface::getKidsContentGrade(int iKidsPrimaryKey, int iContentPrimaryKey)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, iContentPrimaryKey);
    return kidsContent.nGrade;
}

int CJLMS_KidsContentInterface::getKidsContentUpdateID(int iKidsPrimaryKey, int iContentPrimaryKey)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, iContentPrimaryKey);
    return kidsContent.iUpdateId;
}

std::string CJLMS_KidsContentInterface::getKidsContentStartDate(int iKidsPrimaryKey, int iContentPrimaryKey)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, iContentPrimaryKey);
    return kidsContent.szStartDate;
}

std::string CJLMS_KidsContentInterface::getKidsContentEndDate(int iKidsPrimaryKey, int iContentPrimaryKey)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, iContentPrimaryKey);
    return kidsContent.szEndDate;
}

std::string CJLMS_KidsContentInterface::getKidsContentKey(int iKidsPrimaryKey, int iContentPrimaryKey)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, iContentPrimaryKey);
    return kidsContent.szKey;
}


/*
KidsContent CJLMS_KidsContentInterface::getKidsContent(int iKidsPrimaryKey, std::string strPKGCode)
{
    return _dbKidsContent->selectKidsContent(iKidsPrimaryKey, strPKGCode);
}

int CJLMS_KidsContentInterface::getKidsContentPrimaryKey(int iKidsPrimaryKey, std::string strPKGCode)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, strPKGCode);
    return kidsContent.iKidsContentId;
}

int CJLMS_KidsContentInterface::getKidsContentContentForeignKey(int iKidsPrimaryKey, std::string strPKGCode)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, strPKGCode);
    return kidsContent.iContentId;
}

int CJLMS_KidsContentInterface::getKidsContentCount(int iKidsPrimaryKey, std::string strPKGCode)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, strPKGCode);
    return kidsContent.nCount;
}

int CJLMS_KidsContentInterface::getKidsContentGrade(int iKidsPrimaryKey, std::string strPKGCode)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, strPKGCode);
    return kidsContent.nGrade;
}

int CJLMS_KidsContentInterface::getKidsContentUpdateID(int iKidsPrimaryKey, std::string strPKGCode)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, strPKGCode);
    return kidsContent.iUpdateId;
}

std::string CJLMS_KidsContentInterface::getKidsContentStartDate(int iKidsPrimaryKey, std::string strPKGCode)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, strPKGCode);
    return kidsContent.szStartDate;
}

std::string CJLMS_KidsContentInterface::getKidsContentEndDate(int iKidsPrimaryKey, std::string strPKGCode)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, strPKGCode);
    return kidsContent.szEndDate;
}

std::string CJLMS_KidsContentInterface::getKidsContentKey(int iKidsPrimaryKey, std::string strPKGCode)
{
    KidsContent kidsContent = this->getKidsContent(iKidsPrimaryKey, strPKGCode);
    return kidsContent.szKey;
}
*/



std::vector<KidsContent>* CJLMS_KidsContentInterface::getKidsContentsForUpdate(int iKidsPrimaryKey)
{
    return _dbKidsContent->selectUpdateKidsContent(iKidsPrimaryKey);
}
