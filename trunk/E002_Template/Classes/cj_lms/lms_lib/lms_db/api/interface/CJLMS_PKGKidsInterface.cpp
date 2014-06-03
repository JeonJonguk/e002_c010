//
//  CJLMS_PKGKidsInterface.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMS_PKGKidsInterface.h"

//////////////////////////////////////////////////
//
// CJLMS_PKGKidsInterface basic functions.
//
//////////////////////////////////////////////////
CJLMS_PKGKidsInterface::CJLMS_PKGKidsInterface(CJLMSDBManage *pDBManager)
{
    _dbManager      = pDBManager;
    _dbPKGKids      = CJLMSPKGKids::create(_dbManager);
}

CJLMS_PKGKidsInterface::~CJLMS_PKGKidsInterface()
{
    delete _dbPKGKids;
    
    _dbManager      = NULL;
    _dbPKGKids      = NULL;
}

CJLMS_PKGKidsInterface* CJLMS_PKGKidsInterface::create(CJLMSDBManage *pDBManager)
{
    CJLMS_PKGKidsInterface *pInterface = new CJLMS_PKGKidsInterface(pDBManager);
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
// CJLMS_PKGKidsInterface operating functions.
//
//////////////////////////////////////////////////
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////
bool CJLMS_PKGKidsInterface::setKidsInfo(KidsInfo kidsInfo, int iIdxKids)
{
    return _dbPKGKids->insertKids(kidsInfo, iIdxKids);
}


//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////
bool CJLMS_PKGKidsInterface::setKidsStage(int iKidsPrimaryKey, int iStage)
{
    return _dbPKGKids->updateStage(iKidsPrimaryKey, iStage);
}

bool CJLMS_PKGKidsInterface::setKidsStartDate(int iKidsPrimaryKey, std::string strStartDate)
{
    return _dbPKGKids->updateStartDate(iKidsPrimaryKey, strStartDate);
}

bool CJLMS_PKGKidsInterface::setKidsUpdateID(int iKidsPrimaryKey, int iUpdateID)
{
    return _dbPKGKids->updateUpdateId(iKidsPrimaryKey, iUpdateID);
}


//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
int CJLMS_PKGKidsInterface::getPKGKidsPrimayKey(std::string strPKGCode, int iIdxKids)
{
    return _dbPKGKids->selectKidsId(strPKGCode, iIdxKids);
}

KidsInfo CJLMS_PKGKidsInterface::getPKGKidsInfo(int iIdxKids, std::string strPKGCode)
{
    return _dbPKGKids->selectPKGKids(iIdxKids, strPKGCode);
}

int CJLMS_PKGKidsInterface::getPKGKidsIdxKids(int iIdxKids, std::string strPKGCode)
{
    KidsInfo kidsInfo = this->getPKGKidsInfo(iIdxKids, strPKGCode);
    return kidsInfo.iIdxKids;
}

int CJLMS_PKGKidsInterface::getPKGKidsPrimaryKey(int iIdxKids, std::string strPKGCode)
{
    KidsInfo kidsInfo = this->getPKGKidsInfo(iIdxKids, strPKGCode);
    return kidsInfo.iPKGKidsId;
}

int CJLMS_PKGKidsInterface::getPKGKidsStage(int iIdxKids, std::string strPKGCode)
{
    KidsInfo kidsInfo = this->getPKGKidsInfo(iIdxKids, strPKGCode);
    return kidsInfo.iStage;
}

int CJLMS_PKGKidsInterface::getPKGKidsTotalStage(int iIdxKids, std::string strPKGCode)
{
    KidsInfo kidsInfo = this->getPKGKidsInfo(iIdxKids, strPKGCode);
    return kidsInfo.iTotalStage;
}

std::string CJLMS_PKGKidsInterface::getPKGKidsName(int iIdxKids, std::string strPKGCode)
{
    KidsInfo kidsInfo = this->getPKGKidsInfo(iIdxKids, strPKGCode);
    return kidsInfo.szName;
}

std::string CJLMS_PKGKidsInterface::getPKGKidsBirth(int iIdxKids, std::string strPKGCode)
{
    KidsInfo kidsInfo = this->getPKGKidsInfo(iIdxKids, strPKGCode);
    return kidsInfo.szBirth;
}

std::string CJLMS_PKGKidsInterface::getPKGKidsImagePath(int iIdxKids, std::string strPKGCode)
{
    KidsInfo kidsInfo = this->getPKGKidsInfo(iIdxKids, strPKGCode);
    return kidsInfo.szImage;
}

std::string CJLMS_PKGKidsInterface::getPKGKidsWriteDate(int iIdxKids, std::string strPKGCode)
{
    KidsInfo kidsInfo = this->getPKGKidsInfo(iIdxKids, strPKGCode);
    return kidsInfo.szWriteDate;
}

std::string CJLMS_PKGKidsInterface::getPKGKidsComplateDate(int iIdxKids, std::string strPKGCode)
{
    KidsInfo kidsInfo = this->getPKGKidsInfo(iIdxKids, strPKGCode);
    return kidsInfo.szCompleteDate;
}

std::string CJLMS_PKGKidsInterface::getPKGKidsPKGCode(int iIdxKids, std::string strPKGCode)
{
    KidsInfo kidsInfo = this->getPKGKidsInfo(iIdxKids, strPKGCode);
    return kidsInfo.szPKGCode;
}

std::vector<KidsInfo>* CJLMS_PKGKidsInterface::getPKGKidsForUpdate(int iIdxKids)
{
    return _dbPKGKids->selectUpdatePKGKids(iIdxKids);
}
























