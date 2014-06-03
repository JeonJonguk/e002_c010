//
//  CJLMSQuestion.cpp
//  S001-C130
//
//  Created by Soonho Hong on 13. 4. 8..
//  Copyright (c) 2013 CJ Educations. All rights reserved.
//

#include "CJLMSQuestion.h"
#include "CJLMSDefines.h"

#define SELECT_QUESTION1     "SELECT * FROM tblQuestion WHERE oidQuestion = ?"
#define SELECT_QUESTION2     "SELECT * FROM tblQuestion WHERE strContentCode = ? AND nMenuNum = ? AND nQNum = ?"



#pragma mark - base func
CJLMSQuestion::CJLMSQuestion()
{
    
}

CJLMSQuestion::CJLMSQuestion(CJLMSDBManage *pLmsDBManage)
{
    m_lmsDBManage = pLmsDBManage;
}

CJLMSQuestion::~CJLMSQuestion()
{
    m_lmsDBManage = NULL;
}


CJLMSQuestion* CJLMSQuestion::create(CJLMSDBManage *pLmsDBManage)
{
    CJLMSQuestion *ret = new CJLMSQuestion(pLmsDBManage);
    if(NULL != ret)
    {
        return ret;
    }
    else
    {
        delete ret;
        ret = NULL;
        
        return false;
    }
}





#pragma mark - manage func
Question CJLMSQuestion::selectContent(int questionId)
{
    Question data;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_QUESTION1, strlen(SELECT_QUESTION1)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return data;
    
    sqlite3_bind_int( stmt, 1, questionId);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        data.iQuestionId            = sqlite3_column_int(stmt, 0);
        data.iQNum                  = sqlite3_column_int(stmt, 1);
        data.iQCode                 = sqlite3_column_int(stmt, 2);
        data.iMenuNum               = sqlite3_column_int(stmt, 3);
        data.szContentCode.append((char*)sqlite3_column_text(stmt, 4));
        data.szThumbnailPath.append((char*)sqlite3_column_text(stmt, 5));
        data.szDesc.append((char*)sqlite3_column_text(stmt, 6));
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSProgress\n");
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSProgress\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return data;
}

Question CJLMSQuestion::selectContent(std::string contentCode, int menuNum, int questionIndex)
{
    Question data;
    
    sqlite3_stmt* stmt;
    
    int rst = sqlite3_prepare_v2( m_lmsDBManage->getDB(), SELECT_QUESTION2, strlen(SELECT_QUESTION2)+1, &stmt, NULL );
    if( rst != SQLITE_OK ) return data;
    
    sqlite3_bind_text( stmt, 1, contentCode.c_str(), contentCode.size(), NULL );
    sqlite3_bind_int( stmt, 2, menuNum);
    sqlite3_bind_int( stmt, 3, questionIndex);
    
    int s;
    
    s = sqlite3_step(stmt);
    
    if (s == SQLITE_ROW) {
        data.iQuestionId            = sqlite3_column_int(stmt, 0);
        data.iQNum                  = sqlite3_column_int(stmt, 1);
        data.iQCode                 = sqlite3_column_int(stmt, 2);
        data.iMenuNum               = sqlite3_column_int(stmt, 3);
        data.szContentCode.append((char*)sqlite3_column_text(stmt, 4));
        data.szThumbnailPath.append((char*)sqlite3_column_text(stmt, 5));
        data.szDesc.append((char*)sqlite3_column_text(stmt, 6));
    } else if (s == SQLITE_DONE) {
        printf("done or no data in CJLMSProgress\n");
    } else {
        printf("db select fail. rc : %d, err : %s in CJLMSProgress\n", s, sqlite3_errmsg(m_lmsDBManage->getDB()));
    }
    
    sqlite3_reset( stmt );
    
    assert( sqlite3_finalize(stmt) == SQLITE_OK);
    
    return data;
}
