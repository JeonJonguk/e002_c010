//
//  CJLMS_GradeInterface.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMS_GradeInterface.h"

//////////////////////////////////////////////////
//
// CJLMS_GradeInterface basic functions.
//
//////////////////////////////////////////////////
CJLMS_GradeInterface::CJLMS_GradeInterface(CJLMSDBManage *pDBManager)
{
    _dbManager      = pDBManager;
    _dbGrade        = CJLMSGrade::create(_dbManager);
}

CJLMS_GradeInterface::~CJLMS_GradeInterface()
{
    delete _dbGrade;
    
    _dbGrade        = NULL;
    _dbManager      = NULL;
}

CJLMS_GradeInterface* CJLMS_GradeInterface::create(CJLMSDBManage *pDBManager)
{
    CJLMS_GradeInterface *pInterface = new CJLMS_GradeInterface(pDBManager);
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
// CJLMS_GradeInterface operating functions.
//
//////////////////////////////////////////////////
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////
bool CJLMS_GradeInterface::setGrade(Grade grade, int iIdxKids)
{
    return _dbGrade->insertGrade(grade, iIdxKids);
}


//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////
bool CJLMS_GradeInterface::setGradeUpdateID(int iGradePrimaryKey, int iUpdateID)
{
    return _dbGrade->updateUpdateId(iGradePrimaryKey, iUpdateID);
}


//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
std::string CJLMS_GradeInterface::getGradeKey(int iGradePrimaryKey)
{
    return _dbGrade->selectKey(iGradePrimaryKey);
}

std::vector<Grade>* CJLMS_GradeInterface::getGrades(int iKidsPrimaryKey, int iContentID, int iQuestionID)
{
    return _dbGrade->selectGrade(iKidsPrimaryKey, iContentID, iQuestionID);
}

std::vector<Grade>* CJLMS_GradeInterface::getGradesForUpdate(int iKidsPrimaryKey, int iContentID)
{
    return _dbGrade->selectUpdateGrade(iKidsPrimaryKey, iContentID);
}
