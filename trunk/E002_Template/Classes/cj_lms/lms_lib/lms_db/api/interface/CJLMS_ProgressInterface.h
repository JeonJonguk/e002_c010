//
//  CJLMS_ProgressInterface.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMS_ProgressInterface__
#define __SoundPhonics__CJLMS_ProgressInterface__

#include "CJLMSProgress.h"

class CJLMS_ProgressInterface
{
//////////////////////////////////////////////////
//
// CJLMS_ProgressInterface basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMS_ProgressInterface(CJLMSDBManage *pDBManager);
    virtual ~CJLMS_ProgressInterface();
    
    static CJLMS_ProgressInterface* create(CJLMSDBManage *pDBManager);
    
    
    
private:
    CJLMSDBManage                           *_dbManager;
    CJLMSProgress                           *_dbProgress;
    
    
    
//////////////////////////////////////////////////
//
// CJLMS_ProgressInterface QUERY functions.
//
//////////////////////////////////////////////////
public:
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////
    bool                    setProgress(Progress progress, int iIdxKids);
    bool                    setProgressWithCount(Progress progress, int iCount);
    
    
//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////
    bool                    setProgressCount(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID);
    bool                    setProgressCount(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID, int iCount);
    bool                    setProgressEndDate(Progress progress);
    bool                    setProgressUpdateID(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID, int iUpdateID);

    
//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
    bool                    getIsExistProgress(std::string strKey);
    
    Progress                getProgress(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID);
    int                     getProgressCount(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID);
    int                     getProgressUpdateID(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID);
    std::string             getProgressStartDate(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID);
    std::string             getProgressEndDate(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID);
    std::string             getProgressKey(int iKidsPrimaryKey, int iContentPrimaryKey, int iMenuID);
    
    
    std::vector<Progress>*  getProgresses(int iKidsPrimaryKey, int iContentPrimaryKey);
    std::vector<Progress>*  getProgressesForUpdate(int iKidsPrimaryKey, int iContentPrimaryKey);
};

#endif /* defined(__SoundPhonics__CJLMS_ProgressInterface__) */
