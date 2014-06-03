//
//  CJLMS_DBManageInterface.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMS_DBManageInterface.h"


//////////////////////////////////////////////////
//
// CJLMS_DBManageInterface basic functions.
//
//////////////////////////////////////////////////
CJLMS_DBManageInterface::CJLMS_DBManageInterface(CJLMSDataStorage *pLmsDataStorage)
{
    _dbManager      = CJLMSDBManage::create(pLmsDataStorage);
}

CJLMS_DBManageInterface::~CJLMS_DBManageInterface()
{
    delete _dbManager;
    _dbManager = NULL;
}

CJLMS_DBManageInterface* CJLMS_DBManageInterface::create(CJLMSDataStorage *pLmsDataStorage)
{
    CJLMS_DBManageInterface *pInterface = new CJLMS_DBManageInterface(pLmsDataStorage);
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
// CJLMS_DBManageInterface operating functions.
//
//////////////////////////////////////////////////
CJLMSDBManage* CJLMS_DBManageInterface::getDBManager()
{
    if(NULL!=_dbManager)
    {
        return _dbManager;
    }
    else
    {
        return NULL;
    }
}




