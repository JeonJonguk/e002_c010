//
//  CJLMS_DBManageInterface.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMS_DBManageInterface__
#define __SoundPhonics__CJLMS_DBManageInterface__

#include "cocos2d.h"
#include "CJLMSDBManage.h"

class CJLMSDataStorage;

class CJLMS_DBManageInterface
{
//////////////////////////////////////////////////
//
// CJLMS_DBManageInterface basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMS_DBManageInterface(CJLMSDataStorage *pLmsDataStorage);
    virtual ~CJLMS_DBManageInterface();
    
    static CJLMS_DBManageInterface* create(CJLMSDataStorage *pLmsDataStorage);
    
    
    
private:
    CJLMSDataStorage                        *_lmsDataStorage;
    CJLMSDBManage                           *_dbManager;
    
    
//////////////////////////////////////////////////
//
// CJLMS_DBManageInterface operating functions.
//
//////////////////////////////////////////////////
public:
    CJLMSDBManage*      getDBManager();
};

#endif /* defined(__SoundPhonics__CJLMS_DBManageInterface__) */
