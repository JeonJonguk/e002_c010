//
//  CJLMS_QuestionInterface.cpp
//  SoundPhonics
//
//  Created by j2enty on 13. 8. 22..
//  Copyright (c) 2013년 CJ Educations. All rights reserved.
//

#include "CJLMS_QuestionInterface.h"

//////////////////////////////////////////////////
//
// CJLMS_QuestionInterface basic functions.
//
//////////////////////////////////////////////////

CJLMS_QuestionInterface::CJLMS_QuestionInterface(CJLMSDBManage *pDBManager)
{
    _dbManager      = pDBManager;
    _dbQuestion     = CJLMSQuestion::create(_dbManager);
}

CJLMS_QuestionInterface::~CJLMS_QuestionInterface()
{
    delete _dbQuestion;
    
    _dbManager      = NULL;
    _dbQuestion     = NULL;
}

CJLMS_QuestionInterface* CJLMS_QuestionInterface::create(CJLMSDBManage *pDBManager)
{
    CJLMS_QuestionInterface *pInterface = new CJLMS_QuestionInterface(pDBManager);
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
// CJLMS_QuestionInterface operating functions.
//
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// INSERT
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// UPDATE
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// SELECT
//////////////////////////////////////////////////
Question CJLMS_QuestionInterface::getQuestion(int iQuestionPrimaryKey)
{
    return _dbQuestion->selectContent(iQuestionPrimaryKey);
}

int CJLMS_QuestionInterface::getQuestionIndex(int iQuestionPrimaryKey)
{
    Question question = this->getQuestion(iQuestionPrimaryKey);
    return question.iQNum;
}

int CJLMS_QuestionInterface::getQuestionType(int iQuestionPrimaryKey)
{
    Question question = this->getQuestion(iQuestionPrimaryKey);
    return question.iQCode;
}

int CJLMS_QuestionInterface::getQuestionMenuID(int iQuestionPrimaryKey)
{
    Question question = this->getQuestion(iQuestionPrimaryKey);
    return question.iMenuNum;
}

std::string CJLMS_QuestionInterface::getQuestionContentCode(int iQuestionPrimaryKey)
{
    Question question = this->getQuestion(iQuestionPrimaryKey);
    return question.szContentCode;
}

std::string CJLMS_QuestionInterface::getQuestionThumnailPath(int iQuestionPrimaryKey)
{
    Question question = this->getQuestion(iQuestionPrimaryKey);
    return question.szThumbnailPath;
}

std::string CJLMS_QuestionInterface::getQuestionDesc(int iQuestionPrimaryKey)
{
    Question question = this->getQuestion(iQuestionPrimaryKey);
    return question.szDesc;
}




Question CJLMS_QuestionInterface::getQuestion(std::string strContentCode, int iMenuID, int iQuestionIndex)
{
    return _dbQuestion->selectContent(strContentCode, iMenuID, iQuestionIndex);
}

int CJLMS_QuestionInterface::getQuestionIndex(std::string strContentCode, int iMenuID, int iQuestionIndex)
{
    Question question = this->getQuestion(strContentCode, iMenuID, iQuestionIndex);
    return question.iQNum;
}

int CJLMS_QuestionInterface::getQuestionType(std::string strContentCode, int iMenuID, int iQuestionIndex)
{
    Question question = this->getQuestion(strContentCode, iMenuID, iQuestionIndex);
    return question.iQCode;
}

int CJLMS_QuestionInterface::getQuestionMenuID(std::string strContentCode, int iMenuID, int iQuestionIndex)
{
    Question question = this->getQuestion(strContentCode, iMenuID, iQuestionIndex);
    return question.iMenuNum;
}

std::string CJLMS_QuestionInterface::getQuestionContentCode(std::string strContentCode, int iMenuID, int iQuestionIndex)
{
    Question question = this->getQuestion(strContentCode, iMenuID, iQuestionIndex);
    return question.szContentCode;
}

std::string CJLMS_QuestionInterface::getQuestionThumnailPath(std::string strContentCode, int iMenuID, int iQuestionIndex)
{
    Question question = this->getQuestion(strContentCode, iMenuID, iQuestionIndex);
    return question.szThumbnailPath;
}

std::string CJLMS_QuestionInterface::getQuestionDesc(std::string strContentCode, int iMenuID, int iQuestionIndex)
{
    Question question = this->getQuestion(strContentCode, iMenuID, iQuestionIndex);
    return question.szDesc;
}
