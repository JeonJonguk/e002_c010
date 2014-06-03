//
//  CJLMS_GradeInterface.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMS_GradeInterface__
#define __SoundPhonics__CJLMS_GradeInterface__

#include "CJLMSGrade.h"

class CJLMS_GradeInterface
{
//////////////////////////////////////////////////
//
// CJLMS_GradeInterface basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMS_GradeInterface(CJLMSDBManage *pDBManager);
    virtual ~CJLMS_GradeInterface();
    
    static CJLMS_GradeInterface* create(CJLMSDBManage *pDBManager);
    
    
    
private:
    CJLMSDBManage                           *_dbManager;
    CJLMSGrade                              *_dbGrade;
    
    
    
//////////////////////////////////////////////////
//
// CJLMS_GradeInterface QUERY functions.
//
//////////////////////////////////////////////////
public:
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////
    bool                    setGrade(Grade grade, int iIdxKids);
    
    
//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////
    bool                    setGradeUpdateID(int iGradePrimaryKey, int iUpdateID);
    
    
//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
    std::string             getGradeKey(int iGradePrimaryKey);
    
    std::vector<Grade>*     getGrades(int iKidsPrimaryKey, int iContentID, int iQuestionID);
    std::vector<Grade>*     getGradesForUpdate(int iKidsPrimaryKey, int iContentID);
};

#endif /* defined(__SoundPhonics__CJLMS_GradeInterface__) */
