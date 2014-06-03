//
//  CJLMS_ProgressInterface.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMS_ProgressInterface.h"

//////////////////////////////////////////////////
//
// CJLMS_ProgressInterface basic functions.
//
//////////////////////////////////////////////////
CJLMS_ProgressInterface::CJLMS_ProgressInterface(CJLMSDBManage *pDBManager)
{
    _dbManager      = pDBManager;
    _dbProgress     = CJLMSProgress::create(_dbManager);
}

CJLMS_ProgressInterface::~CJLMS_ProgressInterface()
{
    delete _dbProgress;
    
    _dbManager      = NULL;
    _dbProgress     = NULL;
}

CJLMS_ProgressInterface* CJLMS_ProgressInterface::create(CJLMSDBManage *pDBManager)
{
    CJLMS_ProgressInterface *pInterface = new CJLMS_ProgressInterface(pDBManager);
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
// CJLMS_ProgressInterface operating functions.
//
//////////////////////////////////////////////////
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////
bool CJLMS_ProgressInterface::setProgress(Progress progress, int iIdxKids)
{
    return _dbProgress->insertProgress(progress, iIdxKids);
}

bool CJLMS_ProgressInterface::setProgressWithCount(Progress progress, int iCount)
{
    return _dbProgress->insertProgressWithCount(progress, iCount);
}


//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////
bool CJLMS_ProgressInterface::setProgressCount(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID)
{
    return _dbProgress->updateCount(iKidsPrimaryKey, iContentPrimaryKey, iMenuID);
}

bool CJLMS_ProgressInterface::setProgressCount(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID, int iCount)
{
    return _dbProgress->updateCount(iKidsPrimaryKey, iContentPrimaryKey, iMenuID, iCount);
}

bool CJLMS_ProgressInterface::setProgressEndDate(Progress progress)
{
    return _dbProgress->updateEndDate(progress);
}

bool CJLMS_ProgressInterface::setProgressUpdateID(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID, int iUpdateID)
{
    return _dbProgress->updateUpdateId(iKidsPrimaryKey, iContentPrimaryKey, iMenuID, iUpdateID);
}


//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
bool CJLMS_ProgressInterface::getIsExistProgress(std::string strKey)
{
    return _dbProgress->isExistProgress(strKey);
}

Progress CJLMS_ProgressInterface::getProgress(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID)
{
    return _dbProgress->selectProgress(iKidsPrimaryKey, iContentPrimaryKey, iMenuID);
}

int CJLMS_ProgressInterface::getProgressCount(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID)
{
    Progress progress = this->getProgress(iKidsPrimaryKey, iContentPrimaryKey, iMenuID);
    return progress.nCount;
}

int CJLMS_ProgressInterface::getProgressUpdateID(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID)
{
    Progress progress = this->getProgress(iKidsPrimaryKey, iContentPrimaryKey, iMenuID);
    return progress.iUpdateId;
}

std::string CJLMS_ProgressInterface::getProgressStartDate(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID)
{
    Progress progress = this->getProgress(iKidsPrimaryKey, iContentPrimaryKey, iMenuID);
    return progress.szStartDate;
}

std::string CJLMS_ProgressInterface::getProgressEndDate(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID)
{
    Progress progress = this->getProgress(iKidsPrimaryKey, iContentPrimaryKey, iMenuID);
    return progress.szEndDate;
}

std::string CJLMS_ProgressInterface::getProgressKey(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID)
{
    Progress progress = this->getProgress(iKidsPrimaryKey, iContentPrimaryKey, iMenuID);
    return progress.szKey;
}

std::vector<Progress>* CJLMS_ProgressInterface::getProgresses(int iKidsPrimaryKey, int iContentPrimaryKey)
{
    return _dbProgress->selectProgressList(iKidsPrimaryKey, iContentPrimaryKey);
}

std::vector<Progress>* CJLMS_ProgressInterface::getProgressesForUpdate(int iKidsPrimaryKey, int iContentPrimaryKey)
{
    return _dbProgress->selectUpdateProgress(iKidsPrimaryKey, iContentPrimaryKey);
}
