//
//  CJLMS_QuestionInterface.h
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#ifndef __SoundPhonics__CJLMS_QuestionInterface__
#define __SoundPhonics__CJLMS_QuestionInterface__

#include "CJLMSQuestion.h"

class CJLMS_QuestionInterface
{
//////////////////////////////////////////////////
//
// CJLMS_QuestionInterface basic functions.
//
//////////////////////////////////////////////////
public:
    CJLMS_QuestionInterface(CJLMSDBManage *pDBManager);
    virtual ~CJLMS_QuestionInterface();
    
    static CJLMS_QuestionInterface* create(CJLMSDBManage *pDBManager);
    
    
    
private:
    CJLMSDBManage                           *_dbManager;
    CJLMSQuestion                           *_dbQuestion;
    
    
    
//////////////////////////////////////////////////
//
// CJLMS_QuestionInterface QUERY functions.
//
//////////////////////////////////////////////////
public:
//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
    Question                getQuestion(int iQuestionPrimaryKey);
    int                     getQuestionIndex(int iQuestionPrimaryKey);
    int                     getQuestionType(int iQuestionPrimaryKey);
    int                     getQuestionMenuID(int iQuestionPrimaryKey);
    std::string             getQuestionContentCode(int iQuestionPrimaryKey);
    std::string             getQuestionThumnailPath(int iQuestionPrimaryKey);
    std::string             getQuestionDesc(int iQuestionPrimaryKey);
    
    Question                getQuestion(std::string strContentCode, int iMenuID, int iQuestionIndex);
    int                     getQuestionIndex(std::string strContentCode, int iMenuID, int iQuestionIndex);
    int                     getQuestionType(std::string strContentCode, int iMenuID, int iQuestionIndex);
    int                     getQuestionMenuID(std::string strContentCode, int iMenuID, int iQuestionIndex);
    std::string             getQuestionContentCode(std::string strContentCode, int iMenuID, int iQuestionIndex);
    std::string             getQuestionThumnailPath(std::string strContentCode, int iMenuID, int iQuestionIndex);
    std::string             getQuestionDesc(std::string strContentCode, int iMenuID, int iQuestionIndex);
};

#endif /* defined(__SoundPhonics__CJLMS_QuestionInterface__) */
