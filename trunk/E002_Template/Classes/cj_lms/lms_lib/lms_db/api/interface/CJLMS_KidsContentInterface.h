//
//  CJLMS_KidsContentInterface.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMS_KidsContentInterface__
#define __SoundPhonics__CJLMS_KidsContentInterface__

#include "CJLMSKidsContent.h"

class CJLMS_KidsContentInterface
{
//////////////////////////////////////////////////
//
// CJLMS_KidsContentInterface basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMS_KidsContentInterface(CJLMSDBManage *pDBManager);
    virtual ~CJLMS_KidsContentInterface();
    
    static CJLMS_KidsContentInterface* create(CJLMSDBManage *pDBManager);
    
    
    
private:
    CJLMSDBManage                           *_dbManager;
    CJLMSKidsContent                        *_dbKidsContent;
    
    
    
    
    
//////////////////////////////////////////////////
//
// CJLMS_KidsContentInterface QUERY functions.
//
//////////////////////////////////////////////////
public:
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////
    bool                    setKidsContent(KidsContent kidsContent, int iKidsPrimaryKey);

    
//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////
    bool                    setKidsContentCount(int iKidsPrimaryKey, int iContentPrimaryKey, int iCount);
    bool                    setKidsContentGrade(int iKidsPrimaryKey, int iContentPrimaryKey, int iGrade);
    bool                    setKidsContentStartDate(int iKidsPrimaryKey, int iContentPrimaryKey, std::string strStartDate);
    bool                    setKidsContentEndDate(int iKidsPrimaryKey, int iContentPrimaryKey, std::string strEndDate);
    bool                    setKidsContentUpdateID(int iKidsPrimaryKey, int iContentPrimaryKey, int iUpdateID);
    
    
//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
    std::vector<KidsContent>* getKidsContents(int iKidsPrimaryKey);
    KidsContent             getKidsContent(int iKidsPrimaryKey, int iContentPrimaryKey);
    int                     getKidsContentPrimaryKey(int iKidsPrimaryKey, int iContentPrimaryKey);
    int                     getKidsContentCount(int iKidsPrimaryKey, int iContentPrimaryKey);
    int                     getKidsContentGrade(int iKidsPrimaryKey, int iContentPrimaryKey);
    int                     getKidsContentUpdateID(int iKidsPrimaryKey, int iContentPrimaryKey);
    std::string             getKidsContentStartDate(int iKidsPrimaryKey, int iContentPrimaryKey);
    std::string             getKidsContentEndDate(int iKidsPrimaryKey, int iContentPrimaryKey);
    std::string             getKidsContentKey(int iKidsPrimaryKey, int iContentPrimaryKey);
    
    /*
    KidsContent             getKidsContent(int iKidsPrimaryKey, std::string strPKGCode);
    int                     getKidsContentPrimaryKey(int iKidsPrimaryKey, std::string strPKGCode);
    int                     getKidsContentContentForeignKey(int iKidsPrimaryKey, std::string strPKGCode);
    int                     getKidsContentCount(int iKidsPrimaryKey, std::string strPKGCode);
    int                     getKidsContentGrade(int iKidsPrimaryKey, std::string strPKGCode);
    int                     getKidsContentUpdateID(int iKidsPrimaryKey, std::string strPKGCode);
    std::string             getKidsContentStartDate(int iKidsPrimaryKey, std::string strPKGCode);
    std::string             getKidsContentEndDate(int iKidsPrimaryKey, std::string strPKGCode);
    std::string             getKidsContentKey(int iKidsPrimaryKey, std::string strPKGCode);
    */
    std::vector<KidsContent>*   getKidsContentsForUpdate(int iKidsPrimaryKey);
};

#endif /* defined(__SoundPhonics__CJLMS_KidsContentInterface__) */
